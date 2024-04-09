#ifndef __QT_CANVAS_H__
#define __QT_CANVAS_H__

#include <qobject.h>

#include "QtFrameBuffer.h"
#include "core/QtColor.h"
#include "QtPaint.h"

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

	void drawPoint(unsigned x, unsigned y, const QtColor& color);

private:
	QtFrameBuffer* m_canvasBuffer{ nullptr };

	QtPaint* m_paint;
};

#endif