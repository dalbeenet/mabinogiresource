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
	SReourceSet(IResourceSet * pResourceSet)
	{
		m_pResourceSet = pResourceSet;
	};

	~SReourceSet()
	{
		delete m_pResourceSet;
		m_pResourceSet = NULL;
	}
	IResourceSet * m_pResourceSet;
};

struct SResource : public PACK_RESOURCE
{
	SResource(IResource * pResource)
	{
		m_pResource = pResource;
	};
	~SResource()
	{
		delete m_pResource;
		m_pResource = NULL;
	}
	IResource * m_pResource;
};


MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFolder( LPCTSTR lpszFolder )
{
	IResourceSet * pSet = IResourceSet::CreateResourceSetFromFolder(lpszFolder);
	if (pSet != 0)
	{
		return new SReourceSet(pSet);
	}

	return 0;
}

MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFile( LPCTSTR lpszFile )
{
	//shared_ptr<IResourceSet> spSet = CPackResourceSet::CreateResourceSetFromFile(lpszFile);
	//if (spSet.get() != 0)
	//{
	//	return new SReourceSet(spSet);
	//}

	return 0;
}

MABINOGIRESOURCE_API void CloseResourceSet( PACK_RESOURCE_SET_HANDLE hResourceSet )
{
	delete hResourceSet;
}

MABINOGIRESOURCE_API int FindResourceIndex( PACK_RESOURCE_SET_HANDLE hResourceSet, LPCSTR lpszName )
{
	SReourceSet * pSSet = (SReourceSet *) hResourceSet;
	return pSSet->m_pResourceSet->FindResourceIndex(lpszName);
}

MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE GetResource( PACK_RESOURCE_SET_HANDLE hResourceSet, size_t index )
{
	SReourceSet * pSSet = (SReourceSet *) hResourceSet;
	IResource * pRes = pSSet->m_pResourceSet->GetResource(index);
	return new SResource(pRes);
}

MABINOGIRESOURCE_API size_t GetResourceCount( PACK_RESOURCE_SET_HANDLE hResourceSet )
{
	SReourceSet * pSSet = (SReourceSet *) hResourceSet;
	return pSSet->m_pResourceSet->GetResourceCount();
}

MABINOGIRESOURCE_API void CloseResource( PACK_RESOURCE_HANDLE hResource )
{
	delete hResource;
}

//MABINOGIRESOURCE_API LPCSTR GetName( PACK_RESOURCE_HANDLE hResource )
//{
//	SResource * pSRes = (SResource *) hResource;
//	return pSRes->m_spResource->GetName().c_str();
//}

MABINOGIRESOURCE_API size_t GetDecompressedContent( PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size )
{
	SResource * pSRes = (SResource *) hResource;

	return pSRes->m_pResource->GetDecompressedContent((char*)lpBuffer, size);
}

MABINOGIRESOURCE_API size_t GetCompressedContent( PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size )
{
	SResource * pSRes = (SResource *) hResource;

	return pSRes->m_pResource->GetCompressedContent((char*)lpBuffer, size);
}

MABINOGIRESOURCE_API size_t GetCompressedSize( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_pResource->GetCompressedSize();
}

MABINOGIRESOURCE_API size_t GetDecompressedSize( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_pResource->GetDecompressedSize();
}

MABINOGIRESOURCE_API size_t GetVersion( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_pResource->GetVersion();
}

MABINOGIRESOURCE_API FILETIME GetCreationTime( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_pResource->GetCreationTime();
}

MABINOGIRESOURCE_API FILETIME GetLastAccessTime( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_pResource->GetLastAccessTime();
}

MABINOGIRESOURCE_API FILETIME GetLastWriteTime( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_pResource->GetLastWriteTime();
}

MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE CreateResourceFromFile( LPCTSTR lpszFile, LPCSTR lpszResourceName, size_t version )
{
	IResource * pRes = IResource::CreateResourceFromFile(lpszFile, lpszResourceName, version);
	return new SResource(pRes);
}


MABINOGIRESOURCE_API void PackResources( PACK_RESOURCE_HANDLE * hResourceArray, size_t length, size_t version, LPCTSTR lpszPackFile, ProgressMonitorProc proc, DWORD dwParameter)
{

	vector<IResource*> resources;
	for (size_t i = 0;i < length;i++)
	{
		SResource * pSres = (SResource *)hResourceArray[i];
		resources.push_back(pSres->m_pResource);
	}

	IResourceSet::PackResources(&resources[0], resources.size(), version, lpszPackFile, NULL);

}

MABINOGIRESOURCE_API int GetResourceName( PACK_RESOURCE_HANDLE hResource, LPSTR lpszBuffer, int nBuffer )
{
	SResource * pSRes = (SResource *) hResource;
	int nLength = lstrlenA( pSRes->m_pResource->GetName() );
	nLength = (nLength > nBuffer) ? nBuffer : nLength;

	lstrcpynA(lpszBuffer, pSRes->m_pResource->GetName(), nLength);

	return nLength;
}

MABINOGIRESOURCE_API int GetResourceNameLength( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return lstrlenA(pSRes->m_pResource->GetName());
}