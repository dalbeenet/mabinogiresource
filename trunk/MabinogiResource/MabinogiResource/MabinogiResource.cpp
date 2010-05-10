// MabinogiResource.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "MabinogiResource.h"

#include "IResource.h"
#include "PackResourceSet.h"
#include "ResourceFileSystem.h"
#include "FileResource.h"
#include <fstream>


struct SReourceSet : public PACK_RESOURCE_SET
{
	SReourceSet(shared_ptr<IResourceSet> spResourceSet)
	{
		m_spResourceSet = spResourceSet;
	};
	shared_ptr<IResourceSet> m_spResourceSet;
};

struct SResource : public PACK_RESOURCE
{
	SResource(shared_ptr<IResource> spResource)
	{
		m_spResource = spResource;
	};
	shared_ptr<IResource> m_spResource;
};


MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFolder( LPCTSTR lpszFolder )
{
	shared_ptr<IResourceSet> spSet = CResourceFileSystem::CreateResourceFileSystemFromFolder(lpszFolder);
	if (spSet.get() != 0)
	{
		return new SReourceSet(spSet);
	}

	return 0;
}

MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFile( LPCTSTR lpszFile )
{
	shared_ptr<IResourceSet> spSet = CPackResourceSet::CreateResourceSetFromFile(lpszFile);
	if (spSet.get() != 0)
	{
		return new SReourceSet(spSet);
	}

	return 0;
}

MABINOGIRESOURCE_API void CloseResourceSet( PACK_RESOURCE_SET_HANDLE hResourceSet )
{
	delete hResourceSet;
}

MABINOGIRESOURCE_API int FindResourceIndex( PACK_RESOURCE_SET_HANDLE hResourceSet, LPCSTR lpszName )
{
	SReourceSet * pSSet = (SReourceSet *) hResourceSet;
	return pSSet->m_spResourceSet->FindResourceIndex(lpszName);
}

MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE GetResource( PACK_RESOURCE_SET_HANDLE hResourceSet, size_t index )
{
	SReourceSet * pSSet = (SReourceSet *) hResourceSet;
	shared_ptr<IResource> spRes = pSSet->m_spResourceSet->GetResource(index);
	return new SResource(spRes);
}

MABINOGIRESOURCE_API size_t GetResourceCount( PACK_RESOURCE_SET_HANDLE hResourceSet )
{
	SReourceSet * pSSet = (SReourceSet *) hResourceSet;
	return pSSet->m_spResourceSet->GetResourceCount();
}

MABINOGIRESOURCE_API void CloseResource( PACK_RESOURCE_HANDLE hResource )
{
	delete hResource;
}

MABINOGIRESOURCE_API LPCSTR GetName( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_spResource->GetName().c_str();
}

MABINOGIRESOURCE_API size_t GetDecompressedContent( PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size )
{
	SResource * pSRes = (SResource *) hResource;
	shared_ptr< vector<char> > spData = pSRes->m_spResource->GetDecompressedContent();
	size = size > spData->size() ? spData->size() : size;
	memcpy(lpBuffer, &(*spData->begin()) , size);

	return size;
}

MABINOGIRESOURCE_API size_t GetCompressedContent( PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size )
{
	SResource * pSRes = (SResource *) hResource;
	shared_ptr< vector<char> > spData = pSRes->m_spResource->GetCompressedContent();
	size = size > spData->size() ? spData->size() : size;
	memcpy(lpBuffer, &(*spData->begin()) , size);

	return size;
}

MABINOGIRESOURCE_API size_t GetCompressedSize( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_spResource->GetCompressedSize();
}

MABINOGIRESOURCE_API size_t GetDecompressedSize( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_spResource->GetDecompressedSize();
}

MABINOGIRESOURCE_API size_t GetVersion( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_spResource->GetVersion();
}

MABINOGIRESOURCE_API FILETIME GetCreationTime( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_spResource->GetCreationTime();
}

MABINOGIRESOURCE_API FILETIME GetLastAccessTime( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_spResource->GetLastAccessTime();
}

MABINOGIRESOURCE_API FILETIME GetLastWriteTime( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_spResource->GetLastWriteTime();
}

MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE CreateResourceFromFile( LPCTSTR lpszFile, LPCSTR lpszResourceName, size_t version )
{
	shared_ptr<IResource> spRes = CFileResource::CreateResourceFromFile(lpszFile, lpszResourceName, version);
	return new SResource(spRes);
}


MABINOGIRESOURCE_API void PackResources( PACK_RESOURCE_HANDLE * hResourceArray, size_t length, size_t version, LPCTSTR lpszPackFile )
{
	vector<shared_ptr<IResource> > resources;
	for (size_t i = 0;i < length;i++)
	{
		SResource * pSres = (SResource *)hResourceArray[i];
		resources.push_back(pSres->m_spResource);
	}

	CPackResourceSet::PackResources(resources, version, lpszPackFile);
}