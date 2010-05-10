#pragma once

#include "IResource.h"

class CUtility
{
public:
	CUtility(void);
	~CUtility(void);

	// 二分查找已排序资源，找不到返回-1
	static int BinaryFindResourceIndex(ResourceList & resList, LPCSTR lpszName);

	// 顺序查找资源，找不到返回-1
	static int FindResourceIndex(ResourceList & resList, LPCSTR lpszName);

	// 加密一段字节
	static void Encrypt(shared_ptr< vector<char> > spBuffer, size_t seed);
	
	// 解密一段字节
	static void Decrypt(shared_ptr< vector<char> > spBuffer, size_t seed);
};
