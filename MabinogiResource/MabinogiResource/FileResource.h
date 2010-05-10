#pragma once
#include "iresource.h"

#include <string>
#include <memory>
#include <vector>
#include "Win32File.h"

using namespace std;
using namespace std::tr1;

class CFileResource : public IResource
{
protected:
	CFileResource(void);
public:
	virtual ~CFileResource(void);

	static shared_ptr<IResource> CreateResourceFromFile(LPCTSTR lpszFile, LPCSTR lpszResourceName, size_t version);

	// 当前实体的全名，为相对路径，如 db/ss.xml
	virtual string GetName() ;

	// 返回解压后内容，每次返回新的容器
	virtual shared_ptr< vector<char> > GetDecompressedContent() ;

	// 返回解压前内容，每次返回新的容器
	virtual shared_ptr< vector<char> > GetCompressedContent() ;

	// 返回压缩后大小
	virtual size_t GetCompressedSize() ;

	// 返回压缩前的大小
	virtual size_t GetDecompressedSize() ;

	// 返回版本，数字越大，版本越高
	virtual size_t GetVersion() ;

	// 返回创建时间
	virtual FILETIME GetCreationTime() ;

	// 返回最后访问时间
	virtual FILETIME GetLastAccessTime() ;

	// 返回最后写入时间
	virtual FILETIME GetLastWriteTime() ;

protected:
	shared_ptr< CWin32File > m_spFile;
	string m_name;
	size_t m_compressedSize;
	size_t m_decompressedSize;
	size_t m_version;
	FILETIME m_ftCreation;
	FILETIME m_ftLastAccess;
	FILETIME m_ftLastWrite;
};
