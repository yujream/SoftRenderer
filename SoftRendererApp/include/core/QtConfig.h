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

#endif
