#include "QtSoftRendererMainWindow.h"
#include "ui_QtSoftRendererMainWindow.h"

QtSoftRendererMainWindow::QtSoftRendererMainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::QtSoftRendererMainWindow())
{
	ui->setupUi(this);
	initUi();
}

QtSoftRendererMainWindow::~QtSoftRendererMainWindow()
{
	delete ui;
}

void QtSoftRendererMainWindow::initUi()
{
	this->resize(1200, 800);
	this->setWindowTitle(tr("2D soft renderer"));
}
