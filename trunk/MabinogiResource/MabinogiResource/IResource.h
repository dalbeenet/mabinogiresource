#pragma once

#include "IObject.h"

class IResource : public IObject
{
public:

	IResource(void){}

	virtual ~IResource(void){}

	// ��ǰʵ���ȫ����Ϊ���·������ db/ss.xml
	virtual LPCSTR GetName() = 0;

	// ���ؽ�ѹ�����ݣ�δ���ܣ���ÿ�η����µ�����
	virtual size_t GetDecompressedContent(char * pBuffer, size_t size) = 0;

	// ���ؽ�ѹǰ���ݣ�δ���ܣ���ÿ�η����µ�����
	virtual size_t GetCompressedContent(char * pBuffer, size_t size) = 0;

	// ����ѹ�����С
	virtual size_t GetCompressedSize() = 0;

	// ����ѹ��ǰ�Ĵ�С
	virtual size_t GetDecompressedSize() = 0;

	// ���ذ汾������Խ�󣬰汾Խ��
	virtual size_t GetVersion() = 0;

	// ���ش���ʱ��
	virtual FILETIME GetCreationTime() = 0;

	// ����������ʱ��
	virtual FILETIME GetLastAccessTime() = 0;

	// �������д��ʱ��
	virtual FILETIME GetLastWriteTime() = 0;

	// ���ļ�����һ����Դ��
	static IResource * CreateResourceFromFile(LPCTSTR lpszFile, LPCSTR lpszResourceName, size_t version);
};
