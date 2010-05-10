#pragma once

#include "IResource.h"
#include <memory>

using namespace std::tr1;

class IResourceSet
{
public:

	IResourceSet(void){}

	virtual ~IResourceSet(void){}

	// �ҵ�ָ��ȫ������Դ
	virtual int FindResourceIndex(LPCSTR lpszName) = 0;

	// ���һ����Դ
	virtual shared_ptr<IResource> GetResource(size_t index) = 0;

	// �����Դ����
	virtual size_t GetResourceCount() = 0;

};
