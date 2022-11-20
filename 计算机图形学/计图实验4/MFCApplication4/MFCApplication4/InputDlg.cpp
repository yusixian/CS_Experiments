// InputDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication4.h"
#include "InputDlg.h"
#include "afxdialogex.h"


// InputDlg 对话框

IMPLEMENT_DYNAMIC(InputDlg, CDialogEx)

InputDlg::InputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, EX(_T(""))
	, EY(_T(""))
	, SX(_T(""))
	, SY(_T(""))
{

}

InputDlg::~InputDlg()
{
}

void InputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EX, EX);
	DDX_Text(pDX, IDC_EY, EY);
	DDX_Text(pDX, IDC_SX, SX);
	DDX_Text(pDX, IDC_SY, SY);
}


BEGIN_MESSAGE_MAP(InputDlg, CDialogEx)
END_MESSAGE_MAP()


// InputDlg 消息处理程序
