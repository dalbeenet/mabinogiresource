
// MabinogiResourceToolView.h : CMabinogiResourceToolView ��Ľӿ�
//

#pragma once


class CMabinogiResourceToolView : public CListView
{
protected: // �������л�����
	CMabinogiResourceToolView();
	DECLARE_DYNCREATE(CMabinogiResourceToolView)

// ����
public:
	CMabinogiResourceToolDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CMabinogiResourceToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // MabinogiResourceToolView.cpp �еĵ��԰汾
inline CMabinogiResourceToolDoc* CMabinogiResourceToolView::GetDocument() const
   { return reinterpret_cast<CMabinogiResourceToolDoc*>(m_pDocument); }
#endif

