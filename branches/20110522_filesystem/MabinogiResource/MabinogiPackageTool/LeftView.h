
// LeftView.h : CLeftView 类的接口
//


#pragma once

#include "../MabinogiResource/IResourceSet.h"

#include <map>
#include <memory>
#include <vector>

using namespace std;
using namespace std::tr1;

class CMabinogiPackageToolDoc;

class CLeftView : public CTreeView
{
protected: // 仅从序列化创建
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// 特性
public:
	CMabinogiPackageToolDoc* GetDocument();

// 操作
public:

// 重写
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// 树节点和文件列表的映射
	map< HTREEITEM,  shared_ptr< vector< IResource * > > > m_treeDataMap;

	// 路径和节点的映射
	map< CString, HTREEITEM > m_treeNodeMap;
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
private:
	HTREEITEM CreateTreeNode(HTREEITEM root, CString path);
	HIMAGELIST m_hImageList;
	int m_nFolderCloseIcon;
	int m_nFolderOpenIcon;
	void FillData(void);
};

#ifndef _DEBUG  // LeftView.cpp 中的调试版本
inline CMabinogiPackageToolDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CMabinogiPackageToolDoc*>(m_pDocument); }
#endif

