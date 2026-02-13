
// IT2Dlg.h: файл заголовка
//

#pragma once
#include "Drawer.h"

// Диалоговое окно CIT2Dlg
class CIT2Dlg : public CDialogEx
{
	// Создание
public:
	CIT2Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IT2_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


	// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	double f1;
	double f2;
	double f3;
	double fd;
	double N;
	double n1;
	double n2;
	double nn1;
	double nn2;
	Drawer SINS; //рисовалка трех синусов
	Drawer MIS; //рисовалка ошибок
	vector<double> y;//контейнер значений синусоид
	vector<double> pred; //контейнер прогноза
	vector<double> diff;//контейнер разностей 
	vector<double> cleaned_mis;//усредненные разности
	vector<double>dots;//контейнер значений по х
	vector<double> t_vec;//контейнер для рисовки порога
	void Unite();//сохранение значений срощенных синусоид
	void Find_diffs();//рассчет разностей
	void HPFilter();//фильтр частотный фильтр
	void Find_borders();//нахождение n1*, n2*
	double t;
	int TT;
};
