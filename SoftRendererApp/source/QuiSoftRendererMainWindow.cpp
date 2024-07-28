#include "QuiSoftRendererMainWindow.h"
#include "ui_QuiSoftRendererMainWindow.h"
#include "core/QtConfig.h"
#include "algorithm/MathTool.h"
#include "core/QtImage.h"
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
	//renderSnowflack();
	//renderMultiLine();
	//renderTriangle();
	//renderImage();
	//renderTriangleWithTexture();
	renderTextureWrap();
}

void QuiSoftRendererMainWindow::renderSnowflack()
{
	for (int i(0); i < QtGlobal::canvasWidth; ++i)
	{
		for (int j(0); j < QtGlobal::canvasHeight; ++j)
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
		float radian = math::MathTool::degreeToRadian(i);
		int x = radius * std::sin(radian) + center.cx();
		int y = radius * std::cos(radian) + center.cy();

		QtPoint pt{ x, y, QtColor{0, 0, 255}};
		m_canvas->drawLine(center, pt, DrawLineType::DLT_Mid);
	}
}

void QuiSoftRendererMainWindow::renderTriangle()
{
	QtPoint p1(0, 100, QtColor{ 255, 0, 0 });
	QtPoint p2(500, 100, QtColor{ 0, 255, 0 });
	QtPoint p3(250, 500, QtColor{ 0, 0, 255 });

	m_canvas->drawTriangle(p1, p2, p3);
}

void QuiSoftRendererMainWindow::renderImage()
{
	m_canvas->setBlendingEnabled(true);
	std::string path1 = R"(E:\Code\QT\SoftRenderer\assets\texture\map_01.png)";
	std::string path2 = R"(E:\Code\QT\SoftRenderer\assets\texture\map_02.png)";
	m_canvas->drawImageWithAlpha(path1.c_str(), 100, 100, 100);
	m_canvas->drawImageWithAlpha(path2.c_str(), 300, 300, 200);
}

void QuiSoftRendererMainWindow::renderTriangleWithTexture()
{
	std::string path = R"(E:\Code\QT\SoftRenderer\assets\texture\map_01.png)";
	QtImage* image = QtImageUtils::createImage(path.c_str());
	if (nullptr == image)
	{
		return;
	}
	m_canvas->setTexture(image);

	QtPoint p1(0, 100, QtColor{ 255, 0, 0 });
	p1.setUV(0, 0);
	QtPoint p2(500, 100, QtColor{ 0, 255, 0 });
	p2.setUV(1, 0);
	QtPoint p3(250, 500, QtColor{ 0, 0, 255 });
	p3.setUV(0.5, 1);
	m_canvas->drawTriangle(p1, p2, p3);
}

void QuiSoftRendererMainWindow::renderTextureWrap()
{
	std::string path = R"(E:\Code\QT\SoftRenderer\assets\texture\map_01.png)";
	QtImage* image = QtImageUtils::createImage(path.c_str());
	if (nullptr == image)
	{
		return;
	}
	m_canvas->setTexture(image);

	m_p1.setU(m_p1.cu() + m_speed);
	m_p2.setU(m_p2.cu() + m_speed);
	m_p3.setU(m_p3.cu() + m_speed);
	m_p4.setU(m_p4.cu() + m_speed);
	m_p5.setU(m_p5.cu() + m_speed);
	m_p6.setU(m_p6.cu() + m_speed);

	m_canvas->drawTriangle(m_p1, m_p2, m_p3);
	m_canvas->drawTriangle(m_p4, m_p5, m_p6);
}

void QuiSoftRendererMainWindow::pasteToDC()
{
	unsigned char* imageData = static_cast<unsigned char*>(m_canvas->getCanvas());
	QImage image(imageData, QtGlobal::canvasWidth, QtGlobal::canvasHeight, QImage::Format_RGBA8888);

	QPainter paint(this);
	paint.drawImage(this->rect(), image);

	this->update();
}
