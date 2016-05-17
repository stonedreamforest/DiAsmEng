#pragma once
#include "tchar.h"
#include "stdlib.h"
#include <windows.h>
class data
{
public:
	data(void);
	~data(void);
public:
	void readData(BYTE * &opcodes,int& size ,char * filePath);
public:
	//ǰ׺
	int y;								//���� ���������ʽ
	int LPrefix	;						// ����ǰ׺				F0
	int OpSPrefix;						// �л���������Сǰ׺	66
	int AddSPrefix;						// �л���ַ��Сǰ׺		67
	int RepOpPrefixF2;					// �ظ�����ǰ׺			F2
	int RepOpPrefixF3;					// �ظ�����ǰ׺			F3
	int CsegPrefix2E;					// CS �γ�Խǰ׺		2E	
	int CsegPrefix3E;					// DS �γ�Խǰ׺		3E	
	int CsegPrefix26;					// ES �γ�Խǰ׺		26
	int CsegPrefix36;					// SS �γ�Խǰ׺		36	
	int CsegPrefix64;					// FS �γ�Խǰ׺		64	
	int CsegPrefix65;					// GS �γ�Խǰ׺		65
	bool iscode;
	char *filePath;						//��ȡ�ļ�·��
	
};



		   
//map��
typedef struct tagopcode
{
	wchar_t szInstruction[16];	    //ָ�����Ʋ�����
	unsigned int Operation1;		//��һ��������
	unsigned int Operation2;		//�ڶ���������
	unsigned int Operation3;		//������������
}opcode,*Popcode;
//ModR/M�ṹ����Ϣ
typedef struct _tagModR_M		//λ�����ɵ�λ���λ���δ���
{
	BYTE R_M :	3;				//RM��
	BYTE REG :	3;				//REG��
	BYTE MOD :  2;				//MOD��
}MODR_M,*PMODR_M;
//SIB�ṹ����Ϣ
typedef struct _tagSIB
{
	BYTE BASE  :	3;			//base	    ����
	BYTE INDEX :	3;			//index		����
	BYTE SS    :	2;			//scale		����
}SIB,*PSIB;

#define F_YELLOW   0x0002|0x0004        // ���

#define	_E_		0x500		//�Ĵ�����洢��ַ		r/m								
#define	_F_		0x600		//��־�Ĵ���			EFLAGS��32λ��/RFLAGS��64λ��
#define _G_		0x700		//�Ĵ���				reg   
#define _I_		0x800		//������				immediate
#define _Y_		0x900		//�ڴ��ַ				ES:rDI
#define _X_		0xA00		//�ڴ��ַ				DS:rSI
#define _S_		0xB00		//ModR/M��reg��Ϊ�μĴ���
#define _M_		0xC00		//ModR/M�ֽڿ��ܽ������ڴ������(��BOUND,LES,LDS,LSS,LFS,LGS,CMPXCHG8B)
#define _O_		0xD00		//û��ModR/M�ֽ�.��������ƫ�Ʊ�����Ϊ�ֻ�˫��(���ݵ�ַ��С���Ծ���).û��SIB�ֽ�.(��MOV(A0-A3))
							// 00104000   mov     al, byte ptr [00401000]
#define _J_		0xE00		//ָ���а���һ�����ƫ����������ָ��ָ��Ĵ���(��JMP(0E9),LOOP)
#define _A_		0xF00		//ֱ��Ѱַ:ָ��û��ModR/M�ֽڣ��������ĵ�ֱַ�ӱ�����ָ���У�û��SIB�ֽ�.(��far JMP(EA))

#define _b_		0x0			//8λ					byte							  
#define _w_		0x1			//16λ					word
#define _d_		0x2			//32λ					dword
#define _v_		0x3			//64λ �� 128λ			dword��dqword
#define _z_		0x4			//16λ �� 32λ ��64λ	word��dword��qwprd
#define _p_		0x5			//32λ,48λ����80λָ��,���ݲ�������С���Ծ���

#define _AL_	0x2000		//8λ�Ĵ���			AL
#define _BL_	0x3000		//8λ�Ĵ���			BL
#define _CL_	0x4000		//8λ�Ĵ���			CL
#define _DL_	0x5000		//8λ�Ĵ���			DL
#define	_AH_	0x5001		//8λ�Ĵ���			AH
#define	_CH_	0x500		//8λ�Ĵ���			CH
#define	_DH_	0x35000		//8λ�Ĵ���			DH
#define	_BH_	0x45000		//8λ�Ĵ���			BH

#define _AX_	0x6000		//16λ�Ĵ���		AX
#define _BX_	0x7000		//16λ�Ĵ���		BX
#define _CX_	0x8000		//16λ�Ĵ���		CX
#define _DX_	0x9000		//16λ�Ĵ���		DX

