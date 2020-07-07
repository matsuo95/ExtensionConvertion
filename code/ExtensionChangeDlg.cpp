
// ExtensionChangeDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "ExtensionChange.h"
#include "ExtensionChangeDlg.h"
#include "afxdialogex.h"

#include "Conversion.h"
#include <atlpath.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CExtensionChangeDlg ダイアログ



CExtensionChangeDlg::CExtensionChangeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXTENSIONCHANGE_DIALOG, pParent)
	, m_displaypath_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExtensionChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_displaypath);
	DDX_Text(pDX, IDC_EDIT1, m_displaypath_text);
	DDX_Control(pDX, IDC_EDIT2, m_edit_previous_extension);
	DDX_Control(pDX, IDC_EDIT3, m_edit_after_extension);
	DDX_Control(pDX, IDC_LIST1, m_list_displaypath);
}

BEGIN_MESSAGE_MAP(CExtensionChangeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CExtensionChangeDlg::OnBnClickedReferenceButton)
	ON_BN_CLICKED(IDC_BUTTON2, &CExtensionChangeDlg::OnBnClickedConversionButton)
	ON_BN_CLICKED(IDC_BUTTON4, &CExtensionChangeDlg::OnBnClickedReferenceListButton)
	ON_BN_CLICKED(IDC_BUTTON3, &CExtensionChangeDlg::OnBnClickedConversionListButton)
	ON_BN_CLICKED(IDC_BUTTON5, &CExtensionChangeDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CExtensionChangeDlg メッセージ ハンドラー

BOOL CExtensionChangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	CString previous_extension_default("116");
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(previous_extension_default);

	CString after_extension_default("198");
	((CEdit*)GetDlgItem(IDC_EDIT3))->SetWindowText(after_extension_default);

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CExtensionChangeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CExtensionChangeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CExtensionChangeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExtensionChangeDlg::OnBnClickedReferenceButton()
{
	CString PreviousExtension;
	m_edit_previous_extension.GetWindowTextW(PreviousExtension);

	CString txt1("(*."),txt2(")|*."),txt3(";||");

	CString filter(txt1 + PreviousExtension + txt2 + PreviousExtension + txt3);
	CFileDialog selDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter);

	if (selDlg.DoModal() == IDOK)
	{
		m_displaypath_text = selDlg.GetPathName();
		UpdateData(FALSE);
	}
	
	return;
}

void CExtensionChangeDlg::OnBnClickedConversionButton()
{
	CString PreviousExtension, AfterExtension,DisplayPath;

	m_edit_previous_extension.GetWindowTextW(PreviousExtension);
	m_edit_after_extension.GetWindowTextW(AfterExtension);
	m_edit_displaypath.GetWindowTextW(DisplayPath);

	Conversion after_conversion = Conversion(PreviousExtension, AfterExtension);
	after_conversion.RenameExtension(DisplayPath);

	return;
}

void CExtensionChangeDlg::OnBnClickedReferenceListButton()
{
	CString PreviousExtension;
	m_edit_previous_extension.GetWindowTextW(PreviousExtension);

	CString txt1("(*."), txt2(")|*."), txt3(";||");

	CString filter(txt1 + PreviousExtension + txt2 + PreviousExtension + txt3);
	CString         filePath, strBuf;
	POSITION        pos = NULL;
	CFileDialog     selDlg(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, filter);
	int             err = 0, lbErr = 0;

	// ファイル名リスト用メモリ確保
	if (!err)
	{
		try
		{
			selDlg.GetOFN().lpstrFile = strBuf.GetBuffer(MAX_PATH * 100);
			selDlg.GetOFN().nMaxFile = MAX_PATH * 100;
		}
		catch (...) { err = 1; }
	}
	if (!err) if (selDlg.DoModal() != IDOK) err = 1;
	if (!err) if ((pos = selDlg.GetStartPosition()) == NULL) err = 1;
	if (!err)
	{
		while (pos)
		{
			filePath = selDlg.GetNextPathName(pos);
			if (!err)
			{
				lbErr = m_list_displaypath.InsertString(-1, filePath);
				if (lbErr == LB_ERR || lbErr == LB_ERRSPACE) err = 1;
			}
			if (err) break;
		}
		UpdateData(FALSE);
	}
	strBuf.ReleaseBuffer();

	return;
}

