// BoundaryFillDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication3.h"
#include "BoundaryFillDlg.h"
#include "afxdialogex.h"


// BoundaryFillDlg 对话框

IMPLEMENT_DYNAMIC(BoundaryFillDlg, CDialog)

BoundaryFillDlg::BoundaryFillDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, LUX(_T(""))
	, LUY(_T(""))
	, RDX(_T(""))
	, RDY(_T(""))
	, SX(_T(""))
	, SY(_T(""))
{

}

BoundaryFillDlg::~BoundaryFillDlg()
{
}

void BoundaryFillDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LUX, LUX);
	//  DDX_Control(pDX, IDC_LUY, LUY);
	//  DDX_Control(pDX, IDC_RDX, RDX);
	//  DDX_Control(pDX, IDC_RDY, RDY);
	//  DDX_Control(pDX, IDC_SX, SX);
	//  DDX_Control(pDX, IDC_SY, SY);
	//  DDX_Control(pDX, IDCANCEL, CANCEL);
	//  DDX_Control(pDX, IDOK, OK);
	//  DDX_Text(pDX, IDC_LUX, LUX);
	//  DDX_Text(pDX, IDC_LUY, LUY);
	//  DDX_Text(pDX, IDC_RDX, RDX);
	//  DDX_Text(pDX, IDC_RDY, RDY);
	DDX_Text(pDX, IDC_LUX, LUX);
	DDX_Text(pDX, IDC_LUY, LUY);
	//  DDX_Control(pDX, IDC_RDX, RDX);
	//  DDX_Control(pDX, IDC_RDY, RDY);
	DDX_Text(pDX, IDC_SX, SX);
	DDX_Text(pDX, IDC_RDX, RDX);
	DDX_Text(pDX, IDC_RDY, RDY);
	DDX_Text(pDX, IDC_SY, SY);
}


BEGIN_MESSAGE_MAP(BoundaryFillDlg, CDialog)
END_MESSAGE_MAP()


// BoundaryFillDlg 消息处理程序
