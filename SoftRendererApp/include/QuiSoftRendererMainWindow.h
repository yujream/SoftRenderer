#pragma once

#include <QMainWindow>
#include "render/QtCanvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QuiSoftRendererMainWindow; };
QT_END_NAMESPACE

class QuiSoftRendererMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QuiSoftRendererMainWindow(QWidget *parent = nullptr);
	~QuiSoftRendererMainWindow();


protected:
	void paintEvent(QPaintEvent* event) override;

private:
	void initUi();

private:
	void render();
	void renderSnowflack();
	void renderMultiLine();
	void renderTriangle();
	void renderImage();
	void renderTriangleWithTexture();
	void renderTextureWrap();
	void pasteToDC();

private:
	Ui::QuiSoftRendererMainWindow* ui;

	QtCanvas* m_canvas{ nullptr };

	// wrap test
	QtPoint m_p1{ 0, 0, QtColor{255, 0, 0}, 0.f, 0.f };
	QtPoint m_p2{ 0, 500, QtColor{255, 0, 0}, 0.f, 1.f };
	QtPoint m_p3{ 500, 0, QtColor{255, 0, 0}, 1.f, 0.f };
	QtPoint m_p4{ 500, 0, QtColor{255, 0, 0}, 1.f, 0.f };
	QtPoint m_p5{ 0, 500, QtColor{255, 0, 0},0.f, 1.f };
	QtPoint m_p6{ 500, 500, QtColor{255, 0, 0}, 1.f, 1.f };

	float m_speed{ 0.02 };
};
