#ifndef __QT_CANVAS_H__
#define __QT_CANVAS_H__

#include <qobject.h>

#include "QtFrameBuffer.h"
#include "core/QtCore.h"

class QtImage;

class QtCanvas : public QObject
{
	Q_OBJECT
public:
	QtCanvas(QObject* parent = nullptr);
	~QtCanvas();

public:
	bool newCanvas(unsigned width, unsigned height);
	void* getCanvas() const;
	void clear();

	void drawPoint(const QtPoint& point);
	void drawLine(const QtPoint& p1, const QtPoint& p2, DrawLineType type = DrawLineType::DLT_Brensanham);
	void drawTriangle(const QtPoint& p1, const QtPoint& p2, const QtPoint& p3);
	void drawImage(const char* path, int x = 0, int y = 0);
	void drawImageWithAlpha(const char* path, int x = 0, int y = 0, unsigned char alpha = 255);

	void setBlendingEnabled(bool enable);
	void setBilinearityEnabled(bool enable);
	bool blendingEnable() const;
	bool bilinearity() const;

	void setTextrueWrap(const TextureWrap& wrap);

	void setTexture(QtImage* texture);

private:
	// 根据 uv 坐标采样像素点
	QtColor sampleTexture(float u, float v);
	// 双线性插值
	QtColor sampleBilinearity(float u, float v);
	// wrap
	void wrapUOrV(float& uOrV);

private:
	QtFrameBuffer* m_canvasBuffer{ nullptr };
	QtImage* m_texture{ nullptr };
	bool m_enableBlending{ false };
	bool m_enableBilinearity{ false };

	TextureWrap m_wrap{ TextureWrap::TW_Mirror };
};

#endif