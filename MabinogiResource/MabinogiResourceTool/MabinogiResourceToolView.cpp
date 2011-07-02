
// MabinogiResourceToolView.cpp : CMabinogiResourceToolView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MabinogiResourceTool.h"
#endif

#include "MabinogiResourceToolDoc.h"
#include "MabinogiResourceToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <commoncontrols.h>
// CMabinogiResourceToolView

IMPLEMENT_DYNCREATE(CMabinogiResourceToolView, CListView)

BEGIN_MESSAGE_MAP(CMabinogiResourceToolView, CListView)
	ON_WM_STYLECHANGED()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMabinogiResourceToolView ����/����

CMabinogiResourceToolView::CMabinogiResourceToolView()
{
	// TODO: �ڴ˴���ӹ������

}

CMabinogiResourceToolView::~CMabinogiResourceToolView()
{
}

BOOL CMabinogiResourceToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style |= LVS_REPORT | LVS_SHAREIMAGELISTS;
	return CListView::PreCreateWindow(cs);
}

void CMabinogiResourceToolView::OnInitialUpdate()
{
	int nIndex = 0;
	GetListCtrl().InsertColumn(nIndex++, TEXT("�ļ���"), LVCFMT_LEFT, 100);
	GetListCtrl().InsertColumn(nIndex++, TEXT("�汾"), LVCFMT_LEFT, 100);
	GetListCtrl().InsertColumn(nIndex++, TEXT("����˵��"), LVCFMT_LEFT, 100);
	GetListCtrl().InsertColumn(nIndex++, TEXT("��С"), LVCFMT_LEFT, 100);
	GetListCtrl().InsertColumn(nIndex++, TEXT("ѹ�����С"), LVCFMT_LEFT, 100);
	GetListCtrl().InsertColumn(nIndex++, TEXT("�ļ�ʱ��1"), LVCFMT_LEFT, 100);
	GetListCtrl().InsertColumn(nIndex++, TEXT("�ļ�ʱ��2"), LVCFMT_LEFT, 100);
	GetListCtrl().InsertColumn(nIndex++, TEXT("�ļ�ʱ��3"), LVCFMT_LEFT, 100);

	SHFILEINFO shFilefo;
	HIMAGELIST hImgList;// = (HIMAGELIST)SHGetFileInfo(TEXT(""), 0, &shFilefo,sizeof(shFilefo), SHGFI_SYSICONINDEX|SHGFI_LARGEICON);
	SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, (void**) &hImgList);
	GetListCtrl().SetImageList(CImageList::FromHandle(hImgList), TVSIL_NORMAL);

	hImgList = (HIMAGELIST)SHGetFileInfo(TEXT(""), 0, &shFilefo,sizeof(shFilefo), SHGFI_SYSICONINDEX|SHGFI_SMALLICON); 
	GetListCtrl().SetImageList(CImageList::FromHandle(hImgList), LVSIL_SMALL);


	GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_HEADERDRAGDROP);

	LVTILEVIEWINFO lvtvi = { sizeof(LVTILEVIEWINFO), LVTVIM_COLUMNS };

	lvtvi.cLines = 2;
	lvtvi.dwFlags = LVTVIF_AUTOSIZE;
	GetListCtrl().SetTileViewInfo ( &lvtvi );

	CListView::OnInitialUpdate();


}

void CMabinogiResourceToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMabinogiResourceToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMabinogiResourceToolView ���

#ifdef _DEBUG
void CMabinogiResourceToolView::AssertValid() const
{
	CListView::AssertValid();
}

void CMabinogiResourceToolView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CMabinogiResourceToolDoc* CMabinogiResourceToolView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMabinogiResourceToolDoc)));
	return (CMabinogiResourceToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMabinogiResourceToolView ��Ϣ�������
void CMabinogiResourceToolView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: ��Ӵ�������Ӧ�û��Դ�����ͼ��ʽ�ĸ���	
	CListView::OnStyleChanged(nStyleType,lpStyleStruct);	
}

CString GetFileSizeDesc( unsigned long size )
{
	CString desc;

	if (size < 1024)
	{
		desc.Format( TEXT("%d �ֽ�"), size);
	}
	else if ( size < 1024 * 1024)
	{
		desc.Format( TEXT("%d KB"), (int)(size / 1024) );
	}
	else if ( size < 1024 * 1024 * 1024)
	{
		desc.Format( TEXT("%d MB"), (int)(size / 1024 / 1024) );
	}
	else
	{
		desc.Format( TEXT("%d GB"), (int)(size / 1024 / 1024 / 1024) );
	}

	return desc;
}

void CMabinogiResourceToolView::OnUpdate(CView* pSender, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	if (pSender != this)
	{
		SHFILEINFO shFilefo;

		GetListCtrl().DeleteAllItems();
		int index = 0;
		pair<ResourceContainerMap::const_iterator, ResourceContainerMap::const_iterator> valueRange = 
			GetDocument()->m_resContainerMap.equal_range(GetDocument()->m_strDir);
		for (auto iter = valueRange.first; iter!=valueRange.second; ++iter)
		{
			SHGetFileInfo( iter->second->pResource->GetName() , FILE_ATTRIBUTE_NORMAL , &shFilefo,sizeof(shFilefo), SHGFI_SYSICONINDEX|SHGFI_USEFILEATTRIBUTES );

			int row = GetListCtrl().InsertItem(index++, iter->second->name, shFilefo.iIcon);

			int col = 1;
			CString strText;

			// �汾
			strText.Format(TEXT("%d"), iter->second->pResource->GetVersion());
			GetListCtrl().SetItemText(row, col++, strText);

			// ����˵��
			SHFILEINFO shFilefo;
			SHGetFileInfo( iter->second->pResource->GetName() ,FILE_ATTRIBUTE_NORMAL , &shFilefo, sizeof(shFilefo),
				SHGFI_TYPENAME|SHGFI_USEFILEATTRIBUTES );


			GetListCtrl().SetItemText(row, col++, shFilefo.szTypeName);

			// ѹ��ǰ��С
			GetListCtrl().SetItemText(row, col++, GetFileSizeDesc(iter->second->pResource->GetDecompressedSize()) );

			// ѹ�����С
			GetListCtrl().SetItemText(row, col++, GetFileSizeDesc(iter->second->pResource->GetCompressedSize()) );


			CTime time;
			// �ļ�ʱ��1
			GetListCtrl().SetItemText(row, col++, CTime(iter->second->pResource->GetCreationTime()).Format(TEXT("%Y/%m/%d %H:%M:%S")) );

			// �ļ�ʱ��2
			GetListCtrl().SetItemText(row, col++, CTime(iter->second->pResource->GetLastAccessTime()).Format(TEXT("%Y/%m/%d %H:%M:%S")) );

			// �ļ�ʱ��3
			GetListCtrl().SetItemText(row, col++, CTime(iter->second->pResource->GetLastWriteTime()).Format(TEXT("%Y/%m/%d %H:%M:%S")) );


			UINT aCols[] = {3,2};
			LVTILEINFO lvti = { sizeof(LVTILEINFO), row, 2, aCols };

			GetListCtrl().SetTileInfo ( &lvti );
		}
	}
}