#define _EAX_	0xE000		//32λ�Ĵ���		EAX
#define _EBX_	0xE001		//32λ�Ĵ���		EBX
#define _ECX_	0xE002		//32λ�Ĵ���		ECX
#define _EDX_	0xE003		//32λ�Ĵ���		ECX
#define _ESI_	0xE004		//32λ�Ĵ���		ECX
#define _ESP_	0xE005		//32λ�Ĵ���		ECX
#define _EDI_	0xE006		//32λ�Ĵ���		ECX
#define _EBP_	0xE007		//32λ�Ĵ���		ECX


#define _ES_	0xA000		//�μĴ���			ES
#define _CS_	0xA001		//�μĴ���			CS
#define _DS_	0xA002		//�μĴ���			DS
#define _SS_	0xA003		//�μĴ���			SS



//1�ֽ�  opcode MAP��
const opcode g_stcopcode[256]={
	/*code��			ָ��				������1				������2				������3
	/* 00 */	{		TEXT("add"),		_E_ | _b_,			_G_ | _b_,			0			 },  //��λ�뱣��һ���ض���� 
	/* 01 */	{		TEXT("add"),		_E_	| _v_,			_G_ | _v_,			0			 },
	/* 02 */	{		TEXT("add"),		_G_ | _b_,			_E_ | _b_,			0			 },
	/* 03 */	{		TEXT("add"),		_G_ | _v_,			_E_ | _v_,			0			 },
	/* 04 */	{		TEXT("add"),		_AL_	 ,			_I_	| _b_,			0			 },
	/* 05 */	{		TEXT("add"),		_EAX_    ,			_I_ | _z_,			0			 },
	/* 06 */	{		TEXT("push"),		_ES_	 ,			0		 ,			0			 },
	/* 07 */	{		TEXT("pop"),		_ES_	 ,			0        ,			0			 },
	/* 08 */	{		TEXT("or"),			_E_ | _b_,			_G_ | _b_,			0			 },
	/* 09 */	{		TEXT("or"),			_E_	| _v_,			_G_ | _v_,			0			 },
	/* 0A */	{		TEXT("or"),			_G_ | _b_,			_E_ | _b_,			0			 },
	/* 0B */	{		TEXT("or"),			_G_ | _v_,			_E_ | _v_,			0			 },
	/* 0C */	{		TEXT("or"),			_AL_	 ,			_I_	| _b_,			0			 },
	/* 0D */	{		TEXT("or"),			_EAX_    ,			_I_ | _z_,			0			 },
	/* 0E */	{		TEXT("push"),		_CS_	 ,			0		 ,			0			 },
	/* 0F */	{		TEXT(""),			0		 ,			0		 ,			0			 },
																						 
	/* 10 */	{		TEXT("adc"),		_E_ | _b_,			_G_ | _b_,			0			 },
	/* 11 */	{		TEXT("adc"),		_E_	| _v_,			_G_ | _v_,			0			 },
	/* 12 */	{		TEXT("adc"),		_G_ | _b_,			_E_ | _b_,			0			 },
	/* 13 */	{		TEXT("adc"),		_G_ | _v_,			_E_ | _v_,			0			 },
	/* 14 */	{		TEXT("adc"),		_AL_	 ,			_I_	| _b_,			0			 },
	/* 15 */	{		TEXT("adc"),		_EAX_    ,			_I_ | _z_,			0			 },
	/* 16 */	{		TEXT("push"),		_SS_	 ,			0,					0			 },
	/* 17 */	{		TEXT("pop"),		_SS_	 ,			0,					0			 },
	/* 18 */	{		TEXT("sbb"),		_E_ | _b_,			_G_ | _b_,			0			 },
	/* 19 */	{		TEXT("sbb"),		_E_	| _v_,			_G_ | _v_,			0			 },
	/* 1A */	{		TEXT("sbb"),		_G_ | _b_,			_E_ | _b_,			0			 },
	/* 1B */	{		TEXT("sbb"),		_G_ | _v_,			_E_ | _v_,			0			 },
	/* 1C */	{		TEXT("sbb"),		_AL_	 ,			_I_	| _b_,			0			 },
	/* 1D */	{		TEXT("sbb"),		_EAX_    ,			_I_ | _z_,			0			 },
	/* 1E */	{		TEXT("push"),		_DS_	 ,			0,					0			 },
	/* 1F */	{		TEXT("pop"),		_DS_	 ,			0,					0			 },
																						 
	/* 20 */	{		TEXT("and"),		_E_ | _b_,			_G_ | _b_,			0			 },
	/* 21 */	{		TEXT("and"),		_E_	| _v_,			_G_ | _v_,			0			 },
	/* 22 */	{		TEXT("and"),		_G_ | _b_,			_E_ | _b_,			0			 },
	/* 23 */	{		TEXT("and"),		_G_ | _v_,			_E_ | _v_,			0			 },
	/* 24 */	{		TEXT("and"),		_AL_	 ,			_I_	| _b_,			0			 },
	/* 25 */	{		TEXT("and"),		_EAX_    ,			_I_ | _z_,			0			 },
	/* 26 */	{		TEXT("26:"),		0		 ,			0		 ,			0			 },
	/* 27 */	{		TEXT("daa"),		0		 ,			0		 ,			0			 },
	/* 18 */	{		TEXT("sub"),		_E_ | _b_,			_G_ | _b_,			0			 },
	/* 19 */	{		TEXT("sub"),		_E_	| _v_,			_G_ | _v_,			0			 },
	/* 1A */	{		TEXT("sub"),		_G_ | _b_,			_E_ | _b_,			0			 },
	/* 1B */	{		TEXT("sub"),		_G_ | _v_,			_E_ | _v_,			0			 },
	/* 1C */	{		TEXT("sub"),		_AL_	 ,			_I_	| _b_,			0			 },
	/* 1D */	{		TEXT("sub"),		_EAX_    ,			_I_ | _z_,			0			 },
	/* 2E */	{		TEXT("2e:"),		0		 ,			0		 ,			0			 },
	/* 2F */	{		TEXT("das"),		0		 ,			0		 ,			0			 },
																						 
	/* 30 */	{		TEXT("xor"),		_E_ | _b_,			_G_ | _b_,			0			 },
	/* 31 */	{		TEXT("xor"),		_E_	| _v_,			_G_ | _v_,			0			 },
	/* 32 */	{		TEXT("xor"),		_G_ | _b_,			_E_ | _b_,			0			 },
	/* 33 */	{		TEXT("xor"),		_G_ | _v_,			_E_ | _v_,			0			 },
	/* 34 */	{		TEXT("xor"),		_AL_	 ,			_I_	| _b_,			0			 },
	/* 35 */	{		TEXT("xor"),		_EAX_    ,			_I_ | _z_,			0			 },
	/* 36 */	{		TEXT("36:"),		0		 ,			0		 ,			0			 },
	/* 37 */	{		TEXT("aaa"),		0		 ,			0		 ,			0			 },
	/* 38 */	{		TEXT("cmp"),		_E_ | _b_,			_G_ | _b_,			0			 },
	/* 39 */	{		TEXT("cmp"),		_E_	| _v_,			_G_ | _v_,			0			 },
	/* 3A */	{		TEXT("cmp"),		_G_ | _b_,			_E_ | _b_,			0			 },
	/* 3B */	{		TEXT("cmp"),		_G_ | _v_,			_E_ | _v_,			0			 },
	/* 3C */	{		TEXT("cmp"),		_AL_	 ,			_I_	| _b_,			0			 },
	/* 3D */	{		TEXT("cmp"),		_EAX_    ,			_I_ | _z_,			0			 },
	/* 3E */	{		TEXT("3e:"),		0		 ,			0		 ,			0			 },
	/* 3F */	{		TEXT("aas"),		0		 ,			0		 ,			0			 },
																						 
	/* 40 */	{		TEXT("inc"),		_EAX_	 ,			0		 ,			0			 },
	/* 41 */	{		TEXT("inc"),		_ECX_	 ,			0		 ,			0			 },
	/* 42 */	{		TEXT("inc"),		_EDX_	 ,			0		 ,			0			 },
	/* 43 */	{		TEXT("inc"),		_EBX_	 ,			0		 ,			0			 },
	/* 44 */	{		TEXT("inc"),		_ESP_	 ,			0		 ,			0			 },
	/* 45 */	{		TEXT("inc"),		_EBP_	 ,			0		 ,			0			 },
	/* 46 */	{		TEXT("inc"),		_ESI_	 ,			0		 ,			0			 },
	/* 47 */	{		TEXT("inc"),		_EDI_	 ,			0		 ,			0			 },
	/* 48 */	{		TEXT("dec"),		_EAX_	 ,			0		 ,			0			 },
	/* 49 */	{		TEXT("dec"),		_ECX_	 ,			0		 ,			0			 },
	/* 4A */	{		TEXT("dec"),		_EDX_	 ,			0		 ,			0			 },
	/* 4B */	{		TEXT("dec"),		_EBX_	 ,			0		 ,			0			 },
	/* 4C */	{		TEXT("dec"),		_ESP_	 ,			0		 ,			0			 },
	/* 4D */	{		TEXT("dec"),		_EBP_	 ,			0		 ,			0			 },
	/* 4E */	{		TEXT("dec"),		_ESI_	 ,			0		 ,			0			 },
	/* 4F */	{		TEXT("dec"),		_EDI_	 ,			0		 ,			0			 },
																						 
	/* 50 */	{		TEXT("push"),		_EAX_	 ,			0		 ,			0			 },//ֻ������32λ������
	/* 51 */	{		TEXT("push"),		_ECX_	 ,			0		 ,			0			 },
	/* 52 */	{		TEXT("push"),		_EDX_	 ,			0		 ,			0			 },
	/* 53 */	{		TEXT("push"),		_EBX_	 ,			0		 ,			0			 },
	/* 54 */	{		TEXT("push"),		_ESP_	 ,			0		 ,			0			 },
	/* 55 */	{		TEXT("push"),		_EBP_	 ,			0		 ,			0			 },
	/* 56 */	{		TEXT("push"),		_ESI_	 ,			0		 ,			0			 },
	/* 57 */	{		TEXT("push"),		_EDI_	 ,			0		 ,			0			 },
	/* 58 */	{		TEXT("pop"),		_EAX_	 ,			0		 ,			0			 },
	/* 59 */	{		TEXT("pop"),		_ECX_	 ,			0		 ,			0			 },
	/* 5A */	{		TEXT("pop"),		_EDX_	 ,			0		 ,			0			 },
	/* 5B */	{		TEXT("pop"),		_EBX_	 ,			0		 ,			0			 },
	/* 5C */	{		TEXT("pop"),		_ESP_	 ,			0		 ,			0			 },
	/* 5D */	{		TEXT("pop"),		_EBP_	 ,			0		 ,			0			 },
	/* 5E */	{		TEXT("pop"),		_ESI_	 ,			0		 ,			0			 },
	/* 5F */	{		TEXT("pop"),		_EDI_	 ,			0		 ,			0			 },
																						 
	/* 60 */	{		TEXT("pusha"),		0		 ,			0		 ,			0			 },
	/* 61 */	{		TEXT("popa"),		0		 ,			0		 ,			0			 },
	/* 62 */	{		TEXT("bound"),		0		 ,			0		 ,			0			 },
	/* 63 */	{		TEXT("arpl"),		0		 ,			0		 ,			0			 },
	/* 64 */	{		TEXT("fs:"),		0		 ,			0		 ,			0			 },
	/* 65 */	{		TEXT("gs:"),		0		 ,			0		 ,			0			 },
	/* 66 */	{		TEXT("66:"),		0		 ,			0		 ,			0			 },
	/* 67 */	{		TEXT("67:"),		0		 ,			0		 ,			0			 },
	/* 68 */	{		TEXT("push"),		_I_ | _z_,			0		 ,			0	  		 },
	/* 69 */	{		TEXT("imul"),		_G_ | _v_,			_E_ | _v_,			_I_ | _z_	 },
	/* 6A */	{		TEXT("push"),		_I_ | _b_,			0		 ,			0			 },
	/* 6B */	{		TEXT("imul"),		_G_ | _v_,			_E_ | _v_,			_I_ | _b_	 },
	/* 6C */	{		TEXT("ins"),		_Y_ | _b_,			_DX_	 ,			0 			 },
	/* 6D */	{		TEXT("insd"),		_Y_ | _z_,			_DX_	 ,						 },
	/* 6E */	{		TEXT("outs"),		_DX_	 ,			_X_	| _b_,			0			 },
	/* 6F */	{		TEXT("outsd"),	    _DX_     ,			_X_ | _z_,			0			 },
												 
	/* 70 */	{		TEXT("jo"),			0		 ,			0		 ,			0			 },
	/* 71 */	{		TEXT("jno"),		0		 ,			0		 ,			0			 },
	/* 72 */	{		TEXT("jb"),			0		 ,			0		 ,			0			 },
	/* 73 */	{		TEXT("jnb"),		0		 ,			0		 ,			0			 },
	/* 74 */	{		TEXT("jz"),			0		 ,			0		 ,			0			 },
	/* 75 */	{		TEXT("jnz"),		0		 ,			0		 ,			0			 },
	/* 76 */	{		TEXT("jna"),		0		 ,			0		 ,			0			 },
	/* 77 */	{		TEXT("ja"),			0		 ,			0		 ,			0			 },
	/* 78 */	{		TEXT("js"),			0		 ,			0		 ,			0			 },
	/* 79 */	{		TEXT("jns"),		0		 ,			0		 ,			0			 },
	/* 7A */	{		TEXT("jp"),			0		 ,			0		 ,			0			 },
	/* 7B */	{		TEXT("jnp"),		0		 ,			0		 ,			0			 },
	/* 7C */	{		TEXT("jl"),			0		 ,			0		 ,			0			 },
	/* 7D */	{		TEXT("jge"),		0		 ,			0		 ,			0			 },
	/* 7E */	{		TEXT("jle"),		0		 ,			0		 ,			0			 },
	/* 7F */	{		TEXT("jg"),			0		 ,			0		 ,			0			 },
												 
	/* 80 */	{		TEXT("Grp1"),		0		 ,			0		 ,			0			 },
	/* 81 */	{		TEXT("Grp1"),		0		 ,			0		 ,			0			 },
	/* 82 */	{		TEXT("Grp1"),		0		 ,			0		 ,			0			 },
	/* 83 */	{		TEXT("Grp1"),		0		 ,			0		 ,			0			 },
	/* 84 */	{		TEXT("test"),		_E_ | _b_,			_G_ | _b_,			0			 },
	/* 85 */	{		TEXT("test"),		_E_	| _v_,			_G_ | _v_,			0			 },
	/* 86 */	{		TEXT("xchg"),		_E_ | _b_,			_G_ | _b_,			0			 },
	/* 87 */	{		TEXT("xchg"),		_E_	| _v_,			_G_ | _v_,			0			 },
	/* 88 */	{		TEXT("mov"),		_E_ | _b_,			_G_ | _b_,			0			 },
	/* 89 */	{		TEXT("mov"),		_E_	| _v_,			_G_ | _v_,			0			 },
	/* 8A */	{		TEXT("mov"),		_G_ | _b_,			_E_ | _b_,			0			 },
	/* 8B */	{		TEXT("mov"),		_G_ | _v_,			_E_ | _v_,			0			 },
	/* 8C */	{		TEXT("mov"),		_E_ | _v_,			_S_ | _w_,			0			 },
	/* 8D */	{		TEXT("lea"),		_G_ | _v_,			_M_		 ,			0			 },
	/* 8E */	{		TEXT("mov"),		_S_ | _w_,			_E_ | _w_,			0	 		 },
	/* 8F */	{		TEXT("pop"),		_E_ | _v_,			0		 ,			0			 },

	/* 90 */	{		TEXT("nop"),		_EAX_	 ,			0		 ,			0			},
	/* 91 */	{		TEXT("xchg"),		_ECX_	 ,			0		 ,			0			},
	/* 92 */	{		TEXT("xchg"),		_EDX_	 ,			0		 ,			0			},
	/* 93 */	{		TEXT("xchg"),		_EBX_	 ,			0		 ,			0			},
	/* 94 */	{		TEXT("xchg"),		_ESP_	 ,			0		 ,			0			},
	/* 95 */	{		TEXT("xchg"),		_EBP_	 ,			0		 ,			0			},
	/* 96 */	{		TEXT("xchg"),		_ESI_	 ,			0		 ,			0			},
	/* 97 */	{		TEXT("xchg"),		_EDI_	 ,			0		 ,			0			},
	/* 98 */	{		TEXT("cwde"),		0		 ,			0		 ,			0			},
	/* 99 */	{		TEXT("cdq"),		0		 ,			0		 ,			0			},
	/* 9A */	{		TEXT("call"),		0		 ,			0		 ,			0			},
	/* 9B */	{		TEXT("wait"),		0		 ,			0		 ,			0			},
	/* 9C */	{		TEXT("pushfd"),		0		 ,			0		 ,			0			},
	/* 9D */	{		TEXT("popfd"),		0		 ,			0		 ,			0			},
	/* 9E */	{		TEXT("sahf"),		0		 ,			0		 ,			0			},
	/* 9F */	{		TEXT("lahf"),		0		 ,			0		 ,			0			},

	/* A0 */	{		TEXT("mov"),		_AL_	 ,			_O_ | _b_,			0			},
	/* A1 */	{		TEXT("mov"),		_EAX_	 ,			_O_ | _v_,			0			},
	/* A2 */	{		TEXT("mov"),		_O_ | _b_,			_AL_	 ,			0			},
	/* A3 */	{		TEXT("mov"),		_O_ | _v_,			_EAX_	 ,			0			},
	/* A4 */	{		TEXT("movs"),		_Y_	| _b_,			_X_ | _b_,			0			},
	/* A5 */	{		TEXT("movsd"),		_Y_	| _v_,			_X_ | _v_,			0			},
	/* A6 */	{		TEXT("cmps"),		_X_	| _b_,			_Y_ | _b_,			0			},
	/* A7 */	{		TEXT("cmpsd"),		_X_	| _v_,			_Y_ | _v_,			0			},
	/* A8 */	{		TEXT("test"),		_AL_	 ,			_I_ | _b_,			0			},
	/* A9 */	{		TEXT("test"),		_EAX_	 ,			_I_ | _z_,			0			},
	/* AA */	{		TEXT("stos"),		_Y_ | _b_,			_AL_	 ,			0			},
	/* AB */	{		TEXT("stosd"),		_Y_ | _v_,			_EAX_	 ,			0			},
	/* AC */	{		TEXT("lods"),		_AL_	 ,			_X_ | _b_,			0			},
	/* AD */	{		TEXT("lodsd"),		_EAX_	 ,			_X_ | _v_,			0			},
	/* AE */	{		TEXT("scas"),		_AL_	 ,			_Y_ | _b_,			0			},
	/* AF */	{		TEXT("scasd"),		_EAX_	 ,			_Y_ | _v_,			0			},

	/* B0 */	{		TEXT("mov"),		_AL_	 ,			_I_ | _b_,			0			},
	/* B1 */	{		TEXT("mov"),		_CL_	 ,			_I_ | _b_,			0	 		},
	/* B2 */	{		TEXT("mov"),		_DL_	 ,			_I_ | _b_,			0	 		},
	/* B3 */	{		TEXT("mov"),		_BL_	 ,			_I_ | _b_,			0	 		},
	/* B4 */	{		TEXT("mov"),		_AH_	 ,			_I_ | _b_,			0			},
	/* B5 */	{		TEXT("mov"),		_CH_	 ,			_I_ | _b_,			0	 		},
	/* B6 */	{		TEXT("mov"),		_DH_	 ,			_I_ | _b_,			0	 		},
	/* B7 */	{		TEXT("mov"),		_BH_	 ,			_I_ | _b_,			0	 		},
	/* B8 */	{		TEXT("mov"),		_EAX_	 ,			_I_ | _v_,			0			},
	/* B9 */	{		TEXT("mov"),		_ECX_	 ,			_I_ | _v_,			0			},
	/* BA */	{		TEXT("mov"),		_EDX_	 ,			_I_ | _v_,			0			},
	/* BB */	{		TEXT("mov"),		_EBX_	 ,			_I_ | _v_,			0			},
	/* BC */	{		TEXT("mov"),		_ESP_	 ,			_I_ | _v_,			0			},
	/* BD */	{		TEXT("mov"),		_EBP_	 ,			_I_ | _v_,			0			},
	/* BE */	{		TEXT("mov"),		_ESI_	 ,			_I_ | _v_,			0			},
	/* BF */	{		TEXT("mov"),		_EDI_	 ,			_I_ | _v_,			0			},

	/* C0 */	{		TEXT("Grp2"),		0		 ,			0		 ,			0	 		},
	/* C1 */	{		TEXT("Grp2"),		0		 ,			0		 ,			0	 		},
	/* C2 */	{		TEXT("retn"),		_I_ | _w_,			0		 ,			0			},
	/* C3 */	{		TEXT("retn"),		0		 ,			0		 ,			0	 		},
	/* C4 */	{		TEXT("les"),		_G_ | _z_,			_M_ |_p_ ,			0			},
	/* C5 */	{		TEXT("lds"),		_G_ | _z_,			_M_ |_p_ ,			0			},
	/* C6 */	{		TEXT(""),			0		 ,			0		 ,			0	 		},
	/* C7 */	{		TEXT(""),			0		 ,			0		 ,			0	 		},
	/* C8 */	{		TEXT("enter"),		_I_ | _w_,			_I_ | _b_,			0			},
	/* C9 */	{		TEXT("leave"),		0		 ,			0		 ,			0	 		},
	/* CA */	{		TEXT("retf"),		_I_ | _w_,			0		 ,			0			},
	/* CB */	{		TEXT("retf"),		0		 ,			0		 ,			0	 		},
	/* CC */	{		TEXT("int3"),		0		 ,			0		 ,			0	 		},
	/* CD */	{		TEXT("int"),		_I_ | _b_,			0		 ,			0			},
	/* CE */	{		TEXT("into"),		0		 ,			0		 ,			0	 		},
	/* CF */	{		TEXT("iretd"),		0		 ,			0		 ,			0	 		},

	/* D0 */	{		TEXT("Grp2"),		0		 ,			0		 ,			0	 		},
	/* D1 */	{		TEXT("Grp2"),		0		 ,			0		 ,			0	 		},
	/* D2 */	{		TEXT("Grp2"),		0		 ,			0		 ,			0	 		},
	/* D3 */	{		TEXT("Grp2"),		0		 ,			0		 ,			0	 		},
	/* D4 */	{		TEXT("aam"),		_I_ | _b_,			0		 ,			0	 		},
	/* D5 */	{		TEXT("aad"),		_I_ | _b_,			0		 ,			0	 		},
	/* D6 */	{		TEXT("salc"),		0		 ,			0		 ,			0	 		},
	/* D7 */	{		TEXT("xlat"),		0		 ,			0		 ,			0	 		},
	/* D8 */	{		TEXT(""),			0		 ,			0		 ,			0	 		},//ESC (Escape to coprocessor instruction set)
	/* D9 */	{		TEXT(""),			0		 ,			0		 ,			0	 		},//     ȥЭ����ָ�����
	/* DA */	{		TEXT(""),			0		 ,			0		 ,			0	 		},
	/* DB */	{		TEXT(""),			0		 ,			0		 ,			0	 		},
	/* DC */	{		TEXT(""),			0		 ,			0		 ,			0			},
	/* DD */	{		TEXT(""),			0		 ,			0		 ,			0	 		},
	/* DE */	{		TEXT(""),			0		 ,			0		 ,			0			},
	/* DF */	{		TEXT(""),			0		 ,			0		 ,			0			},

	/* E0 */	{		TEXT("loopnz"),		_J_ | _b_,			0		 ,			0			},
	/* E1 */	{		TEXT("loopz"),		_J_ | _b_,			0		 ,			0			},
	/* E2 */	{		TEXT("loop"),		_J_ | _b_,			0		 ,			0			},
	/* E3 */	{		TEXT(""),			0		 ,			0		 ,			0			},
	/* E4 */	{		TEXT("in"),			_AL_	 ,			_I_ | _b_,			0			},
	/* E5 */	{		TEXT("in"),			_EAX_	 ,			_I_ | _b_,			0			},
	/* E6 */	{		TEXT("out"),		_I_ | _b_,			_AL_	 ,			0			},
	/* E7 */	{		TEXT("out"),		_I_ | _b_,			_EAX_	 ,			0			},
	/* E8 */	{		TEXT("call"),		_J_ | _z_,			0		 ,			0			},
	/* E9 */	{		TEXT("jmp"),		_J_ | _z_,			0		 ,			0			},
	/* EA */	{		TEXT("jmp"),		_A_ | _p_,			0		 ,			0			},
	/* EB */	{		TEXT("jmp"),		_J_ | _b_,			0		 ,			0			},
	/* EC */	{		TEXT("in"),			_AL_	 ,			_DX_	 ,			0			},
	/* ED */	{		TEXT("in"),			_EAX_	 ,			_DX_	 ,			0			},
	/* EE */	{		TEXT("out"),		_DX_	 ,			_AL_	 ,			0			},
	/* EF */	{		TEXT("out"),		_DX_	 ,			_EAX_	 ,			0			},

	/* F0 */	{		TEXT("lock:"),		0		 ,			0		 ,			0			},
	/* F1 */	{		TEXT("int1"),		0		 ,			0		 ,			0			},
	/* F2 */	{		TEXT("repne:"),		0		 ,			0		 ,			0			},
	/* F3 */	{		TEXT("rep:"),		0		 ,			0		 ,			0			},
	/* F4 */	{		TEXT("hlt"),		0		 ,			0		 ,			0			},
	/* F5 */	{		TEXT("cmc"),		0		 ,			0		 ,			0			},
	/* F6 */	{		TEXT("Grp3"),		0		 ,			0		 ,			0			},
	/* F7 */	{		TEXT("Grp3"),		0		 ,			0		 ,			0			},
	/* F8 */	{		TEXT("clc"),		0		 ,			0		 ,			0			},
	/* F9 */	{		TEXT("stc"),		0		 ,			0		 ,			0			},
	/* FA */	{		TEXT("cli"),		0		 ,			0		 ,			0			},
	/* FB */	{		TEXT("sti"),		0		 ,			0		 ,			0			},
	/* FC */	{		TEXT("cld"),		0		 ,			0		 ,			0			},
	/* FD */	{		TEXT("std"),		0		 ,			0		 ,			0			},
	/* FE */	{		TEXT("Grp4"),		0		 ,			0		 ,			0			},
	/* FF */	{		TEXT("Grp5"),		0		 ,			0		 ,			0			}
};



