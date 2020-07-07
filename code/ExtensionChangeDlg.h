﻿
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
	afx_msg void OnBnClickedReferenceButton();
	CEdit m_edit_displaypath;
	CString m_displaypath_text;
	CEdit m_edit_previous_extension;
	CEdit m_edit_after_extension;
	afx_msg void OnBnClickedConversionButton();
	afx_msg void OnBnClickedReferenceListButton();
	CListBox m_list_displaypath;
	afx_msg void OnBnClickedConversionListButton();
	afx_msg void OnBnClickedButton5();
	BOOL GetFileList(CString path);
};