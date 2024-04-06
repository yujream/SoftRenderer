#pragma once

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class QtSoftRendererMainWindow; };
QT_END_NAMESPACE

class QtSoftRendererMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QtSoftRendererMainWindow(QWidget *parent = nullptr);
	~QtSoftRendererMainWindow();

private:
	void initUi();

private:
	Ui::QtSoftRendererMainWindow *ui;
};
