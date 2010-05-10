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
	// 阻止直接的实例化
	CPackResourceSet(void);
public:
	virtual ~CPackResourceSet(void);

	// 从一个pack文件创建资源集
	static shared_ptr<IResourceSet> CreateResourceSetFromFile(LPCTSTR lpszPackFile);

	static void PackResources( vector<shared_ptr<IResource> > & resources, size_t version, LPCTSTR lpszPackFile );

	// 找到指定全名的资源
	virtual int FindResourceIndex(LPCSTR lpszName);

	// 获得一个资源
	virtual shared_ptr<IResource> GetResource(size_t index);

	// 获得资源总数
	virtual size_t GetResourceCount();

protected:
	ResourceList m_Resources;
};
