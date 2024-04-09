#include "QuiSoftRendererMainWindow.h"
#include "ui_QuiSoftRendererMainWindow.h"
#include "core/QtConfig.h"

#include <QPainter>

QuiSoftRendererMainWindow::QuiSoftRendererMainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::QuiSoftRendererMainWindow())
{
	ui->setupUi(this);
	this->resize(QtGlobal::canvasWidth, QtGlobal::canvasHeight);
	this->setWindowTitle(tr("2D soft renderer"));
	initUi();
}

QuiSoftRendererMainWindow::~QuiSoftRendererMainWindow()
{
	delete ui;
}

void QuiSoftRendererMainWindow::paintEvent(QPaintEvent* event)
{
	render();
	pasteToDC();
	QMainWindow::paintEvent(event);
}

void QuiSoftRendererMainWindow::initUi()
{
	m_canvas = new QtCanvas(this);
	m_canvas->newCanvas(QtGlobal::canvasWidth, QtGlobal::canvasHeight);
}

void QuiSoftRendererMainWindow::render()
{
	m_canvas->clear();
	renderSnowflack();
}

void QuiSoftRendererMainWindow::renderSnowflack()
{
	for (unsigned i(0); i < QtGlobal::canvasWidth; ++i)
	{
		for (unsigned j(0); j < QtGlobal::canvasHeight; ++j)
		{
			unsigned char val = std::rand() % 255;
			QtColor color(val, val, val);
			m_canvas->drawPoint(i, j, color);
		}
	}
}

void QuiSoftRendererMainWindow::pasteToDC()
{
	unsigned char* imageData = static_cast<unsigned char*>(m_canvas->getCanvas());
	QImage image(imageData, QtGlobal::canvasWidth, QtGlobal::canvasHeight, QImage::Format_RGBA8888);

	QPainter paint(this);
	paint.drawImage(this->rect(), image);

	this->update();
}