/*                     ModR/M ��                             */
const WCHAR g_szRM[3][8][8]=	
{	{   TEXT("EAX"),			TEXT("ECX"),			TEXT("EDX"),			TEXT("EBX"),			TEXT("[-][-]"),			TEXT("")	,		TEXT("ESI"),				TEXT("EDI")},
	{   TEXT("EAX"),			TEXT("ECX"),			TEXT("EDX"),			TEXT("EBX"),			TEXT("[-][-]"),			TEXT("EBP")	,		TEXT("ESI"),				TEXT("EDI")},
	{   TEXT("EAX"),			TEXT("ECX"),			TEXT("EDX"),			TEXT("EBX"),			TEXT("[-][-]"),			TEXT("EBP")	,		TEXT("ESI"),				TEXT("EDI")}
};

// R/M				
const WCHAR g_szRM3[5][8][6]={
	{	TEXT("al"),		TEXT("cl"),		TEXT("dl"),		TEXT("bl"),		TEXT("ah"),		TEXT("ch"),		TEXT("dh"),		TEXT("bh")	},		//	8REG
	{	TEXT("ax"),		TEXT("cx"),		TEXT("dx"),		TEXT("bx"),		TEXT("sp"),		TEXT("bp"),		TEXT("si"),		TEXT("di")	},		//	16REG
	{	TEXT("eax"),	TEXT("ecx"),	TEXT("edx"),	TEXT("ebx"),	TEXT("esp"),	TEXT("ebp"),	TEXT("esi"),	TEXT("edi")	},		//	3REG
	{	TEXT("mm0"),	TEXT("mm1"),	TEXT("mm2"),	TEXT("mm3"),	TEXT("mm4"),	TEXT("mm5"),	TEXT("mm6"),	TEXT("mm7")	},		
	{	TEXT("xmm0"),	TEXT("xmm1"),	TEXT("xmm2"),	TEXT("xmm3"),	TEXT("xmm4"),	TEXT("xmm5"),	TEXT("xmm6"),	TEXT("xmm7")}
};
// Reg 
const WCHAR g_szReg[5][8][6]={
	{	TEXT("al"),		TEXT("cl"),		TEXT("dl"),		TEXT("bl"),		TEXT("ah"),		TEXT("ch"),		TEXT("dh"),		TEXT("bh")	},		//	8REG
	{	TEXT("ax"),		TEXT("cx"),		TEXT("dx"),		TEXT("bx"),		TEXT("sp"),		TEXT("bp"),		TEXT("si"),		TEXT("di")	},		//	16REG
	{	TEXT("eax"),	TEXT("ecx"),	TEXT("edx"),	TEXT("ebx"),	TEXT("esp"),	TEXT("ebp"),	TEXT("esi"),	TEXT("edi")	},		//	3REG
	{	TEXT("mm0"),	TEXT("mm1"),	TEXT("mm2"),	TEXT("mm3"),	TEXT("mm4"),	TEXT("mm5"),	TEXT("mm6"),	TEXT("mm7")	},		
	{	TEXT("xmm0"),	TEXT("xmm1"),	TEXT("xmm2"),	TEXT("xmm3"),	TEXT("xmm4"),	TEXT("xmm5"),	TEXT("xmm6"),	TEXT("xmm7")}
};


