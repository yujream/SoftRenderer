#ifndef __QT_CONFIG_H__
#define __QT_CONFIG_H__

namespace QtGlobal
{
	const int canvasWidth = 1600;
	const int canvasHeight = 1200;
}

enum class DrawLineType
{
	DLT_DDA,
	DLT_Mid,
	DLT_Brensanham
};

enum class TextureWrap
{
	TW_Repeat,     // 重复
	TW_Mirror,     // 镜像
	TW_Stretch     // 拉伸
};

#endif
