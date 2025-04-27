#include<stdlib.h>
#include<stdarg.h>
#include<assert.h>
#include"Object.h"

void* _new(const void* _object, ...){
	const struct Object* object = _object;
	void* p = calloc(1, object->size);
	assert(p);
	*(const struct Object**)p = object;
    if (object->ctor) {
        va_list ap;
        va_start(ap, _object);
        p = object->ctor(p, &ap);
        va_end(ap);
    }
    return p;
}

void _delete(void* self) {
    const struct Object** cp = self;
    if (self && *cp && (*cp)->dtor)
        self = (*cp)->dtor(self);
    free(self);
}

void draw(const void* self, Scene* scene) {
    const struct Object* const* cp = self;
    assert(self && *cp && (*cp)->draw);
    (*cp)->draw(self, scene);
}