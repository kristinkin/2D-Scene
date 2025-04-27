#include <stddef.h>
#include <stdarg.h>
#include"Object.h"
#include"HLine.h"

static void* HLine_ctor(void* _self, va_list* app) {
    struct HLine* self = _self;
    int x1 = va_arg(*app, int);
    int x2 = va_arg(*app, int);
    self->x1 = min(x1, x2);
    self->x2 = max(x1, x2);
    self->y = va_arg(*app, int);
    self->color = 4;

    return self;
}

static void HLine_draw(const void* _self, Scene* scene) {
    const struct HLine* self = _self;

    for (int i = self->x1; i <= self->x2; i++) {
        draw_pixel(scene, i, self->y, self->color, "_");
    }
}

static const struct Object _HLine = { sizeof(struct HLine), HLine_ctor, NULL, HLine_draw };

const void* HLine = &_HLine;