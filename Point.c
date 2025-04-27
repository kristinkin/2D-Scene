#include <stddef.h>
#include <stdarg.h>
#include"Point.h"
#include"Object.h"
static void* Point_ctor(void* _self, va_list* app) {
    struct Point* self = _self;
    self->x = va_arg(*app, int);
    self->y = va_arg(*app, int);
    self->color = 1;

    return self;
}

static void Point_draw(const void* _self, Scene* scene) {
    const struct Point* self = _self;
    draw_pixel(scene, self->x, self->y, self->color, ".");
}

static const struct Object _Point = {
    sizeof(struct Point),
    Point_ctor,
    NULL,
    Point_draw
};

const void* Point = &_Point;