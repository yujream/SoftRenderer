#ifndef __QT_CONFIG_H__
#define __QT_CONFIG_H__

namespace QtGlobal
{
	const int canvasWidth = 1200;
	const int canvasHeight = 800;
}

enum class DrawLineType
{
	DLT_DDA,
	DLT_Mid,
	DLT_Brensanham
};

#endif
