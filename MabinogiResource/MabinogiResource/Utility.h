#pragma once

#include "IResource.h"
#include <memory>
#include <vector>

using namespace std;
using namespace std::tr1;

class CUtility
{
public:
	CUtility(void);
	~CUtility(void);

	// ���ֲ�����������Դ���Ҳ�������-1
	static int BinaryFindResourceIndex(vector<shared_ptr<IResource>> & resList, LPCSTR lpszName);

	// ˳�������Դ���Ҳ�������-1
	static int FindResourceIndex(vector<shared_ptr<IResource>> & resList, LPCSTR lpszName);

	// ����һ���ֽ�
	static void Encrypt(char * pBuffer, size_t size, size_t seed);
	
	// ����һ���ֽ�
	static void Decrypt(char * pBuffer, size_t size, size_t seed);

	static bool ZlibUncompress (void * dest, unsigned long * destLen,
		const void * source, unsigned long sourceLen);

	static bool ZlibCompress (void * dest, unsigned long * destLen,
		const void * source, unsigned long sourceLen);
};
