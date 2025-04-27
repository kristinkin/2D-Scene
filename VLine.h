#pragma once
#include"Object.h"

struct VLine {
	const void* object;
	int x, y1, y2;
	int color;
};

extern const void* VLine;