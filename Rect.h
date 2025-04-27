#pragma once

struct Rect {
	const void* Object;
	int x1, y1, x2, y2;
	int color;
};

extern const void* Rect;
