#pragma once
#include "iresource.h"

#include "types.h"

class CWin32File;
class CPackResource : public IResource
{
public:
	CPackResource(string name, shared_ptr<CWin32File> spFile, ITEM_INFO * pInfo);
	virtual ~CPackResource(void);

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
	string m_name;
	shared_ptr<CWin32File> m_spFile;
	ITEM_INFO m_info;
};
