#pragma once

#include <string>
#include <vector>
#include <memory>

using namespace std;
using namespace std::tr1;

class IResource
{
public:

	IResource(void){}

	virtual ~IResource(void){}

	// 当前实体的全名，为相对路径，如 db/ss.xml
	virtual string GetName() = 0;

	// 返回解压后内容（未加密），每次返回新的容器
	virtual shared_ptr< vector<char> > GetDecompressedContent() = 0;


	// 返回解压前内容（未加密），每次返回新的容器
	virtual shared_ptr< vector<char> > GetCompressedContent() = 0;

	// 返回压缩后大小
	virtual size_t GetCompressedSize() = 0;

	// 返回压缩前的大小
	virtual size_t GetDecompressedSize() = 0;

	// 返回版本，数字越大，版本越高
	virtual size_t GetVersion() = 0;

	// 返回创建时间
	virtual FILETIME GetCreationTime() = 0;

	// 返回最后访问时间
	virtual FILETIME GetLastAccessTime() = 0;

	// 返回最后写入时间
	virtual FILETIME GetLastWriteTime() = 0;	
};

typedef vector<shared_ptr<IResource> > ResourceList;
