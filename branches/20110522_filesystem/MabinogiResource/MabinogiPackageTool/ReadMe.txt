================================================================================
MICROSOFT �������: MabinogiPackageTool ��Ŀ����
===============================================================================

Ӧ�ó�������Ϊ����������� MabinogiPackageTool Ӧ�ó��򡣴�Ӧ�ó��򲻽���ʾ Microsoft ������Ļ���ʹ�÷�����������Ϊ����дӦ�ó������㡣

���ļ���Ҫ������� MabinogiPackageTool Ӧ�ó����ÿ���ļ������ݡ�

MabinogiPackageTool.vcxproj
����ʹ��Ӧ�ó��������ɵ� VC++ ��Ŀ������Ŀ�ļ��� 
���������ɸ��ļ��� Visual C++ �İ汾��Ϣ���Լ��й�ʹ��Ӧ�ó�����ѡ���ƽ̨�����ú���Ŀ���ܵ���Ϣ��

MabinogiPackageTool.vcxproj.filters
    ����ʹ�á�Ӧ�ó����򵼡����ɵ� VC++ ��Ŀɸѡ���ļ���
    �������й���Ŀ�ļ���ɸѡ��֮��Ĺ�����Ϣ���� IDE �У�ͨ�����ֹ��������ض��ڵ����Է�����ʽ��ʾ����������չ�����ļ������磬��.cpp���ļ��롰Դ�ļ���ɸѡ��������

MabinogiPackageTool.h
����Ӧ�ó������Ҫͷ�ļ���������������Ŀ�ض���ͷ�ļ�(���� Resource.h)�������� CMabinogiPackageToolApp Ӧ�ó����ࡣ

MabinogiPackageTool.cpp
���ǰ���Ӧ�ó����� CMabinogiPackageToolApp ����ҪӦ�ó���Դ�ļ���

MabinogiPackageTool.rc
���ǳ���ʹ�õ����� Microsoft Windows ��Դ���б������� RES ��Ŀ¼�д洢��ͼ�ꡢλͼ�͹�ꡣ���ļ�����ֱ���� Microsoft Visual C++ �н��б༭����Ŀ��Դλ�� 2052 �С�

res\MabinogiPackageTool.ico
��������Ӧ�ó���ͼ���ͼ���ļ�����ͼ���������Ҫ��Դ�ļ� MabinogiPackageTool.rc �С�

res\MabinogiPackageTool.rc2
���ļ��������� Microsoft Visual C++ �н��б༭����Դ����Ӧ�ý���������Դ�༭���༭��������Դ���ڴ��ļ��С�

MabinogiPackageTool.reg
����һ��ʾ�� .reg �ļ�������ʾ�˿�ܽ�Ϊ�����õ�ע�����õ����ࡣ���Խ�������
��������Ӧ�ó���һ��ʹ�õ� .reg �ļ����������Խ���ɾ����������Ĭ�ϵ� RegisterShellFileTypes ע�ᡣ


/////////////////////////////////////////////////////////////////////////////

��������ܴ���:
Windows ��Դ��������ʽ: ��Ŀ������ Windows ��Դ��������ʽ�Ľ��棬����������ܡ�

MainFrm.h, MainFrm.cpp
��Щ�ļ���������� CMainFrame������������
CMDIFrameWnd ���������� MDI ��ܹ��ܡ�

LeftView.h, LeftView.cpp
��Щ�ļ����������� CLeftView������������
CTreeView��

/////////////////////////////////////////////////////////////////////////////

�����ӿ�ܴ���:

ChildFrm.h��ChildFrm.cpp
��Щ�ļ����岢ʵ�� CChildFrame �࣬����֧�� MDI Ӧ�ó����е��Ӵ��ڡ�

/////////////////////////////////////////////////////////////////////////////

Ӧ�ó����򵼴���һ���ĵ����ͺ�һ����ͼ:

MabinogiPackageToolDoc.h��MabinogiPackageToolDoc.cpp - �ĵ�
��Щ�ļ����� CMabinogiPackageToolDoc �ࡣ�༭��Щ�ļ�������������ĵ����ݲ���ʵ���ļ�����ͼ���(ͨ�� CMabinogiPackageToolDoc::Serialize)��
�ĵ������������ַ���:
�ļ���չ��:      pack
�ļ����� ID:        MabinogiPackageTool.Document
����ܱ���:  MabinogiPackageTool
�ĵ���������:       MabinogiPackage
ɸѡ����:         ������Դѹ���� (*.pack)
�ļ����¼��: MabinogiPackage
�ļ�����ȫ��: MabinogiPackageTool.Document

MabinogiPackageToolView.h��MabinogiPackageToolView.cpp - �ĵ�����ͼ
��Щ�ļ����� CMabinogiPackageToolView �ࡣ
CMabinogiPackageToolView �������ڲ鿴 CMabinogiPackageToolDoc ����

res\MabinogiPackageToolDoc.ico
����ͼ���ļ��������� CMabinogiPackageToolDoc ��� MDI �Ӵ��ڵ�ͼ�ꡣ��ͼ���������Ҫ��Դ�ļ� MabinogiPackageTool.rc �С�




/////////////////////////////////////////////////////////////////////////////

������׼�ļ�:

StdAfx.h��StdAfx.cpp
��Щ�ļ�����������Ϊ MabinogiPackageTool.pch ��Ԥ����ͷ (PCH) �ļ�����Ϊ StdAfx.obj ��Ԥ���������ļ���

Resource.h
���Ǳ�׼ͷ�ļ����������µ���Դ ID��
Microsoft Visual C++ ��ȡ�����´��ļ���

MabinogiPackageTool.manifest
	Ӧ�ó����嵥�ļ��� Windows XP ��������Ӧ�ó���
	���ض��汾���г��򼯵������ԡ����س���ʹ�ô�
	��Ϣ�ӳ��򼯻�������ʵ��ĳ��򼯻�
	��Ӧ�ó������˽����Ϣ��Ӧ�ó����嵥����Ϊ�����·ַ�����Ϊ
	��Ӧ�ó����ִ���ļ���װ����ͬ�ļ����е��ⲿ .manifest �ļ�������
	Ҳ��������Դ����ʽ�����ڸÿ�ִ���ļ��С� 
/////////////////////////////////////////////////////////////////////////////

����ע��:

Ӧ�ó�����ʹ�á�TODO:��ָʾӦ��ӻ��Զ����Դ���벿�֡�

���Ӧ�ó����ڹ���� DLL ��ʹ�� MFC������Ҫ���·�����Щ MFC DLL�����Ӧ�ó������õ����������ϵͳ�ĵ�ǰ�������ò�ͬ������Ҫ���·�����Ӧ�ı��ػ���Դ MFC100XXX.DLL���й�����������ĸ�����Ϣ����μ� MSDN �ĵ����й� Redistributing Visual C++ applications (���·��� Visual C++ Ӧ�ó���)���½ڡ�

/////////////////////////////////////////////////////////////////////////////
