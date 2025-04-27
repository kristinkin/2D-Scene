#pragma once
#include<stdio.h>

typedef struct Scene {
    void* objects;
    int x1, x2, y1, y2;
    int n_messages;
} Scene;

void print_message(struct Scene* self, int n_str, ...);
void draw_corners(struct Scene* self);
void draw_pixel(struct Scene* self, int x, int y, int color, const char* simbol);
void draw_scene(struct Scene* self);
void destroy_scene(struct Scene* self);
Scene* create_scene(FILE* file);


