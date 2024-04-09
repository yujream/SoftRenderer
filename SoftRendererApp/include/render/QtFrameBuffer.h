#ifndef __QT_FRAME_BUFFER_H__
#define __QT_FRAME_BUFFER_H__

#include "core/QtColor.h"

/*
 * 存储当前画布对应的 bmp 内存指针，作为当前绘图画板
 */

class QtFrameBuffer
{
public:
	QtFrameBuffer(unsigned width, unsigned height, void* buffer = nullptr);
	~QtFrameBuffer();

	QtFrameBuffer(const QtFrameBuffer&) = delete;

public:
	void setPixel(unsigned x, unsigned y, const QtColor& color);
	void fill(const QtColor& color);

	unsigned width() const;
	unsigned height() const;
	QtColor* buffer() const;

private:
	unsigned m_width{ 0 };
	unsigned m_height{ 0 };
	QtColor* m_colorBuffer{ nullptr };
};

#endif