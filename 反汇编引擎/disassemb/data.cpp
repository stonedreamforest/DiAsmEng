#include "stdafx.h"
#include "data.h"


data::data(void)
{
	filePath="1.txt";					//��ȡ����·��
	 y = 0;								//���� ���������ʽ
}


data::~data(void)
{
}
void  data::readData(BYTE * &opcodes,int& size ,char * filePath)
{
	FILE *pFile;
	if (0 == fopen_s(&pFile, filePath, "rb"))
	{		
		fseek(pFile, 0, SEEK_END);
		int file_len = ftell(pFile);
		size = file_len/3+1;
		fseek(pFile, 0, SEEK_SET);
		opcodes = new BYTE[size+3];
		BYTE* temp = opcodes;
		//fread(opcodes, file_len, 1, pFile);
		for (int i = 0;i<size;i++)
		{
			fscanf_s(pFile, "%x", temp++);
		}
		fclose(pFile);
		pFile = NULL;
	}

}