#include <stddef.h>
#include <stdarg.h>
#include <math.h>
#include"Object.h"
#include"VLine.h"

static void* VLine_ctor(void* _self, va_list* app) {
    struct VLine* self = _self;
    int y1 = va_arg(*app, int);
    int y2 = va_arg(*app, int);
    self->y1 = min(y1, y2);
    self->y2 = max(y1, y2);
    self->x = va_arg(*app, int);


    self->color = 3;

    return self;
}

static void VLine_draw(const void* _self, Scene* scene) {
    const struct VLine* self = _self;

    for (int i = self->y1; i <= self->y2; i++) {
        draw_pixel(scene, self->x, i, self->color, "|");
    }
}

static const struct Object _VLine = { sizeof(struct VLine), VLine_ctor, NULL, VLine_draw };

const void* VLine = &_VLine;