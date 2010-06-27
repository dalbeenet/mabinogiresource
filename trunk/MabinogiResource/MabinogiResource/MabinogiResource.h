// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MABINOGIRESOURCE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MABINOGIRESOURCE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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
// ������Դ���͹ر���Դ���Ĳ���
MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFolder(LPCTSTR lpszFolder);
MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFile(LPCTSTR lpszFile);
MABINOGIRESOURCE_API void CloseResourceSet(PACK_RESOURCE_SET_HANDLE hResourceSet);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// �ҵ�ָ��ȫ������Դ
MABINOGIRESOURCE_API int FindResourceIndex(PACK_RESOURCE_SET_HANDLE hResourceSet, LPCSTR lpszName);

// ���һ����Դ
MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE GetResource(PACK_RESOURCE_SET_HANDLE hResourceSet, size_t index);

// ��һ���ļ�������Դ
MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE CreateResourceFromFile(LPCTSTR lpszFile, LPCSTR lpszResourceName, size_t version);

// �ͷ�һ����Դ������
MABINOGIRESOURCE_API void CloseResource(PACK_RESOURCE_HANDLE hResource);

// �����Դ����
MABINOGIRESOURCE_API size_t GetResourceCount(PACK_RESOURCE_SET_HANDLE hResourceSet);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// ��ǰʵ���ȫ����Ϊ���·������ db/ss.xml
MABINOGIRESOURCE_API int GetResourceName(PACK_RESOURCE_HANDLE hResource, LPSTR lpszBuffer, int nBuffer);

// ȫ���ĳ���
MABINOGIRESOURCE_API int GetResourceNameLength(PACK_RESOURCE_HANDLE hResource);

// ���ؽ�ѹ������
MABINOGIRESOURCE_API size_t GetDecompressedContent(PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size);

// ���ؽ�ѹǰ����
MABINOGIRESOURCE_API size_t GetCompressedContent(PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size);

// ����ѹ�����С
MABINOGIRESOURCE_API size_t GetCompressedSize(PACK_RESOURCE_HANDLE hResource);

// ����ѹ��ǰ�Ĵ�С
MABINOGIRESOURCE_API size_t GetDecompressedSize(PACK_RESOURCE_HANDLE hResource);

// ���ذ汾������Խ�󣬰汾Խ��
MABINOGIRESOURCE_API size_t GetVersion(PACK_RESOURCE_HANDLE hResource);

// ���ش���ʱ��
MABINOGIRESOURCE_API FILETIME GetCreationTime(PACK_RESOURCE_HANDLE hResource);

// ����������ʱ��
MABINOGIRESOURCE_API FILETIME GetLastAccessTime(PACK_RESOURCE_HANDLE hResource);

// �������д��ʱ��
MABINOGIRESOURCE_API FILETIME GetLastWriteTime(PACK_RESOURCE_HANDLE hResource);	
//////////////////////////////////////////////////////////////////////////

// ����Ϊһ��pack�ļ�
MABINOGIRESOURCE_API void PackResources(PACK_RESOURCE_HANDLE * hResourceArray, size_t length, size_t version, LPCTSTR lpszPackFile);