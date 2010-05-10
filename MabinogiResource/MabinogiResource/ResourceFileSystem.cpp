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

shared_ptr<IResource> CResourceFileSystem::GetResource( size_t index )
{
	return m_Resources.at(index);
}

int CResourceFileSystem::FindResourceIndex( LPCSTR lpszName )
{
	return CUtility::FindResourceIndex(m_Resources, lpszName);
}

shared_ptr<IResourceSet> CResourceFileSystem::CreateResourceFileSystemFromFolder( LPCTSTR lpszPackFolder )
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
				shared_ptr<IResourceSet> spResourceSet = CPackResourceSet::CreateResourceSetFromFile( fullPath.c_str());
				if (spResourceSet.get() != 0)
				{
					// 添加
					size_t count = spResourceSet->GetResourceCount();
					for (size_t i = 0; i < count; i++)
					{
						shared_ptr<IResource> spResource = spResourceSet->GetResource(i);
						// 和本地比较版本，保留高版本的
						ResourceMap::iterator iter = resourceMap.find(spResource->GetName());
						
						if (iter != resourceMap.end())
						{
							shared_ptr<IResource> spResourceOld = iter->second;
							if (spResourceOld->GetVersion() >= spResource->GetVersion())
							{
								continue;
							}
						}
						
						resourceMap[spResource->GetName()] = spResource;
					}
				}
			}
		}
		while (::FindNextFile(hFind, &ffd) != 0);
		::FindClose(hFind);
	}

	if (resourceMap.size() > 0)
	{
		shared_ptr<IResourceSet> result(new CResourceFileSystem());
		for (ResourceMap::iterator iter = resourceMap.begin(); iter != resourceMap.end(); ++iter)
		{
			((CResourceFileSystem*)result.get())->m_Resources.push_back( iter->second );
		}

		return result;
	}
	else
	{
		return shared_ptr<CResourceFileSystem>();
	}
}