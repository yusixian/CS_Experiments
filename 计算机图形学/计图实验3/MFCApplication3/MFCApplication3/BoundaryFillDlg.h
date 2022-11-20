#pragma once


// BoundaryFillDlg 对话框

class BoundaryFillDlg : public CDialog
{
	DECLARE_DYNAMIC(BoundaryFillDlg)

public:
	BoundaryFillDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~BoundaryFillDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString LUX;
	CString LUY;
	CString SX;
	CString RDX;
	CString RDY;
	CString SY;
};
