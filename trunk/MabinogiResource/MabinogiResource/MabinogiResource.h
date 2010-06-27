// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 MABINOGIRESOURCE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// MABINOGIRESOURCE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#pragma once

#ifdef MABINOGIRESOURCE_EXPORTS
#define MABINOGIRESOURCE_API __declspec(dllexport)
#else
#define MABINOGIRESOURCE_API __declspec(dllimport)
#endif

struct PACK_RESOURCE_SET {};
struct PACK_RESOURCE {};

typedef PACK_RESOURCE_SET* PACK_RESOURCE_SET_HANDLE;
typedef PACK_RESOURCE* PACK_RESOURCE_HANDLE;

//////////////////////////////////////////////////////////////////////////
// 创建资源集和关闭资源集的操作
MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFolder(LPCTSTR lpszFolder);
MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFile(LPCTSTR lpszFile);
MABINOGIRESOURCE_API void CloseResourceSet(PACK_RESOURCE_SET_HANDLE hResourceSet);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 找到指定全名的资源
MABINOGIRESOURCE_API int FindResourceIndex(PACK_RESOURCE_SET_HANDLE hResourceSet, LPCSTR lpszName);

// 获得一个资源
MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE GetResource(PACK_RESOURCE_SET_HANDLE hResourceSet, size_t index);

// 从一个文件创建资源
MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE CreateResourceFromFile(LPCTSTR lpszFile, LPCSTR lpszResourceName, size_t version);

// 释放一个资源的引用
MABINOGIRESOURCE_API void CloseResource(PACK_RESOURCE_HANDLE hResource);

// 获得资源总数
MABINOGIRESOURCE_API size_t GetResourceCount(PACK_RESOURCE_SET_HANDLE hResourceSet);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 当前实体的全名，为相对路径，如 db/ss.xml
MABINOGIRESOURCE_API int GetResourceName(PACK_RESOURCE_HANDLE hResource, LPSTR lpszBuffer, int nBuffer);

// 全名的长度
MABINOGIRESOURCE_API int GetResourceNameLength(PACK_RESOURCE_HANDLE hResource);

// 返回解压后内容
MABINOGIRESOURCE_API size_t GetDecompressedContent(PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size);

// 返回解压前内容
MABINOGIRESOURCE_API size_t GetCompressedContent(PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size);

// 返回压缩后大小
MABINOGIRESOURCE_API size_t GetCompressedSize(PACK_RESOURCE_HANDLE hResource);

// 返回压缩前的大小
MABINOGIRESOURCE_API size_t GetDecompressedSize(PACK_RESOURCE_HANDLE hResource);

// 返回版本，数字越大，版本越高
MABINOGIRESOURCE_API size_t GetVersion(PACK_RESOURCE_HANDLE hResource);

// 返回创建时间
MABINOGIRESOURCE_API FILETIME GetCreationTime(PACK_RESOURCE_HANDLE hResource);

// 返回最后访问时间
MABINOGIRESOURCE_API FILETIME GetLastAccessTime(PACK_RESOURCE_HANDLE hResource);

// 返回最后写入时间
MABINOGIRESOURCE_API FILETIME GetLastWriteTime(PACK_RESOURCE_HANDLE hResource);	
//////////////////////////////////////////////////////////////////////////

// 保存为一个pack文件
MABINOGIRESOURCE_API void PackResources(PACK_RESOURCE_HANDLE * hResourceArray, size_t length, size_t version, LPCTSTR lpszPackFile);