#include "StdAfx.h"
#include "ResourceFileSystem.h"

#include "PackResourceSet.h"
#include "Utility.h"
#include <map>

using namespace std;

#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif

//////////////////////////////////////////////////////////////////////////
IResourceSet * IResourceSet::CreateResourceSetFromFolder(LPCTSTR lpszPackFolder)
{
	CResourceFileSystem * pRfs = new CResourceFileSystem();
	pRfs->Open(lpszPackFolder);
	return pRfs;
}

//////////////////////////////////////////////////////////////////////////
CResourceFileSystem::CResourceFileSystem(void)
{
}

CResourceFileSystem::~CResourceFileSystem(void)
{
}

size_t CResourceFileSystem::GetResourceCount()
{
	return m_Resources.size();
}

IResource * CResourceFileSystem::GetResource( size_t index )
{
	return m_Resources.at(index).get();
}

int CResourceFileSystem::FindResourceIndex( LPCSTR lpszName )
{
	return CUtility::FindResourceIndex(m_Resources, lpszName);
}

bool CResourceFileSystem::Open( LPCTSTR lpszPackFolder )
{
	tstring folderPath = lpszPackFolder;
	tstring::iterator lastChar = folderPath.end();
	--lastChar;
	if ( *lastChar != TEXT('/') && *lastChar != TEXT('\\') )
	{
		folderPath += TEXT("\\");
	}

	tstring condition = folderPath + TEXT("*.pack");

	WIN32_FIND_DATA ffd;
	HANDLE hFind;

	typedef map<string, shared_ptr<IResource> > ResourceMap;
	ResourceMap resourceMap;

	hFind = ::FindFirstFile(condition.c_str(), &ffd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			// 非文件夹
			if ( (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			{
				tstring fullPath = folderPath + ffd.cFileName;
				CPackResourceSet resourceSet;
				if (resourceSet.Open(fullPath.c_str()))
				{
					for (vector<shared_ptr<IResource>>::iterator iter = resourceSet.m_Resources.begin();iter != resourceSet.m_Resources.end();++iter)
					{
						// 和本地比较版本，保留高版本的
						ResourceMap::iterator iter2 = resourceMap.find((*iter)->GetName());

						if (iter2 != resourceMap.end())
						{
							shared_ptr<IResource> spResourceOld = iter2->second;
							if (spResourceOld->GetVersion() >= (*iter)->GetVersion())
							{
								continue;
							}
						}

						resourceMap[(*iter)->GetName()] = (*iter);
					}
				}
			}
		}
		while (::FindNextFile(hFind, &ffd) != 0);
		::FindClose(hFind);
	}

	if (resourceMap.size() > 0)
	{
		m_Resources.clear();
		for (ResourceMap::iterator iter = resourceMap.begin(); iter != resourceMap.end(); ++iter)
		{
			m_Resources.push_back( iter->second );
		}

		return true;
	}
	else
	{
		return false;
	}
}

void CResourceFileSystem::Release()
{
	delete this;
}