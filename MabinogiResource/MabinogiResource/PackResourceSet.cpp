#include "StdAfx.h"
#include "PackResourceSet.h"

#include "Win32File.h"
#include "types.h"
#include "PackResource.h"
#include "Utility.h"

#include <algorithm>



CPackResourceSet::CPackResourceSet(void)
{
}

CPackResourceSet::~CPackResourceSet(void)
{
	
}

shared_ptr<IResourceSet> CPackResourceSet::CreateResourceSetFromFile( LPCTSTR lpszPackFile )
{
	static shared_ptr<IResourceSet> INVALID_VALUE;

	CPackResourceSet * pResourceSet;
	shared_ptr<IResourceSet> resourceSet(pResourceSet = new CPackResourceSet());
	shared_ptr<CWin32File> spFile(new CWin32File(lpszPackFile));
	if (!spFile->IsOK())
	{
		// 打开文件错误
		return INVALID_VALUE;
	}

	UINT tmp;
	PACKAGE_HEADER header;
	tmp = spFile->Read(&header, sizeof(PACKAGE_HEADER));

	if ( tmp != sizeof(PACKAGE_HEADER))
	{
		// 读取文件错误
		return INVALID_VALUE;
	}

	// 检查文件头
	if ( memcmp(header.signature, "PACK", 4) != 0) 
	{
		// 文件头错误
		return INVALID_VALUE;
	}


	PACKAGE_LIST_HEADER listHeader;
	tmp = spFile->Read(&listHeader, sizeof(PACKAGE_LIST_HEADER));

	if (tmp != sizeof(PACKAGE_LIST_HEADER))
	{
		// 读取文件错误
		return INVALID_VALUE;
	}

	shared_ptr< vector<char> > spListInfoData(new vector<char>(listHeader.list_header_size));
	tmp = spFile->Read( &(*spListInfoData->begin()), listHeader.list_header_size );
	if (tmp != listHeader.list_header_size)
	{
		// 读取文件错误
		return INVALID_VALUE;
	}

	char * pTemp =  &(*spListInfoData->begin());
	for (size_t i = 0;i < listHeader.sum; i++)
	{
		ITEM_NAME * pItemName = (ITEM_NAME *)pTemp;

		unsigned long ulSize;
		if (pItemName->len_or_type < 4)
		{
			// 第一字节小于4
			ulSize = (0x10 * (pItemName->len_or_type + 1));
		}
		else if (pItemName->len_or_type == 4)
		{
			// 可恶的恶魔猫，这里怎么要搞特殊的
			ulSize = 0x60 ;
		}
		else
		{
			// 基本参考mabiunpack代码
			ulSize = pItemName->len + 5;
		}

		string name;
		if ( pItemName->len_or_type <= 0x04 )
		{
			name = pItemName->sz_ansi_name;
		}
		else // 0x05
		{
			name = pItemName->sz_ansi_name2;
		}

		// 指针跨越名称定义区
		pTemp += ulSize;

		ITEM_INFO * pInfo = (ITEM_INFO*)pTemp;

		// 累计文件偏移，其实这里修改了内存
		pInfo->offset += sizeof(PACKAGE_HEADER) + sizeof(PACKAGE_LIST_HEADER) + listHeader.list_header_size;

		// 指针定位到下一项
		pTemp += sizeof(ITEM_INFO);

		shared_ptr<IResource> spResource(new CPackResource(name, spFile, pInfo));
		pResourceSet->m_Resources.push_back( spResource );
	}

	//class ResourceGreater
	//{
	//public:
	//	bool operator()(shared_ptr<IResource> spResource1, shared_ptr<IResource> spResource2) 
	//	{
	//		return spResource1->GetName() > spResource2->GetName();
	//	}
	//};

	//// 对于容器进行排序，以便可以进行二分查找
	//sort(pResourceSet->m_Resources.begin(), pResourceSet->m_Resources.end(), ResourceGreater());

	return resourceSet;
}

int CPackResourceSet::FindResourceIndex( LPCSTR lpszName )
{
	return CUtility::FindResourceIndex(m_Resources, lpszName);
}

size_t CPackResourceSet::GetResourceCount()
{
	return m_Resources.size();
}

shared_ptr<IResource> CPackResourceSet::GetResource( size_t index )
{
	return m_Resources.at(index);
}


