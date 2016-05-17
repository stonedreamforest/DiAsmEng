// disassemb.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	BYTE *OPcode;
	data obj;
	int size;
	obj.readData(OPcode,size,obj.filePath);
	engine index(size);
	index.DisassemblyEngine(OPcode);
	return 0;
}

