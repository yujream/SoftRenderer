#ifndef __QT_FRAME_BUFFER_H__
#define __QT_FRAME_BUFFER_H__

#include "core/QtColor.h"

/*
 * 存储当前画布对应的 bmp 内存指针，作为当前绘图画板
 */

class QtFrameBuffer
{
public:
	QtFrameBuffer(int width, int height, void* buffer = nullptr);
	~QtFrameBuffer();

	QtFrameBuffer(const QtFrameBuffer&) = delete;

public:
	void setPixel(int x, int y, const QtColor& color);
	QtColor getPixel(int x, int y);

	void fill(const QtColor& color);

	int width() const;
	int height() const;
	QtColor* buffer() const;

private:
	int m_width{ 0 };
	int m_height{ 0 };
	QtColor* m_colorBuffer{ nullptr };
};

#endif