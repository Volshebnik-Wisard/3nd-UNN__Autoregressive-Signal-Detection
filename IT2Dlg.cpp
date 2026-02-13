
// IT2Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "IT2.h"
#include "IT2Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define M_PI 3.14159265358979323846
using namespace std;


// Диалоговое окно CIT2Dlg
CIT2Dlg::CIT2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IT2_DIALOG, pParent)
	, f1(2)
	, f2(8)
	, f3(4)
	, fd(100)
	, N(1001)
	, n1(300)
	, n2(680)
	, nn1(0)
	, nn2(0)
	, t(0.06)
	, TT(50)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIT2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_f1, f1);
	DDX_Text(pDX, IDC_f2, f2);
	DDX_Text(pDX, IDC_f3, f3);
	DDX_Text(pDX, IDC_fd, fd);
	DDX_Text(pDX, IDC_N, N);
	DDX_Text(pDX, IDC_n1, n1);
	DDX_Text(pDX, IDC_n2, n2);
	DDX_Text(pDX, IDC_nn1, nn1);
	DDX_Text(pDX, IDC_nn2, nn2);
	DDX_Text(pDX, IDC_t, t);
	DDX_Text(pDX, IDC_TT, TT);
}

BEGIN_MESSAGE_MAP(CIT2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CIT2Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CIT2Dlg

BOOL CIT2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	SINS.Create(GetDlgItem(IDC_SINS)->GetSafeHwnd());
	MIS.Create(GetDlgItem(IDC_MIS)->GetSafeHwnd());
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CIT2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CIT2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CIT2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

double Sin(double f, double t, double phi) {
	return sin(2 * M_PI * f * t + phi);
}
//t=n/fd;

void CIT2Dlg::Unite() {
	for (int i = 0; i < n1; i++) {
		y.push_back(Sin(f1, i / fd, 0));
		dots.push_back(i);
		t_vec.push_back(t);
	}
	double phi2 = 2 * M_PI * n1 * (f1 - f2) / fd;
	for (int i = n1; i < n2; i++) {
		y.push_back(Sin(f2, i / fd, phi2));
		dots.push_back(i);
		t_vec.push_back(t);

	}
	double phi3 = 2 * M_PI * n2 * (f2 - f3) / fd + phi2;
	for (int i = n2; i < N; i++) {
		y.push_back(Sin(f3, i / fd, phi3));
		dots.push_back(i);
		t_vec.push_back(t);
	}
}

void CIT2Dlg::Find_diffs() {
	double w = 2 * M_PI * f2;
	double a1(-2 * cos(w / fd));
	pred.push_back(y[0]);
	diff.push_back(abs(y[0] - pred[0]));
	pred.push_back(-y[1] * a1);
	diff.push_back(abs(y[1] - pred[1]));
	for (int i = 2; i < N; i++) {
		double temp = -a1 * y[i - 1] - y[i - 2];
		pred.push_back(temp);
		diff.push_back(abs(pred[i] - y[i]));
	}
}

void CIT2Dlg::HPFilter() {
	dots.clear();
	cleaned_mis.clear();
	double temp(0);
	for (int i = TT / 2.; i < N - TT / 2.; i++) {
		for (int j = i - TT / 2; j < i + TT / 2; j++) {
			temp += diff[j];
		}
		cleaned_mis.push_back(temp / TT);
		dots.push_back((double)i);
		temp = 0;
	}
}

void CIT2Dlg::Find_borders() {
	bool first(false);
	for (int i = 0; i < N - TT; i++) {
		if (cleaned_mis[i] <= t && first == false) {
			first = true;
			nn1 = i + TT / 2;
		}
		if (cleaned_mis[i] <= t && first == true) {
			nn2 = i + TT / 2;
		}
	}
}

void CIT2Dlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	Unite();
	//рисуем первый график синусов
	SINS.DrawGrid(y, 1, dots, N, 0, 0);
	SINS.DrawPlot(y, 1, dots, N, 0, 0, 0);
	//находим разности, рисуем
	Find_diffs();
	double y_max_2 = *max_element(diff.begin(), diff.end());
	MIS.DrawGrid(diff, 2, dots, N, y_max_2, 0);
	MIS.DrawPlot(diff, 2, dots, N, y_max_2, 0, 0);
	//рисуем порог
	MIS.DrawPlot(t_vec, 4, dots, N, y_max_2, TT, t);

	dots.clear();
	//находим новые n1*, n2*
	HPFilter();
	Find_borders();
	MIS.DrawPlot(cleaned_mis, 3, dots, N - TT, y_max_2, TT, 0);

	//чистим память
	y.clear();
	dots.clear();
	diff.clear();
	pred.clear();
	t_vec.clear();
	cleaned_mis.clear();
	UpdateData(FALSE);
}
