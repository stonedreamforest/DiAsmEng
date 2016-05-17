#pragma once
#include "engine.h"
class engine:public data
{
public:
	engine(int n);
	~engine(void);
public:
	int m_OPcodLength;			//���������
	PMODR_M RegionFlag ;		//����
	PSIB	SibFlag;			//sib���
	
public:
	void DisassemblyEngine(PBYTE pbyCodeBuf);										//���������
	int	 getSize(BYTE byopcodeSize);												//��ȡ��ָ���С
	
	void GetInstruction(PBYTE &pbyCodeBuf,	WCHAR Code[MAX_PATH]);					//��ȡ������
	void GetReg(UINT uOPertype,	WCHAR Code[MAX_PATH]);								//ƥ��Ĵ���
	void GetOperation(PBYTE &pCodeBuf,	WCHAR Code[MAX_PATH],	UINT uOperation);	//����������
	void GetPrefix(PBYTE &pbyCodeBuf,	WCHAR Code[MAX_PATH]);						//��ȡǰ׺
	void MatePrefix1(PBYTE &pbyCodeBuf,	WCHAR Code[MAX_PATH]);						//ƥ��ǰ׺1
	void MatePrefix2(PBYTE &pbyCodeBuf,	WCHAR Code[MAX_PATH],UINT uOperation);		//ƥ��ǰ׺2
	void FindeSib(PBYTE &pCodeBuf,wchar_t szSib[],WCHAR Code[MAX_PATH]);

	void jxx(PBYTE &pbyCodeBuf,	WCHAR Code[MAX_PATH],UINT uOperation);								//��תָ��

	void GetType_E_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//ƥ������
	void GetType_G_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//ƥ������
	void GetType_I_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//ƥ������
	void GetType_Y_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//ƥ������
	void GetType_X_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//ƥ������
	void GetType_S_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//ƥ������
	void GetType_O_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//ƥ������
	void GetType_J_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//ƥ������

	void  readData(BYTE * &opcodes,int& size ,char * filePath);									//��ȡ�����뺯��
	void  CursorPosition(int x,int y,wchar_t *pszChar,WORD wArr);

};

