
// HomeworkDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Homework.h"
#include "HomeworkDlg.h"
#include "afxdialogex.h"
#include "stdafx.h"

#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\imgproc\types_c.h>
#include <opencv2\objdetect\objdetect_c.h>

#include "face_recognition.h"


using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CString BmpName1;
CString BmpName2;

CEdit m_edit1;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CHomeworkDlg 对话框



CHomeworkDlg::CHomeworkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOMEWORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHomeworkDlg::DoDataExchange(CDataExchange* pDX)
{
	
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHomeworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHomeworkDlg::OnBnClickedButton1)
	//ON_EN_CHANGE(IDC_EDIT1, &CHomeworkDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHomeworkDlg::OnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CHomeworkDlg::OnClickedButton3)
END_MESSAGE_MAP()


// CHomeworkDlg 消息处理程序

BOOL CHomeworkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	CString ss = L"开启匹配";
	SetDlgItemText(IDC_STATIC_TEXT, ss);
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHomeworkDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHomeworkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHomeworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHomeworkDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	//从资源中加载图片
	CBitmap bitmap;
	//加载指定位图资源 Bmp图片ID
	bitmap.LoadBitmap(IDB_BITMAP1);
	//获取对话框上的句柄 图片控件ID
	CStatic *p = (CStatic *)GetDlgItem(IDC_STATIC_PIC);
	//设置静态控件窗口风格为位图居中显示
	p->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	//将图片设置到Picture控件上
	p->SetBitmap(bitmap);
	*/
	//打开文件 定义四种格式的文件bmp gif jpg tiff
	CString filter;
	filter = "所有文件(*.bmp,*.jpg,*.gif,*tiff)|*.bmp;*.jpg;*.gif;*.tiff| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg| GIF(*.gif)|*.gif| TIFF(*.tiff)|*.tiff||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	//按下确定按钮 dlg.DoModal() 函数显示对话框
	if (dlg.DoModal() == IDOK)
	{
		//打开对话框获取图像信息
		BmpName1 = dlg.GetPathName();     //获取文件路径名   如D:\pic\abc.bmp
		CString EntName = dlg.GetFileExt();      //获取文件扩展名
		EntName.MakeLower();                     //将文件扩展名转换为一个小写字符

		if (EntName.Compare(_T("bmp")) == 0)
		{
			//定义变量存储图片信息
			BITMAPINFO *pBmpInfo;       //记录图像细节
			BYTE *pBmpData;             //图像数据
			BITMAPFILEHEADER bmpHeader; //文件头
			BITMAPINFOHEADER bmpInfo;   //信息头
			CFile bmpFile;              //记录打开文件

			//以只读的方式打开文件 读取bmp图片各部分 bmp文件头 信息 数据
			if (!bmpFile.Open(BmpName1, CFile::modeRead | CFile::typeBinary))
				return;
			if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
				return;
			if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
				return;
			pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
			//为图像数据申请空间
			memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
			DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
			pBmpData = (BYTE*)new char[dataBytes];
			bmpFile.Read(pBmpData, dataBytes);
			bmpFile.Close();

			//显示图像
			CWnd *pWnd = GetDlgItem(IDC_STATIC_PIC); //获得pictrue控件窗口的句柄
			CRect rect;
			pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
			CDC *pDC = pWnd->GetDC(); //获得pictrue控件的DC
			pDC->SetStretchBltMode(COLORONCOLOR);
			StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
				bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
		}
	}
}


void CHomeworkDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CHomeworkDlg::OnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filter;
	filter = "所有文件(*.bmp,*.jpg,*.gif,*tiff)|*.bmp;*.jpg;*.gif;*.tiff| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg| GIF(*.gif)|*.gif| TIFF(*.tiff)|*.tiff||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	//按下确定按钮 dlg.DoModal() 函数显示对话框
	if (dlg.DoModal() == IDOK)
	{
		//打开对话框获取图像信息
		BmpName2 = dlg.GetPathName();     //获取文件路径名   如D:\pic\abc.bmp
		CString EntName = dlg.GetFileExt();      //获取文件扩展名
		EntName.MakeLower();                     //将文件扩展名转换为一个小写字符

		if (EntName.Compare(_T("bmp")) == 0)
		{
			//定义变量存储图片信息
			BITMAPINFO *pBmpInfo;       //记录图像细节
			BYTE *pBmpData;             //图像数据
			BITMAPFILEHEADER bmpHeader; //文件头
			BITMAPINFOHEADER bmpInfo;   //信息头
			CFile bmpFile;              //记录打开文件

			//以只读的方式打开文件 读取bmp图片各部分 bmp文件头 信息 数据
			if (!bmpFile.Open(BmpName2, CFile::modeRead | CFile::typeBinary))
				return;
			if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
				return;
			if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
				return;
			pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
			//为图像数据申请空间
			memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
			DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
			pBmpData = (BYTE*)new char[dataBytes];
			bmpFile.Read(pBmpData, dataBytes);
			bmpFile.Close();

			//显示图像
			CWnd *pWnd = GetDlgItem(IDC_STATIC_PIC1); //获得pictrue控件窗口的句柄
			CRect rect;
			pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
			CDC *pDC = pWnd->GetDC(); //获得pictrue控件的DC
			pDC->SetStretchBltMode(COLORONCOLOR);
			StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
				bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
		}
	}
}


void CHomeworkDlg::OnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat image1, image2;
	String path1, path2;

	CascadeClassifier faceDetector;
	string faceCascadeFilename = "C:\\Users\\yn\\source\\repos\\algorithm\\Homework\\haarcascade_frontalface_default.xml";
	
	wstring ws1(BmpName1);
	path1.assign(ws1.begin(), ws1.end());
	image1 = imread(path1, IMREAD_COLOR);
	Mat gray_image1;
	cvtColor(image1, gray_image1, CV_BGR2GRAY);

	imshow("", gray_image1);
	waitKey(0);

	wstring ws2(BmpName2);
	path2.assign(ws2.begin(), ws2.end());
	image2 = imread(path2, IMREAD_COLOR);
	Mat gray_image2;
	cvtColor(image2, gray_image2, CV_BGR2GRAY);
	

	//人脸检测用Cascade Classifier::detectMultiScale来进行人脸检测

	if (!faceDetector.load(faceCascadeFilename)) {
		printf("[error] 无法加载级联分类器文件！\n");
	}

	int flags = CASCADE_FIND_BIGGEST_OBJECT | CASCADE_DO_ROUGH_SEARCH;	//只检测脸最大的人
	//int flags = CASCADE_SCALE_IMAGE;	//检测多个人
	Size minFeatureSize(30, 30);
	float searchScaleFactor = 1.1f;
	int minNeighbors = 4;
	vector<Rect> face1, face2;
	faceDetector.detectMultiScale(gray_image1, face1, searchScaleFactor, minNeighbors, flags, minFeatureSize);
	faceDetector.detectMultiScale(gray_image2, face2, searchScaleFactor, minNeighbors, flags, minFeatureSize);
	//画矩形框
	Mat detect_face, template_face;
	/*for (size_t i = 0; i < faces.size(); i++)
	{
		if (faces[i].height > 0 && faces[i].width > 0)
		{
			face = image1(faces[i]);
			text_lb = Point(faces[i].x, faces[i].y);
			rectangle(image1, faces[i], Scalar(255, 0, 0), 1, 8, 0);
		}
	}*/

	cvtColor(image1, gray_image1, CV_BGR2GRAY);
	cvtColor(image1, gray_image1, CV_BGR2GRAY);

	detect_face = gray_image1(face1[0]);
	template_face = gray_image2(face2[0]);

	imshow("", detect_face);

	bool match = false;
	match = matchFace(detect_face, template_face);
	if (match)
	{
		CString s1 = L"匹配成功！";
		SetDlgItemText(IDC_STATIC_TEXT, s1);
	}
	else
	{
		CString s1 = L"匹配失败！";
		SetDlgItemText(IDC_STATIC_TEXT, s1);
	}
}



