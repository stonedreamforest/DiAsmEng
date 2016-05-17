#include "stdafx.h"
#include "data.h"
#include "engine.h"


engine::engine(int n)
{
	m_OPcodLength=n;

	LPrefix=0	;						// 锁定前缀				F0
	OpSPrefix=0;						// 切换操作数大小前缀	66
	AddSPrefix=0;						// 切换地址大小前缀		67
	RepOpPrefixF2=0	;					// 重复操作前缀			F2
	RepOpPrefixF3=0	;					// 重复操作前缀			F3
	CsegPrefix2E=0;						// CS 段超越前缀		2E	
	CsegPrefix3E=0;						// DS 段超越前缀		3E	
	CsegPrefix26=0;						// ES 段超越前缀		26
	CsegPrefix36=0;						// SS 段超越前缀		36	
	CsegPrefix64=0;						// FS 段超越前缀		64	
	CsegPrefix65=0;						// GS 段超越前缀		65
	
	iscode=false;
}


engine::~engine(void)
{

}

void engine::GetPrefix(
	PBYTE &pbyCodeBuf,
	WCHAR Code[MAX_PATH])
{

	while (1)	//判断是否为前缀
	{
		switch(*pbyCodeBuf)
		{
		case 0x66:				// 切换操作数大小
			{
				OpSPrefix=1;break;
			}
		case 0x67:				//切换地址大小  高->低
			{
				AddSPrefix=1;break;
			}
		case 0xF2:	
			{
				RepOpPrefixF2=1;	break;
			}			//重复操作前缀
		case 0xF3:
			{
				RepOpPrefixF3=1;	break;
			}
		case 0x2E:
			{
				CsegPrefix2E=1;break;
			}
		case 0x3E:
			{
				CsegPrefix3E=1;break;
			}
		case 0x26:
			{
				CsegPrefix26=1;break;
			}
		case 0x36:
			{
				CsegPrefix36=1;break;
			}		
		case 0x64:
			{
				CsegPrefix64=1;break;
			}
		case 0x65:
			{
				CsegPrefix65=1;break;
			}
		case 0xF0:
			{
				LPrefix=1;break;
			}
		default:
			return ;
		}
		pbyCodeBuf++;
		m_OPcodLength--;
	}
}
//反汇编引擎
void engine::DisassemblyEngine(
	PBYTE pbyCodeBuf)
{
	//判断指令长度
	//for (int i = 0; i < m_OPcodLength; i++)
	//{
	//	printf("%02x ",*pbyCodeBuf);
	//}

	
	while(m_OPcodLength>0)
	{
		PBYTE TempPbyCodeBuf=pbyCodeBuf;
		int TempLength=m_OPcodLength;
		printf("%08x",pbyCodeBuf);
		WCHAR Code[MAX_PATH]={};

		//给前缀设定标记
		/*printf("  %02x ",*pbyCodeBuf);*/
		GetPrefix(pbyCodeBuf,Code);

		BYTE byCodeNprefix=*pbyCodeBuf;		//无F2 F3 F0前缀

		//解析指令
				
		GetInstruction(pbyCodeBuf,Code);
		
		BYTE byCode=*pbyCodeBuf;
		//byCodeNprefix=*pbyCodeBuf;
		unsigned int operation1;
		
		if(LPrefix==1||RepOpPrefixF2==1||RepOpPrefixF3==1)
		{
			operation1=g_stcopcode[byCode].Operation1;	
		}
		else
		{
			operation1=g_stcopcode[byCodeNprefix].Operation1;
		}
		if (operation1)			//判断是否有值
		{
			//printf("%02x ",*pbyCodeBuf);
			GetOperation(pbyCodeBuf,Code,operation1);
		}

		//再解析操作数2
		
		unsigned int operation2;
		if (LPrefix==1||RepOpPrefixF2==1||RepOpPrefixF3==1)
		{
			RegionFlag = (PMODR_M)pbyCodeBuf++;
			operation2=g_stcopcode[byCode].Operation2;
		}
		else
		{
			operation2=g_stcopcode[byCodeNprefix].Operation2;
		}
		if (operation2)
		{
			swprintf_s(Code,L"%s %s",Code,L",");
			GetOperation(pbyCodeBuf,Code,operation2);			
		}
		jxx(pbyCodeBuf,Code,operation1);
		printf("  ");
		for (int i = 0; i < TempLength-m_OPcodLength; i++)
		{
			if(i==1)
			{
				printf(" ");
			}
			printf("%02x",*TempPbyCodeBuf++);
		}
		printf(" ");
		swprintf_s(Code,L"%s %s",Code,L"\n");		
		CursorPosition(15,y++,Code,F_YELLOW);
		
		//初始化前缀标记开始执行下条指令
		LPrefix=0	;	
		OpSPrefix=0;	
		AddSPrefix=0;	
		RepOpPrefixF2=0;
		RepOpPrefixF3=0;
		CsegPrefix2E=0;
		CsegPrefix3E=0;
		CsegPrefix26=0;
		CsegPrefix36=0;
		CsegPrefix64=0;
		CsegPrefix65=0;
		//*pbyCodeBuf++;
		iscode=false;
			
	}

	

}
//跳转指令
void engine::jxx(PBYTE &pbyCodeBuf,	WCHAR Code[MAX_PATH],UINT uOperation)
{
	
	if(uOperation==0)		//一字节的跳转指令大部分jxx是没有 操作数1 2的 
	{
		*pbyCodeBuf--;			//指向前一个 例 77 55    指向77
		switch (*pbyCodeBuf)
		{
		case 0x70 :
		case 0x71 :
		case 0x72 :
		case 0x73 :
		case 0x74 :
		case 0x75 :
		case 0x76 :
		case 0x77 :
		case 0x78 :
		case 0x79 :
		case 0x7A :
		case 0x7B :
		case 0x7C :
		case 0x7D :
		case 0x7E :
		case 0x7F :
			{
				*pbyCodeBuf++;		//复位		指向55
				swprintf_s(Code,MAX_PATH,L"%s %s[0x%08x]",Code,L"short disassemb.",(*pbyCodeBuf)+pbyCodeBuf+1);
				m_OPcodLength--;
				pbyCodeBuf++;
			}
			break;
		default:
			*pbyCodeBuf++;			//不是跳转复位  指向55
			break;
		}
	}
	
}
//匹配前缀1
void engine::MatePrefix1(
	PBYTE &pbyCodeBuf,
	WCHAR Code[MAX_PATH])
{
		if(LPrefix==1)
	{
		StringCchCopy(Code,_MAX_PATH,L" lock");	
	}
	if(RepOpPrefixF2==1)
	{
		StringCchCopy(Code,_MAX_PATH,L" repne");	
	}
	if(RepOpPrefixF3==1)
	{
		StringCchCopy(Code,_MAX_PATH,L" rep");	 
	}
	if(RepOpPrefixF2==1&&LPrefix==1)
	{
		StringCchCopy(Code,_MAX_PATH,L" lock repne");	 
	}
	if(RepOpPrefixF3==1&&LPrefix==1)
	{
		StringCchCopy(Code,_MAX_PATH,L" lock rep");	
	}
}
//获取操作码  前缀不可能存在正常指令后面   例：0x55,0x66(段前缀),是错误的！
void engine::GetInstruction(
	PBYTE &pbyCodeBuf,	
	WCHAR Code[MAX_PATH])
{

	MatePrefix1(pbyCodeBuf,Code);
	PMODR_M Modr_m=(PMODR_M)(pbyCodeBuf+1);
	switch(*pbyCodeBuf)
	{
	case 0x80:					//当操作码为组1			组不做 时间不够难度有点高  但大致框架还是放在这里  有时间再来  
	case 0x81:
	case 0x82:
	case 0x83:
		{
			/*StringCchCopy(Code,_MAX_PATH,g_Grp[0][Modr_m->REG]);*/
			break;
		}
	case 0xc0:					//当操作码为组2
	case 0xC1:
	case 0xD0:
	case 0xD1:
	case 0xD2:
	case 0xD3:
		{
			/*StringCchCopy(Code,_MAX_PATH,g_Grp[1][Modr_m->REG]);*/
			break;
		}
	case 0xF6:
	case 0xF7:					//当操作码为组3	
		{
			/*StringCchCopy(Code,_MAX_PATH,g_Grp[2][Modr_m->REG]);*/
			break;
		}
	case 0xFE:					//当操作码为组4
		{
			/*StringCchCopy(Code,_MAX_PATH,g_Grp[3][Modr_m->REG]);*/
			break;
		}
	case 0xFF:					//当操作码为组5
		{
			/*StringCchCopy(Code,_MAX_PATH,g_Grp[4][Modr_m->REG]);*/
			break;
		}
	default:					//当操作码不是组  按正常解析  
		{
			swprintf_s(Code,MAX_PATH,L"%s %s",Code,g_stcopcode[*pbyCodeBuf].szInstruction);
			//if (m_OPcodLength==1)		//单操作数	特殊处理
			//{
			//	return;
			//}
			/*if (CsegPrefix2E==1)
			{
				return;
			}*/
			//StringCchCopy(Code,_MAX_PATH,L"%s,%s",Code,);		
		}
		if (LPrefix==1||RepOpPrefixF2==1||RepOpPrefixF3==1)
		{
			m_OPcodLength--;
			return;
		}		
	}
		pbyCodeBuf++;			//地址取下一个字节
		m_OPcodLength--;		//所有指令长度减一  相当于将传进来的数组长度减1
}
//匹配寄存器
void engine::GetReg(
	UINT uOPertype,
	WCHAR Code[MAX_PATH])
{
	switch (uOPertype)		//匹配寄存器类型
	{
	case _AL_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"al");break;	//输出8bit寄存器  下同
	case _BL_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"bl");break;
	case _CL_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"cl");break;
	case _DL_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"dl");break;
	case _AH_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ah");break;
	case _CH_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ch");break;
	case _DH_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"dh");break;
	case _BH_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"bh");break;

	case _AX_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ax");break;		//输出16bit寄存器  下同
	case _BX_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"bx");break;
	case _CX_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"cx");break;
	case _DX_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"dx");break;

	case _EAX_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"eax");break;		//输出32bit寄存器   下同
	case _EBX_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ebx");break;
	case _ECX_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ecx");break;
	case _EDX_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"edx");break;
	case _ESP_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"esp");break;
	case _EBP_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ebp");break;
	case _ESI_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"esi");break;
	case _EDI_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"edi");break;
	case _ES_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"es");break;
	case _CS_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"cs");break;
	case _DS_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ds");break;
	case _SS_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ss");break;
	}
}
//解析操作数
void engine::GetOperation(
	PBYTE &pCodeBuf,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	if(uOperation>=0x2000)		//判断操作数是否需要查MOD表
	{
		//操作数位寄存器时
		
		GetReg(uOperation,Code);
		return;
	}
	/*printf("%02x ",*pCodeBuf);*/
	//当为组合码时
	UINT uOperType=uOperation & 0xFF00;		//高位不变 低位清零  用以判断是否为寄存器

	if(uOperType==_E_||uOperType==_G_)		
	{
		if (!iscode)
		{
			RegionFlag = (PMODR_M)pCodeBuf++;	//取操作数
			m_OPcodLength--;
			iscode=true;
		}
	}
	MatePrefix2(pCodeBuf,Code,uOperation);

	switch (uOperType)
	{
	case _M_:
	case _E_:
		GetType_E_(pCodeBuf,RegionFlag,Code,uOperation);
		break;
	case _G_:
		GetType_G_(pCodeBuf,RegionFlag,Code,uOperation);
		break;
	case _I_:
		GetType_I_(pCodeBuf,RegionFlag,Code,uOperation);
		break;
	case _Y_:
		GetType_Y_(pCodeBuf,RegionFlag,Code,uOperation);
		break;
	case _X_:
		GetType_X_(pCodeBuf,RegionFlag,Code,uOperation);
		break;
	case _S_:
		GetType_S_(pCodeBuf,RegionFlag,Code,uOperation);
		break;
	case _O_:
		GetType_O_(pCodeBuf,RegionFlag,Code,uOperation);
		break;
	case _J_:
		GetType_J_(pCodeBuf,RegionFlag,Code,uOperation);
		break;
	}
} 
//匹配类型_J_
void engine::GetType_J_(
	PBYTE &pCodeBuf,
	PMODR_M RegionFlag,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//高位不变 低位清零  用以判断是类型
	switch (byopcodeSize)
	{
	case _b_:
		{
			swprintf_s(Code,MAX_PATH,L"%s %s[0x%08x]",Code,L"short disassemb.",(*pCodeBuf)+pCodeBuf+1);
			m_OPcodLength--;
			pCodeBuf++;
		}
		break;
	case _z_:
		{
			swprintf_s(Code,MAX_PATH,L"%s %08x",Code,
				 *(int*)pCodeBuf+pCodeBuf+4);
				pCodeBuf+=4;
			m_OPcodLength-=4;
		}
	}
}
//匹配类型_M_
void engine::GetType_O_(
	PBYTE &pCodeBuf,
	PMODR_M RegionFlag,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//高位不变 低位清零  用以判断是类型
	//int Size=getSize(byopcodeSize);
	switch (byopcodeSize)
	{
	case _b_:
		{
			swprintf_s(Code,MAX_PATH,L"%s %s[0x%x%x%x%x]",Code,L"byte ptr ds:",*pCodeBuf++,
				*pCodeBuf++,*pCodeBuf++,*pCodeBuf++);
			m_OPcodLength-=4;
		}
		break;
	case _v_:
		{
			swprintf_s(Code,MAX_PATH,L"%s %s[0x%x%x%x%x]",Code,L"dword ptr ds:",*pCodeBuf++,
				*pCodeBuf++,*pCodeBuf++,*pCodeBuf++);
			m_OPcodLength-=4;
		}
	}
}
//匹配类型_S_
void engine::GetType_S_(
	PBYTE &pCodeBuf,
	PMODR_M RegionFlag,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//高位不变 低位清零  用以判断是类型
	//int Size=getSize(byopcodeSize);
	switch (byopcodeSize)
	{
	case _w_:
		{
			swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ss");
		}
	}
}
//匹配类型_X_
void engine::GetType_X_(
	PBYTE &pCodeBuf,
	PMODR_M RegionFlag,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//高位不变 低位清零  用以判断是类型
	//int Size=getSize(byopcodeSize);
	switch (byopcodeSize)
	{
	case _v_:
	case _z_:
		{
			swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"dword ptr ds:[esi]");
		}
		break;
	case _b_:
		{
			swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"byte ptr ds:[esi]");
		}
		break;
	}
}
//匹配类型_Y_
void engine::GetType_Y_(
	PBYTE &pCodeBuf,
	PMODR_M RegionFlag,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//高位不变 低位清零  用以判断是类型
	//int Size=getSize(byopcodeSize);
	switch (byopcodeSize)
	{
	case _v_:
	case _z_:
		{
			swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"dword ptr es:[edi]");
		}
		break;
	case _b_:
		{
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"byte ptr es:[edi]");
		}
		break;
	}
}
//匹配类型_I_
void engine::GetType_I_(
	PBYTE &pCodeBuf,
	PMODR_M RegionFlag,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//高位不变 低位清零  用以判断是类型
	//int Size=getSize(byopcodeSize);
	switch (byopcodeSize)
	{
	case _v_:
	case _d_:
	case _z_:
		{
			swprintf_s(Code,MAX_PATH,L"%s 0x%x%x%x%x",Code,*pCodeBuf++,	
			*pCodeBuf++,*pCodeBuf++,*pCodeBuf++);
			m_OPcodLength-=4;
		}
		break;
	case _w_:
		{
			swprintf_s(Code,MAX_PATH,L"%s 0x%x%x",Code,*pCodeBuf++,	
			*pCodeBuf++);
			m_OPcodLength-=2;
		}
		break;
	case _b_:
		{
		swprintf_s(Code,MAX_PATH,L"%s 0x%x",Code,	
			*pCodeBuf++);
		m_OPcodLength--;
		}
		break;
	}	
}
//匹配前缀
void engine::MatePrefix2(
	PBYTE &pbyCodeBuf,	
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//取低位
	UINT uOperType=uOperation & 0xFF00;		//取高位
	if (uOperType==_E_||uOperType==_M_)
	{
		switch (byopcodeSize)
		{
		case _b_:
			swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"byte ptr ");
			break;
		case _v_:
		case _w_:
			swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"dword ptr ");
			break;
		}
	}	
	if(CsegPrefix2E==1)
	{
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"cs: ");
		CsegPrefix2E=0; 
	}
	if(CsegPrefix3E==1)
	{
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ds: ");
		CsegPrefix3E=0; 
	}
	if(CsegPrefix26==1)
	{
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"es: ");
		CsegPrefix26=0; 
	}
	if(CsegPrefix36==1)
	{
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ss: ");
		CsegPrefix36=0; 
	}	
	if(CsegPrefix64==1)
	{
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ss: ");
		CsegPrefix64=0; 
	}	
	if(CsegPrefix65==1)
	{
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ss: ");
		CsegPrefix65=0; 
	}				
}
//匹配类型_G_
void engine::GetType_G_(
	PBYTE		&pCodeBuf,
	PMODR_M		RegionFlag,
	WCHAR	    Code[MAX_PATH],
	UINT		uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//高位不变 低位清零  用以判断是类型
	int Size=getSize(byopcodeSize);
	swprintf_s(Code,MAX_PATH,L"%s %s",Code,	
		g_szRM3[Size][RegionFlag->REG]);

	
}
//匹配类型_E_
void engine::GetType_E_(
	PBYTE		&pCodeBuf,	
	PMODR_M		RegionFlag,	
	WCHAR	    Code[MAX_PATH],	
	UINT		uOperation)
{
	wchar_t szSib[30];
	switch (RegionFlag->MOD)			//都是以二进制实现 所以可以匹配该域  下同
	{
	case 0:			//MOD域1
		{
			if(RegionFlag->R_M==4)		//[--][--]
			{
				FindeSib(pCodeBuf,szSib,Code);
				break;
			}
			if(RegionFlag->R_M==5)		//立即数
			{
				swprintf_s(Code,MAX_PATH,L"%s [0x%x%x%x%x]",Code,*pCodeBuf++,	
					*pCodeBuf++,*pCodeBuf++,*pCodeBuf++);
				m_OPcodLength-=4;
			}
			swprintf_s(Code,MAX_PATH,L"%s %s",Code,g_szRM[RegionFlag->MOD][RegionFlag->R_M]);
		}
		break;
	case 1:
		{
			if(RegionFlag->R_M==4)		//[--][--]
			{
				FindeSib(pCodeBuf,szSib,Code);
				break;
			}
			//可能要加 段超越
			//
			swprintf_s(Code,MAX_PATH,L"%s [%s+0x%x]",Code,g_szRM[RegionFlag->MOD][RegionFlag->R_M],
				*pCodeBuf++
				);
			m_OPcodLength--;	
		}
		break;
	case 2:
		{
			if(RegionFlag->R_M==4)		//[--][--]
			{
				FindeSib(pCodeBuf,szSib,Code);
				break;
			}
			swprintf_s(Code,MAX_PATH,L"%s [%s+0x%x%x%x%x]",Code,g_szRM[RegionFlag->MOD][RegionFlag->R_M],
				*pCodeBuf++,*pCodeBuf++,*pCodeBuf++,*pCodeBuf++);
			m_OPcodLength-=4;
		}
		break;
	case 3:
		{
			BYTE byopcodeSize=uOperation &0xff;		//低位位不变 低位清零  用以判断是类型
			int Size=getSize(byopcodeSize);
			swprintf_s(Code,MAX_PATH,L"%s %s",Code,	
				g_szRM3[Size][RegionFlag->R_M]);
		}			
		break;
	}
}
//sib查找
void engine::FindeSib(
	PBYTE &pCodeBuf,
	wchar_t szSib[],
	WCHAR Code[MAX_PATH])
{
	//先处理特殊情况 MOD
	SibFlag=(PSIB)pCodeBuf;
	wchar_t lpBase[20]={};
	wchar_t lpBase2[20]={};
	//MOD bits Effective Address
	switch (RegionFlag->MOD)
	{
	case 0:					//00 [scaled index] + disp32
		{
			if (SibFlag->BASE==5)
			{
				swprintf_s(lpBase,L"%s]",g_szBASE[SibFlag->BASE]);

				break;
			}
			swprintf_s(lpBase,L"%s]",g_szBASE[SibFlag->BASE]);
		}
		break;
	case 1:				//01 [scaled index] + disp8 + [EBP]
		{
			if (SibFlag->BASE==5)
			{
				swprintf_s(lpBase,L"ebp+0x%x]",*pCodeBuf++);
				m_OPcodLength--;
				break;
			}
			swprintf_s(lpBase,L"%s+0x%x]",g_szBASE[SibFlag->BASE],*pCodeBuf++);
			m_OPcodLength--;
		}
		break;
	case 2:				//10  [scaled index] + disp32 + [EBP]
		{
			if (SibFlag->BASE==5)
			{
				swprintf_s(lpBase,L"ebp+0x%x%x%x%x]",*pCodeBuf++,
					*pCodeBuf++,*pCodeBuf++,*pCodeBuf++);
				m_OPcodLength-=4;
				break;
			}
			swprintf_s(lpBase,L"%s+0x%x%x%x%x]",g_szBASE[SibFlag->BASE],
					*pCodeBuf++,*pCodeBuf++,*pCodeBuf++,*pCodeBuf++);
			m_OPcodLength-=4;
		}
		break;
	}
	//Scaled Index  中是否为none
	if (SibFlag->INDEX!=4)
	{
		swprintf_s(szSib,30,L"[%s+%s",g_szSCALED[SibFlag->SS][SibFlag->INDEX],lpBase);
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,szSib);
		pCodeBuf++;
		m_OPcodLength--;
		return;
	}
	swprintf_s(szSib,30,L"[%s",lpBase);			//不为none  不为 [*]
	swprintf_s(Code,MAX_PATH,L"%s %s",Code,szSib);
}

//获取该指令大小
int	engine::getSize(BYTE byopcodeSize)
{
	switch (byopcodeSize)
	{
	case _b_:
		return 0;
	case _w_:
		return 1;
	case _d_:
		return 2;
	}
	return 2;
}

//
void engine::CursorPosition(int x,int y,wchar_t *pszChar,WORD wArr)
{
	CONSOLE_CURSOR_INFO Cui={1,FALSE};
	HANDLE hout;
	COORD coord;
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hout,&Cui);//取消光标
	coord.X=2*x;
	coord.Y=y;

	SetConsoleTextAttribute(hout,wArr);
	SetConsoleCursorPosition(hout,coord);//光标位置
	wprintf_s(pszChar);
	SetConsoleTextAttribute(hout,7);
	//WriteConsoleInputA()
	//WriteConsoleOutputCharacter
}