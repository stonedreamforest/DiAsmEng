#include "stdafx.h"
#include "data.h"
#include "engine.h"


engine::engine(int n)
{
	m_OPcodLength=n;

	LPrefix=0	;						// ����ǰ׺				F0
	OpSPrefix=0;						// �л���������Сǰ׺	66
	AddSPrefix=0;						// �л���ַ��Сǰ׺		67
	RepOpPrefixF2=0	;					// �ظ�����ǰ׺			F2
	RepOpPrefixF3=0	;					// �ظ�����ǰ׺			F3
	CsegPrefix2E=0;						// CS �γ�Խǰ׺		2E	
	CsegPrefix3E=0;						// DS �γ�Խǰ׺		3E	
	CsegPrefix26=0;						// ES �γ�Խǰ׺		26
	CsegPrefix36=0;						// SS �γ�Խǰ׺		36	
	CsegPrefix64=0;						// FS �γ�Խǰ׺		64	
	CsegPrefix65=0;						// GS �γ�Խǰ׺		65
	
	iscode=false;
}


engine::~engine(void)
{

}

void engine::GetPrefix(
	PBYTE &pbyCodeBuf,
	WCHAR Code[MAX_PATH])
{

	while (1)	//�ж��Ƿ�Ϊǰ׺
	{
		switch(*pbyCodeBuf)
		{
		case 0x66:				// �л���������С
			{
				OpSPrefix=1;break;
			}
		case 0x67:				//�л���ַ��С  ��->��
			{
				AddSPrefix=1;break;
			}
		case 0xF2:	
			{
				RepOpPrefixF2=1;	break;
			}			//�ظ�����ǰ׺
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
//���������
void engine::DisassemblyEngine(
	PBYTE pbyCodeBuf)
{
	//�ж�ָ���
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

		//��ǰ׺�趨���
		/*printf("  %02x ",*pbyCodeBuf);*/
		GetPrefix(pbyCodeBuf,Code);

		BYTE byCodeNprefix=*pbyCodeBuf;		//��F2 F3 F0ǰ׺

		//����ָ��
				
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
		if (operation1)			//�ж��Ƿ���ֵ
		{
			//printf("%02x ",*pbyCodeBuf);
			GetOperation(pbyCodeBuf,Code,operation1);
		}

		//�ٽ���������2
		
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
		
		//��ʼ��ǰ׺��ǿ�ʼִ������ָ��
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
//��תָ��
void engine::jxx(PBYTE &pbyCodeBuf,	WCHAR Code[MAX_PATH],UINT uOperation)
{
	
	if(uOperation==0)		//һ�ֽڵ���תָ��󲿷�jxx��û�� ������1 2�� 
	{
		*pbyCodeBuf--;			//ָ��ǰһ�� �� 77 55    ָ��77
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
				*pbyCodeBuf++;		//��λ		ָ��55
				swprintf_s(Code,MAX_PATH,L"%s %s[0x%08x]",Code,L"short disassemb.",(*pbyCodeBuf)+pbyCodeBuf+1);
				m_OPcodLength--;
				pbyCodeBuf++;
			}
			break;
		default:
			*pbyCodeBuf++;			//������ת��λ  ָ��55
			break;
		}
	}
	
}
//ƥ��ǰ׺1
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
//��ȡ������  ǰ׺�����ܴ�������ָ�����   ����0x55,0x66(��ǰ׺),�Ǵ���ģ�
void engine::GetInstruction(
	PBYTE &pbyCodeBuf,	
	WCHAR Code[MAX_PATH])
{

	MatePrefix1(pbyCodeBuf,Code);
	PMODR_M Modr_m=(PMODR_M)(pbyCodeBuf+1);
	switch(*pbyCodeBuf)
	{
	case 0x80:					//��������Ϊ��1			�鲻�� ʱ�䲻���Ѷ��е��  �����¿�ܻ��Ƿ�������  ��ʱ������  
	case 0x81:
	case 0x82:
	case 0x83:
		{
			/*StringCchCopy(Code,_MAX_PATH,g_Grp[0][Modr_m->REG]);*/
			break;
		}
	case 0xc0:					//��������Ϊ��2
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
	case 0xF7:					//��������Ϊ��3	
		{
			/*StringCchCopy(Code,_MAX_PATH,g_Grp[2][Modr_m->REG]);*/
			break;
		}
	case 0xFE:					//��������Ϊ��4
		{
			/*StringCchCopy(Code,_MAX_PATH,g_Grp[3][Modr_m->REG]);*/
			break;
		}
	case 0xFF:					//��������Ϊ��5
		{
			/*StringCchCopy(Code,_MAX_PATH,g_Grp[4][Modr_m->REG]);*/
			break;
		}
	default:					//�������벻����  ����������  
		{
			swprintf_s(Code,MAX_PATH,L"%s %s",Code,g_stcopcode[*pbyCodeBuf].szInstruction);
			//if (m_OPcodLength==1)		//��������	���⴦��
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
		pbyCodeBuf++;			//��ַȡ��һ���ֽ�
		m_OPcodLength--;		//����ָ��ȼ�һ  �൱�ڽ������������鳤�ȼ�1
}
//ƥ��Ĵ���
void engine::GetReg(
	UINT uOPertype,
	WCHAR Code[MAX_PATH])
{
	switch (uOPertype)		//ƥ��Ĵ�������
	{
	case _AL_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"al");break;	//���8bit�Ĵ���  ��ͬ
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
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ax");break;		//���16bit�Ĵ���  ��ͬ
	case _BX_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"bx");break;
	case _CX_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"cx");break;
	case _DX_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"dx");break;

	case _EAX_:
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"eax");break;		//���32bit�Ĵ���   ��ͬ
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
//����������
void engine::GetOperation(
	PBYTE &pCodeBuf,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	if(uOperation>=0x2000)		//�жϲ������Ƿ���Ҫ��MOD��
	{
		//������λ�Ĵ���ʱ
		
		GetReg(uOperation,Code);
		return;
	}
	/*printf("%02x ",*pCodeBuf);*/
	//��Ϊ�����ʱ
	UINT uOperType=uOperation & 0xFF00;		//��λ���� ��λ����  �����ж��Ƿ�Ϊ�Ĵ���

	if(uOperType==_E_||uOperType==_G_)		
	{
		if (!iscode)
		{
			RegionFlag = (PMODR_M)pCodeBuf++;	//ȡ������
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
//ƥ������_J_
void engine::GetType_J_(
	PBYTE &pCodeBuf,
	PMODR_M RegionFlag,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//��λ���� ��λ����  �����ж�������
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
//ƥ������_M_
void engine::GetType_O_(
	PBYTE &pCodeBuf,
	PMODR_M RegionFlag,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//��λ���� ��λ����  �����ж�������
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
//ƥ������_S_
void engine::GetType_S_(
	PBYTE &pCodeBuf,
	PMODR_M RegionFlag,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//��λ���� ��λ����  �����ж�������
	//int Size=getSize(byopcodeSize);
	switch (byopcodeSize)
	{
	case _w_:
		{
			swprintf_s(Code,MAX_PATH,L"%s %s",Code,L"ss");
		}
	}
}
//ƥ������_X_
void engine::GetType_X_(
	PBYTE &pCodeBuf,
	PMODR_M RegionFlag,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//��λ���� ��λ����  �����ж�������
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
//ƥ������_Y_
void engine::GetType_Y_(
	PBYTE &pCodeBuf,
	PMODR_M RegionFlag,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//��λ���� ��λ����  �����ж�������
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
//ƥ������_I_
void engine::GetType_I_(
	PBYTE &pCodeBuf,
	PMODR_M RegionFlag,
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//��λ���� ��λ����  �����ж�������
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
//ƥ��ǰ׺
void engine::MatePrefix2(
	PBYTE &pbyCodeBuf,	
	WCHAR Code[MAX_PATH],
	UINT uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//ȡ��λ
	UINT uOperType=uOperation & 0xFF00;		//ȡ��λ
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
//ƥ������_G_
void engine::GetType_G_(
	PBYTE		&pCodeBuf,
	PMODR_M		RegionFlag,
	WCHAR	    Code[MAX_PATH],
	UINT		uOperation)
{
	BYTE byopcodeSize=uOperation &0xff;		//��λ���� ��λ����  �����ж�������
	int Size=getSize(byopcodeSize);
	swprintf_s(Code,MAX_PATH,L"%s %s",Code,	
		g_szRM3[Size][RegionFlag->REG]);

	
}
//ƥ������_E_
void engine::GetType_E_(
	PBYTE		&pCodeBuf,	
	PMODR_M		RegionFlag,	
	WCHAR	    Code[MAX_PATH],	
	UINT		uOperation)
{
	wchar_t szSib[30];
	switch (RegionFlag->MOD)			//�����Զ�����ʵ�� ���Կ���ƥ�����  ��ͬ
	{
	case 0:			//MOD��1
		{
			if(RegionFlag->R_M==4)		//[--][--]
			{
				FindeSib(pCodeBuf,szSib,Code);
				break;
			}
			if(RegionFlag->R_M==5)		//������
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
			//����Ҫ�� �γ�Խ
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
			BYTE byopcodeSize=uOperation &0xff;		//��λλ���� ��λ����  �����ж�������
			int Size=getSize(byopcodeSize);
			swprintf_s(Code,MAX_PATH,L"%s %s",Code,	
				g_szRM3[Size][RegionFlag->R_M]);
		}			
		break;
	}
}
//sib����
void engine::FindeSib(
	PBYTE &pCodeBuf,
	wchar_t szSib[],
	WCHAR Code[MAX_PATH])
{
	//�ȴ���������� MOD
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
	//Scaled Index  ���Ƿ�Ϊnone
	if (SibFlag->INDEX!=4)
	{
		swprintf_s(szSib,30,L"[%s+%s",g_szSCALED[SibFlag->SS][SibFlag->INDEX],lpBase);
		swprintf_s(Code,MAX_PATH,L"%s %s",Code,szSib);
		pCodeBuf++;
		m_OPcodLength--;
		return;
	}
	swprintf_s(szSib,30,L"[%s",lpBase);			//��Ϊnone  ��Ϊ [*]
	swprintf_s(Code,MAX_PATH,L"%s %s",Code,szSib);
}

//��ȡ��ָ���С
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
	SetConsoleCursorInfo(hout,&Cui);//ȡ�����
	coord.X=2*x;
	coord.Y=y;

	SetConsoleTextAttribute(hout,wArr);
	SetConsoleCursorPosition(hout,coord);//���λ��
	wprintf_s(pszChar);
	SetConsoleTextAttribute(hout,7);
	//WriteConsoleInputA()
	//WriteConsoleOutputCharacter
}