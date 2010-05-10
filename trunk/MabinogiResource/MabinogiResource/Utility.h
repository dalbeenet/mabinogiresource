#pragma once

#include "IResource.h"

class CUtility
{
public:
	CUtility(void);
	~CUtility(void);

	// ���ֲ�����������Դ���Ҳ�������-1
	static int BinaryFindResourceIndex(ResourceList & resList, LPCSTR lpszName);

	// ˳�������Դ���Ҳ�������-1
	static int FindResourceIndex(ResourceList & resList, LPCSTR lpszName);

	// ����һ���ֽ�
	static void Encrypt(shared_ptr< vector<char> > spBuffer, size_t seed);
	
	// ����һ���ֽ�
	static void Decrypt(shared_ptr< vector<char> > spBuffer, size_t seed);
};
