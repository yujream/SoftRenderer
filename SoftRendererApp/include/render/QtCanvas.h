#ifndef __QT_CANVAS_H__
#define __QT_CANVAS_H__

#include <qobject.h>

#include "QtFrameBuffer.h"
#include "core/QtColor.h"
#include "QtRender.h"
#include "core/QtConfig.h"

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

private:
	QtFrameBuffer* m_canvasBuffer{ nullptr };

	QtRender* m_paint;
};

#endif