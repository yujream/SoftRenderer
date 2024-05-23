#ifndef __QT_IMAGE_H__
#define __QT_IMAGE_H__

union QtColor;

class QtImage
{
public:
	QtImage(int width, int height, int channels, QtColor* data);
	~QtImage();

	QtColor* data() const;
	int width() const;
	int height() const;

private:
	int m_width;
	int m_height;
	int m_channels;
	QtColor* m_data;
};

class QtImageUtils
{
public:
	static QtImage* createImage(const char* path);
};

#endif