#include "StdAfx.h"
#include "PackResource.h"

#include "Utility.h"
#include "Win32File.h"
#include "zlib/zlib.h"
#pragma comment(lib, "zlib/zlib")

CPackResource::CPackResource( string name, shared_ptr<CWin32File> spFile, ITEM_INFO * pInfo )
{
	m_name = name;
	m_spFile = spFile;
	m_info = *pInfo;
}

CPackResource::~CPackResource(void)
{
}

string CPackResource::GetName() 
{
	return m_name;
}

size_t CPackResource::GetCompressedSize() 
{
	return m_info.compress_size;
}

size_t CPackResource::GetDecompressedSize() 
{
	return m_info.decompress_size;
}

size_t CPackResource::GetVersion() 
{
	return m_info.seed;
}

FILETIME CPackResource::GetCreationTime() 
{
	return m_info.ft[0];
}

FILETIME CPackResource::GetLastAccessTime() 
{
	return m_info.ft[2];
}

FILETIME CPackResource::GetLastWriteTime() 
{
	return m_info.ft[4];
}

shared_ptr< vector<char> > CPackResource::GetDecompressedContent() 
{
	shared_ptr< vector<char> > compressedContent = GetCompressedContent();
	if (compressedContent.get() == 0)
	{
		// 错误
		return shared_ptr< vector<char> >();
	}

	shared_ptr< vector<char> > result(new vector<char>(m_info.decompress_size));
	unsigned long decodeLen = m_info.decompress_size; 
	uncompress((Bytef *)&(*result->begin()), &decodeLen, (Bytef *)&(*compressedContent->begin()), m_info.compress_size);
	return result;
}

shared_ptr< vector<char> > CPackResource::GetCompressedContent() 
{
	shared_ptr<vector<char> > result(new vector<char>(m_info.compress_size));

	m_spFile->Seek(m_info.offset, FILE_BEGIN);
	int tmp = m_spFile->Read( &(*result->begin()), m_info.compress_size );
	if (tmp != m_info.compress_size)
	{
		// 文件读取错误
		return shared_ptr< vector<char> >();
	}

	// 直接读取的是加密的，需要解密
	CUtility::Decrypt(result, m_info.seed);

	return result;
}