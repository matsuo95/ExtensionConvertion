
// ExtensionChangeDlg.h : ヘッダー ファイル
//

#pragma once


// CExtensionChangeDlg ダイアログ
class CExtensionChangeDlg : public CDialogEx
{
// コンストラクション
public:
	CExtensionChangeDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXTENSIONCHANGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_previous_extension;
	CEdit m_edit_after_extension;

	CListBox m_list_displaypath;

	afx_msg void OnBnClickedReferenceListButton();
	afx_msg void OnBnClickedConversionListButton();
	afx_msg void OnBnClickedReferenceFolderButton();

	BOOL SelectFolder(HWND hWnd, LPCTSTR lpDefFolder, LPTSTR lpSelectPath, UINT nFlag, LPCTSTR lpTitle);
	BOOL GetFileList(CString path,bool flag);
};