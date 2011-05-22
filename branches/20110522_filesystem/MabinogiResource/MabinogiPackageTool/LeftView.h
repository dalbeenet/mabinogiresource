
// LeftView.h : CLeftView ��Ľӿ�
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
protected: // �������л�����
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// ����
public:
	CMabinogiPackageToolDoc* GetDocument();

// ����
public:

// ��д
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// ���ڵ���ļ��б��ӳ��
	map< HTREEITEM,  shared_ptr< vector< IResource * > > > m_treeDataMap;

	// ·���ͽڵ��ӳ��
	map< CString, HTREEITEM > m_treeNodeMap;
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
private:
	HTREEITEM CreateTreeNode(HTREEITEM root, CString path);
	HIMAGELIST m_hImageList;
	int m_nFolderCloseIcon;
	int m_nFolderOpenIcon;
	void FillData(void);
};

#ifndef _DEBUG  // LeftView.cpp �еĵ��԰汾
inline CMabinogiPackageToolDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CMabinogiPackageToolDoc*>(m_pDocument); }
#endif

