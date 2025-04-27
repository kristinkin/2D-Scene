#include <stddef.h>
#include <stdarg.h>
#include"Object.h"
#include"Rect.h"

static void* Rect_ctor(void* _self, va_list* app) {
    struct Rect* self = _self;
    int x1 = va_arg(*app, int);
    int y1 = va_arg(*app, int);
    int x2 = va_arg(*app, int);
    int y2 = va_arg(*app, int);

    self->x1 = min(x1, x2);
    self->x2 = max(x1, x2);
    self->y1 = min(y1, y2);
    self->y2 = max(y1, y2);

    self->color = 2;
    return self;
}

static void Rect_draw(const void* _self, Scene* scene) {
    const struct Rect* self = _self;

    for (int i = self->y1; i <= self->y2; i++) {
        for (int j = self->x1; j <= self->x2; j++) {
            draw_pixel(scene, j, i, self->color, "#");
        }
    }
    
}

static const struct Object _Rect = { sizeof(struct Rect), Rect_ctor, NULL, Rect_draw };

const void* Rect = &_Rect;