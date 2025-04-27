#pragma once
#include <stddef.h>
#include <stdarg.h>
#include<stdlib.h>
#include"scene.h"

struct Object {
	size_t size;
	void* (*ctor) (void* self, va_list* app);
	void* (*dtor) (void* self);
	void (*draw) (const void* self, Scene* scene);
};

void* _new(const void* object, ...);
void _delete(void* item);
void draw(const void* self, Scene* scene);
