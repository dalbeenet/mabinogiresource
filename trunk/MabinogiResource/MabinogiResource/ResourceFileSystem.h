#pragma once

#include "IResourceSet.h"


class CResourceFileSystem : public IResourceSet
{
protected:
	CResourceFileSystem(void);
public:
	virtual ~CResourceFileSystem(void);

	// ��һ��pack�ļ��д���
	static shared_ptr<IResourceSet> CreateResourceFileSystemFromFolder(LPCTSTR lpszPackFolder);

	// �ҵ�ָ��ȫ������Դ
	virtual int FindResourceIndex(LPCSTR lpszName);

	// ���һ����Դ
	virtual shared_ptr<IResource> GetResource(size_t index);

	// �����Դ����
	virtual size_t GetResourceCount();

protected:
	ResourceList m_Resources;
};
