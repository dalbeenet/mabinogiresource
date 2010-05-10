#include "StdAfx.h"
#include "Utility.h"

#include "MersenneTwister.h"

CUtility::CUtility(void)
{
}

CUtility::~CUtility(void)
{
}

int CUtility::FindResourceIndex( ResourceList & resList, LPCSTR lpszName )
{
	for (size_t i = 0;i < resList.size();i++)
	{
		if (resList.at(i)->GetName() == lpszName)
		{
			return i;
		}
	}

	return -1;
}

int CUtility::BinaryFindResourceIndex( ResourceList & resList, LPCSTR lpszName )
{
	size_t begin = 0, end = resList.size() - 1;
	while (begin <= end)
	{
		int middle = (end - begin) / 2 + begin;
		shared_ptr<IResource> spResrouce = resList.at(middle);
		int result = spResrouce->GetName().compare(lpszName);

		if (result == 0)
		{
			return middle;
		}
		else if (result > 0)
		{
			begin = middle + 1;
		}
		else
		{
			end = middle - 1;
		}

	}

	return -1;
}

void CUtility::Encrypt(shared_ptr< vector<char> > spBuffer, size_t seed )
{
	// º”√‹
	CMersenneTwister mt;
	unsigned long rseed = (seed << 7) ^ 0xA9C36DE1;
	mt.init_genrand(rseed);
	for (size_t i = 0; i < spBuffer->size();i++)
	{
		spBuffer->at(i) = (char)(spBuffer->at(i)  ^ mt.genrand_int32());
	}
}

void CUtility::Decrypt(shared_ptr< vector<char> > spBuffer, size_t seed )
{
	CMersenneTwister mt;
	unsigned long rseed = (seed << 7) ^ 0xA9C36DE1;
	mt.init_genrand(rseed);
	for (size_t i = 0; i < spBuffer->size();i++)
	{
		spBuffer->at(i) = (char)(spBuffer->at(i)  ^ mt.genrand_int32());
	}
}