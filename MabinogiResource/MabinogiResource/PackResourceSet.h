#pragma once
#include "iresourceset.h"

#include <memory>
#include <vector>
#include <string>
#include <map>

using namespace std;
using namespace std::tr1;

class CPackResourceSet : public IResourceSet
{
protected:
	// ��ֱֹ�ӵ�ʵ����
	CPackResourceSet(void);
public:
	virtual ~CPackResourceSet(void);

	// ��һ��pack�ļ�������Դ��
	static shared_ptr<IResourceSet> CreateResourceSetFromFile(LPCTSTR lpszPackFile);

	static void PackResources( vector<shared_ptr<IResource> > & resources, size_t version, LPCTSTR lpszPackFile );

	// �ҵ�ָ��ȫ������Դ
	virtual int FindResourceIndex(LPCSTR lpszName);

	// ���һ����Դ
	virtual shared_ptr<IResource> GetResource(size_t index);

	// �����Դ����
	virtual size_t GetResourceCount();

protected:
	ResourceList m_Resources;
};
