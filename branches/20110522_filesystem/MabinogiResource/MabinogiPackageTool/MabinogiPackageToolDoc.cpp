
// MabinogiPackageToolDoc.cpp : CMabinogiPackageToolDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MabinogiPackageTool.h"
#endif

#include "MabinogiPackageToolDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#if _DEBUG
#pragma comment(lib, "../debug/lib/MabinogiResource.lib")
#else
#pragma comment(lib, "../release/lib/MabinogiResource.lib")
#endif

// CMabinogiPackageToolDoc

IMPLEMENT_DYNCREATE(CMabinogiPackageToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CMabinogiPackageToolDoc, CDocument)
END_MESSAGE_MAP()


// CMabinogiPackageToolDoc ����/����

CMabinogiPackageToolDoc::CMabinogiPackageToolDoc()
{
	m_pResourceSet = NULL;
}

CMabinogiPackageToolDoc::~CMabinogiPackageToolDoc()
{
}

BOOL CMabinogiPackageToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	AfxMessageBox(TEXT("�޷��½�"));

	return FALSE;
}




// CMabinogiPackageToolDoc ���л�

void CMabinogiPackageToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ����

	}
	else
	{
		m_pResourceSet = IResourceSet::CreateResourceSetFromFile(ar.GetFile()->GetFilePath());
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMabinogiPackageToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMabinogiPackageToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMabinogiPackageToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMabinogiPackageToolDoc ���

#ifdef _DEBUG
void CMabinogiPackageToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMabinogiPackageToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMabinogiPackageToolDoc ����


void CMabinogiPackageToolDoc::OnCloseDocument()
{
	if (m_pResourceSet != NULL)
	{
		m_pResourceSet->Release();
		m_pResourceSet = NULL;
	}
	CDocument::OnCloseDocument();
}
