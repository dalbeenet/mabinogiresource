#pragma once

#include "IResourceSet.h"


class CResourceFileSystem : public IResourceSet
{
protected:
	CResourceFileSystem(void);
public:
	virtual ~CResourceFileSystem(void);

	// 从一个pack文件夹创建
	static shared_ptr<IResourceSet> CreateResourceFileSystemFromFolder(LPCTSTR lpszPackFolder);

	// 找到指定全名的资源
	virtual int FindResourceIndex(LPCSTR lpszName);

	// 获得一个资源
	virtual shared_ptr<IResource> GetResource(size_t index);

	// 获得资源总数
	virtual size_t GetResourceCount();

protected:
	ResourceList m_Resources;
};
