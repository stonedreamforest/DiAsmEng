#pragma once
#include "engine.h"
class engine:public data
{
public:
	engine(int n);
	~engine(void);
public:
	int m_OPcodLength;			//操作码个数
	PMODR_M RegionFlag ;		//域标记
	PSIB	SibFlag;			//sib标记
	
public:
	void DisassemblyEngine(PBYTE pbyCodeBuf);										//反汇编引擎
	int	 getSize(BYTE byopcodeSize);												//获取该指令大小
	
	void GetInstruction(PBYTE &pbyCodeBuf,	WCHAR Code[MAX_PATH]);					//获取操作码
	void GetReg(UINT uOPertype,	WCHAR Code[MAX_PATH]);								//匹配寄存器
	void GetOperation(PBYTE &pCodeBuf,	WCHAR Code[MAX_PATH],	UINT uOperation);	//解析操作数
	void GetPrefix(PBYTE &pbyCodeBuf,	WCHAR Code[MAX_PATH]);						//获取前缀
	void MatePrefix1(PBYTE &pbyCodeBuf,	WCHAR Code[MAX_PATH]);						//匹配前缀1
	void MatePrefix2(PBYTE &pbyCodeBuf,	WCHAR Code[MAX_PATH],UINT uOperation);		//匹配前缀2
	void FindeSib(PBYTE &pCodeBuf,wchar_t szSib[],WCHAR Code[MAX_PATH]);

	void jxx(PBYTE &pbyCodeBuf,	WCHAR Code[MAX_PATH],UINT uOperation);								//跳转指令

	void GetType_E_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//匹配类型
	void GetType_G_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//匹配类型
	void GetType_I_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//匹配类型
	void GetType_Y_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//匹配类型
	void GetType_X_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//匹配类型
	void GetType_S_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//匹配类型
	void GetType_O_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//匹配类型
	void GetType_J_(PBYTE &pCodeBuf,PMODR_M RegionFlag,WCHAR Code[MAX_PATH],UINT uOperation);	//匹配类型

	void  readData(BYTE * &opcodes,int& size ,char * filePath);									//读取操作码函数
	void  CursorPosition(int x,int y,wchar_t *pszChar,WORD wArr);

};

