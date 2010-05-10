#pragma once
#include "iresource.h"

#include <string>
#include <memory>
#include <vector>
#include "Win32File.h"

using namespace std;
using namespace std::tr1;

class CFileResource : public IResource
{
protected:
	CFileResource(void);
public:
	virtual ~CFileResource(void);

	static shared_ptr<IResource> CreateResourceFromFile(LPCTSTR lpszFile, LPCSTR lpszResourceName, size_t version);

	// ��ǰʵ���ȫ����Ϊ���·������ db/ss.xml
	virtual string GetName() ;

	// ���ؽ�ѹ�����ݣ�ÿ�η����µ�����
	virtual shared_ptr< vector<char> > GetDecompressedContent() ;

	// ���ؽ�ѹǰ���ݣ�ÿ�η����µ�����
	virtual shared_ptr< vector<char> > GetCompressedContent() ;

	// ����ѹ�����С
	virtual size_t GetCompressedSize() ;

	// ����ѹ��ǰ�Ĵ�С
	virtual size_t GetDecompressedSize() ;

	// ���ذ汾������Խ�󣬰汾Խ��
	virtual size_t GetVersion() ;

	// ���ش���ʱ��
	virtual FILETIME GetCreationTime() ;

	// ����������ʱ��
	virtual FILETIME GetLastAccessTime() ;

	// �������д��ʱ��
	virtual FILETIME GetLastWriteTime() ;

protected:
	shared_ptr< CWin32File > m_spFile;
	string m_name;
	size_t m_compressedSize;
	size_t m_decompressedSize;
	size_t m_version;
	FILETIME m_ftCreation;
	FILETIME m_ftLastAccess;
	FILETIME m_ftLastWrite;
};
