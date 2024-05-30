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
	void pasteToDC();

private:
	Ui::QuiSoftRendererMainWindow* ui;

	QtCanvas* m_canvas{ nullptr };
};