shared_ptr< vector<char> > GetNameChars(LPCSTR lpszName)
{
	int nLen = lstrlenA(lpszName) + 1; // 结束符
	if (nLen <= 0x60 - 1 )
	{
		shared_ptr< vector<char> > spBuffer;
		char type;
		if (nLen < 0x40 - 1)
		{
			type = nLen / 0x10;
			spBuffer.reset(new vector<char>( (type + 1) * 0x10));
		}
		else
		{
			type = 4;
			spBuffer.reset(new vector<char>(0x60));
		}

		*spBuffer->begin() = type;

		lstrcpyA( &(*spBuffer->begin()) + 1, lpszName );

		return spBuffer;
	}
	else
	{
		DWORD dwLen = (nLen + 5) % 0x10;
		if (dwLen == 0)
		{
			dwLen = nLen;
		}
		else
		{
			dwLen = (nLen - dwLen + 0x10);
		}

		shared_ptr< vector<char> > spBuffer(new vector<char>( 5 + dwLen));

		memset( &(*spBuffer->begin()), 0, dwLen + 5);
		*spBuffer->begin() = 5;
		memcpy( &(*spBuffer->begin()) + 1, &dwLen, 2);
		lstrcpyA( &(*spBuffer->begin()) + 5, lpszName);
		return spBuffer;
	}

}

void CPackResourceSet::PackResources( vector<shared_ptr<IResource> > & resources, size_t version, LPCTSTR lpszPackFile )
{
	PACKAGE_HEADER header;
	memcpy(header.signature, "PACK\002\001\0\0", 8);
	header.d1 = 1;
	header.sum = resources.size();

	FILETIME ft;
	SYSTEMTIME st;

	GetSystemTime(&st);              // gets current time
	SystemTimeToFileTime(&st, &ft);  // converts to file time format
	header.ft1 = ft;
	header.ft2 = ft;

	memset(header.path, 0, 480);
	lstrcpyA(header.path, "data\\");

	PACKAGE_LIST_HEADER listHeader;
	listHeader.sum = resources.size();
	// 预先设定一个文件列表空间
	listHeader.list_header_size = 0 ;
	listHeader.blank_size = 0;
	listHeader.data_section_size = 0;
	memset(listHeader.zero, 0, 16);

	vector< shared_ptr<vector<char> > > array_item_name_chars;
	for (size_t i = 0; i < resources.size();i++)
	{
		shared_ptr< vector<char> > namechars = GetNameChars(resources[i]->GetName().c_str());

		array_item_name_chars.push_back(namechars);

		listHeader.list_header_size += (namechars->size() + sizeof(ITEM_INFO));
	}

	CWin32File outFile(lpszPackFile, true);
	outFile.Seek( sizeof(PACKAGE_HEADER) + sizeof(PACKAGE_LIST_HEADER) + listHeader.list_header_size, FILE_BEGIN);

	vector< shared_ptr<ITEM_INFO> > array_info;
	for (size_t i = 0; i < resources.size();i++)
	{
		shared_ptr< vector<char> > spCompressedContent = resources[i]->GetCompressedContent();

		// 写入文件需要加密
		CUtility::Encrypt(spCompressedContent, version);
		outFile.Write( &(*spCompressedContent->begin()), spCompressedContent->size() );

		shared_ptr<ITEM_INFO> spInfo(new ITEM_INFO);
		spInfo->compress_size = resources[i]->GetCompressedSize();
		spInfo->decompress_size = resources[i]->GetDecompressedSize();
		spInfo->is_compressed = 1;
		spInfo->offset = listHeader.data_section_size;
		spInfo->seed = version;
		spInfo->ft[0] = spInfo->ft[1] = resources[i]->GetCreationTime();
		spInfo->ft[2] = spInfo->ft[3] = resources[i]->GetLastAccessTime();
		spInfo->ft[4] = resources[i]->GetLastWriteTime();

		array_info.push_back(spInfo);

		listHeader.data_section_size += spCompressedContent->size();
	}

	outFile.Seek(0, FILE_BEGIN);
	outFile.Write(&header, sizeof(PACKAGE_HEADER));
	outFile.Write(&listHeader, sizeof(PACKAGE_LIST_HEADER));

	for (size_t i = 0; i < resources.size();i++)
	{
		outFile.Write(&(*array_item_name_chars[i]->begin()), array_item_name_chars[i]->size()  );
		outFile.Write( array_info[i].get(), sizeof(ITEM_INFO) );
	}
}