void CExtensionChangeDlg::OnBnClickedConversionListButton()
{
	CString filepath;
	CString PreviousExtension, AfterExtension;

	m_edit_previous_extension.GetWindowTextW(PreviousExtension);
	m_edit_after_extension.GetWindowTextW(AfterExtension);

	Conversion after_conversion = Conversion(PreviousExtension, AfterExtension);

	for (int i = 0; i < m_list_displaypath.GetCount(); i++) {
		m_list_displaypath.GetText(i, filepath);
		after_conversion.RenameExtension(filepath);
	}
}

int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg)
	{
	case BFFM_INITIALIZED:
		SendMessage(hWnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);
		break;
	case BFFM_SELCHANGED:
		break;
	}
	return 0;
}

BOOL SelectFolder(HWND hWnd,LPCTSTR lpDefFolder,LPTSTR lpSelectPath,UINT nFlag,LPCTSTR lpTitle)
{
	LPMALLOC pMalloc;
	BOOL bRet = FALSE;

	char chSelectPath[sizeof(lpSelectPath)];
	char chDefFolder[sizeof(lpDefFolder)];
	WideCharToMultiByte(CP_ACP, 0, lpSelectPath, -1, chSelectPath, sizeof(chSelectPath), NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, lpDefFolder, -1, chDefFolder, sizeof(chDefFolder), NULL, NULL);

	if (SUCCEEDED(SHGetMalloc(&pMalloc))) {
		BROWSEINFO browsInfo;
		ITEMIDLIST *pIDlist;

		memset(&browsInfo, NULL, sizeof(browsInfo));

		browsInfo.hwndOwner = hWnd;
		browsInfo.pidlRoot = NULL;
		browsInfo.pszDisplayName = lpSelectPath;
		browsInfo.lpszTitle = lpTitle;
		browsInfo.ulFlags = nFlag;
		browsInfo.lpfn = &BrowseCallbackProc;
		browsInfo.lParam = (LPARAM)lpDefFolder;
		browsInfo.iImage = (int)NULL;

		pIDlist = SHBrowseForFolder(&browsInfo);
		if (NULL == pIDlist) {
			strcpy_s(chSelectPath, MAX_PATH, chDefFolder);
		}
		else {
			SHGetPathFromIDList(pIDlist, lpSelectPath);
			bRet = TRUE;
			pMalloc->Free(pIDlist);
		}
		pMalloc->Release();
	}
	return bRet;
}

BOOL CExtensionChangeDlg::GetFileList(CString path)
{
	// ファイル検索を開始します。
	CFileFind fileFind;
	BOOL bResult = fileFind.FindFile(path);

	// ファイル検索ができない場合、終了します。
	if (!bResult) return FALSE;

	// ファイルが検索できる間繰り返します。
	do
	{
		// ファイルを検索します。
		// 次のファイル・ディレクトリがない場合、FALSEが返却されます。
		bResult = fileFind.FindNextFile();

		// "."または".."の場合、次を検索します。
		if (fileFind.IsDots()) continue;

		// 検索した結果がディレクトリの場合
		CString msg;
		CString filePath = fileFind.GetFilePath();
		if (fileFind.IsDirectory())
		{
			msg.Format(_T("Directory:%s\n"), filePath);
			AfxOutputDebugString(msg);

			// サブディレクトリを検索する場合、再帰呼出しします。
			CPath subDir = filePath;
			// ディレクトリ内のすべてのファイル・ディレクトリを対象とするため
			// ワイルドカード"*"を指定します。
			subDir.Append(_T("*"));
			GetFileList(subDir);
		}

		// ファイルの場合
		else
		{
			CString PreviousExtension;
			m_edit_previous_extension.GetWindowTextW(PreviousExtension);

			string str_filePath = CStringA(filePath).GetBuffer();
			string str_PreviousExtension = CStringA(PreviousExtension).GetBuffer();

			if (str_filePath.find(str_PreviousExtension) != std::string::npos) {

				m_list_displaypath.AddString(filePath);
			}
		}
	} while (bResult);

	return TRUE;
}

void CExtensionChangeDlg::OnBnClickedButton5()
{
	char dir[MAX_PATH] = { '\0' };

	const int tchrSize = sizeof(dir) + 1;
	TCHAR tchrText2[tchrSize] = { _T('¥0') };
	int res = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, dir, sizeof(dir), tchrText2, tchrSize);

	UpdateData(TRUE);

	BOOL bRes = SelectFolder(
		this->m_hWnd,
		NULL,
		tchrText2,
		BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE,
		_T("フォルダーを選択してください。")
	);

	if (bRes) {
		GetFileList(tchrText2);
	}
}