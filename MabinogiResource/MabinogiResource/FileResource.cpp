#include "StdAfx.h"
#include "FileResource.h"

#include "zlib/zlib.h"
#include "Utility.h"

CFileResource::CFileResource(void)
{
	m_decompressedSize = m_compressedSize = m_version = 0;
}


CFileResource::~CFileResource(void)
{
}

std::string CFileResource::GetName() 
{
	return m_name;
}

size_t CFileResource::GetCompressedSize() 
{
	if (m_compressedSize <= 0)
	{
		m_compressedSize = GetCompressedContent()->size();
	}
	return m_compressedSize;
}

size_t CFileResource::GetVersion() 
{
	return m_version;
}

FILETIME CFileResource::GetCreationTime() 
{
	return m_ftCreation;
}

FILETIME CFileResource::GetLastAccessTime() 
{
	return m_ftLastAccess;
}

FILETIME CFileResource::GetLastWriteTime() 
{
	return m_ftLastWrite;
}

shared_ptr< vector<char> > CFileResource::GetDecompressedContent() 
{
	shared_ptr< vector<char> > buffer(new vector<char>(m_spFile->GetLength()));
	m_spFile->Seek(0, FILE_BEGIN);
	UINT tmp = m_spFile->Read(&(*buffer->begin()), buffer->size() );
	// 暂时不检查tmp
	return buffer;
}

shared_ptr< vector<char> > CFileResource::GetCompressedContent() 
{
	shared_ptr<vector<char> > decompressed = GetDecompressedContent();
	unsigned long encodeLen = m_compressedSize;
	if (encodeLen <= 0)
	{
		encodeLen = decompressed->size() + 10240; // 加上一个数字，防止一些压缩后更大的
	}
	
	shared_ptr<vector<char> > buffer(new vector<char>(encodeLen));

	compress((Bytef *)&(*buffer->begin()), &encodeLen, (Bytef *)&(*decompressed->begin()), decompressed->size());

	buffer->resize(encodeLen);
	m_compressedSize = encodeLen;

	return buffer;
}

shared_ptr<IResource> CFileResource::CreateResourceFromFile( LPCTSTR lpszFile, LPCSTR lpszResourceName, size_t version)
{
	shared_ptr<IResource> spResource(new CFileResource());
	CFileResource * pRes = (CFileResource *)spResource.get();
	pRes->m_version = version;
	pRes->m_spFile = shared_ptr<CWin32File>(new CWin32File(lpszFile));
	pRes->m_name = lpszResourceName;
	
	WIN32_FIND_DATA wfd;
	HANDLE hFind = ::FindFirstFile(lpszFile, &wfd);
	pRes->m_ftCreation = wfd.ftCreationTime;
	pRes->m_ftLastAccess = wfd.ftLastAccessTime;
	pRes->m_ftLastWrite = wfd.ftLastWriteTime;
	pRes->m_decompressedSize = wfd.nFileSizeLow;
	::FindClose(hFind);

	return spResource;

}

size_t CFileResource::GetDecompressedSize() 
{
	return m_decompressedSize;
}