/*								SIB��							*/

const WCHAR g_szBASE[8][4]={ L"EAX",L"ECX",L"EDX",L"EBX",L"ESP",L"[*]",L"ESI",L"EDI" };//Reg32

//SIB��
const WCHAR g_szSCALED[4][8][8]={
	{   L"EAX",		L"ECX",	    L"EDX",		L"EBX",		L"none",	L"EBP",		L"ESI",		L"EDI"	  },
	{	L"EAX*2",	L"ECX*2",	L"EDX*2",	L"EBX*2",	L"none",	L"EBP*2",	L"ESI*2",	L"EDI*2"  },
	{	L"EAX*4",	L"ECX*4",	L"EDX*4",	L"EBX*4",	L"none",	L"EBP*4",	L"ESI*4",	L"EDI*4"  },
	{	L"EAX*8",	L"ECX*8",	L"EDX*8",	L"EBX*8",	L"none",	L"EBP*8",	L"ESI*8",	L"EDI*8"  }
};

/*								Grp��							*/
const WCHAR g_Grp[5][8][8]=
{
	{	L"add",		L"or",		L"adc",		L"sbb",		L"and",		L"sub",		L"xor",		L"cmp"	},
	{	L"rol",		L"ror",		L"rcl",		L"rcr",		L"shl",		L"shr",		L"",		L"sar"	},
	{	L"test",	L"",		L"not",		L"neg",		L"mul",		L"imul",	L"div",		L"idiv"	},
	{	L"inc",		L"dec",																			},
	{	L"inc",		L"dec",		L"calln",	L"callf",	L"jmpn",	L"jmpf",	L"push"				}
};