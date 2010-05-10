#pragma once

#include <string>
#include <vector>
#include <memory>

using namespace std;
using namespace std::tr1;

class IResource
{
public:

	IResource(void){}

	virtual ~IResource(void){}

	// ��ǰʵ���ȫ����Ϊ���·������ db/ss.xml
	virtual string GetName() = 0;

	// ���ؽ�ѹ�����ݣ�δ���ܣ���ÿ�η����µ�����
	virtual shared_ptr< vector<char> > GetDecompressedContent() = 0;


	// ���ؽ�ѹǰ���ݣ�δ���ܣ���ÿ�η����µ�����
	virtual shared_ptr< vector<char> > GetCompressedContent() = 0;

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
};

typedef vector<shared_ptr<IResource> > ResourceList;
