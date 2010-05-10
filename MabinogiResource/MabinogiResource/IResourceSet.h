#pragma once

#include "IResource.h"
#include <memory>

using namespace std::tr1;

class IResourceSet
{
public:

	IResourceSet(void){}

	virtual ~IResourceSet(void){}

	// 找到指定全名的资源
	virtual int FindResourceIndex(LPCSTR lpszName) = 0;

	// 获得一个资源
	virtual shared_ptr<IResource> GetResource(size_t index) = 0;

	// 获得资源总数
	virtual size_t GetResourceCount() = 0;

};
