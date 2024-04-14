#include "QuiSoftRendererMainWindow.h"
#include "ui_QuiSoftRendererMainWindow.h"
#include "core/QtConfig.h"

#include <QPainter>

#include "algorithm/QtMathLibrary.h"

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
	//renderSnowflack();
	renderMultiLine();
}

void QuiSoftRendererMainWindow::renderSnowflack()
{
	for (unsigned i(0); i < QtGlobal::canvasWidth; ++i)
	{
		for (unsigned j(0); j < QtGlobal::canvasHeight; ++j)
		{
			unsigned char val = std::rand() % 255;

			QtPoint point(i, j, QtColor(val, val, val));
			m_canvas->drawPoint(point);
		}
	}
}

void QuiSoftRendererMainWindow::renderMultiLine()
{
	const int radius = 200;
	QtPoint center{ 400, 400, QtColor{255, 0, 0} };
	for (float i(0.f); i < 360.f; i += 10)
	{
		float radian = QtMathLibrary::deg2rad(i);
		unsigned x = radius * std::sin(radian) + center.cx();
		unsigned y = radius * std::cos(radian) + center.cy();

		QtPoint pt{ x, y, QtColor{0, 0, 255}};
		m_canvas->drawLine(center, pt, DrawLineType::DLT_DDA);
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