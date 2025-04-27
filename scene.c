#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#include <stdarg.h>

#include "console.h"
#include "dlist.h"
#include "scene.h"
#include "make_object.h"


void print_message(Scene* self, int n_str, ...) {
    con_gotoXY(self->x1, self->y2 + self->n_messages + 2);
    va_list text;
    va_start(text, n_str);
    for (int i = 0; i < n_str; i++) {
        printf(va_arg(text, char*));
    }
    va_end(text);
    self->n_messages++;
}

void init_console() {
    con_init();
    con_hideCursor();
    con_initPair(1, CON_COLOR_YELLOW, CON_COLOR_BLACK);
    con_initPair(2, CON_COLOR_GREEN, CON_COLOR_BLACK);
    con_initPair(3, CON_COLOR_RED, CON_COLOR_BLACK);
    con_initPair(4, CON_COLOR_BLUE, CON_COLOR_BLACK);
    
}

void draw_corners(Scene* self) {
    for (int x = self->x1; x <= self->x2; x++) {
        con_gotoXY(x, self->y1);
        con_outTxt("#");
        con_gotoXY(x, self->y2);
        con_outTxt("#");
    }
    for (int y = self->y1; y <= self->y2; y++) {
        con_gotoXY(self->x1, y);
        con_outTxt("#");
        con_gotoXY(self->x2, y);
        con_outTxt("#");
    }
}

void draw_pixel(Scene* self, int x, int y, int color, const char* simbol) {
    if (x > self->x1 &&
        x < self->x2 &&
        y > self->y1 &&
        y < self->y2) {
        con_gotoXY(x, y);
        con_setColor(color);
        con_outTxt(simbol);
    }
    
}

static void read_from_file(Scene* self, FILE* file) {
    char str[256];
    while (!feof(file)) {
        fgets(str, 256, file);
        void* new_object = make_object(str, self);
        if (new_object != NULL) {
            void** p = dlist_append(self->objects);
            if(p)
                *p = new_object;
        }
    }
}

void draw_scene(Scene* self) {
    if (!self)
        return;
    for (size_t node = dlist_first(self->objects); node != dlist_stop(self->objects); node = dlist_next(self->objects, node)) {
        void** p = (void**)dlist_current(self->objects, node);
        void* object = *p;
        draw(object, self);
    }
}

static void delete_obj(void* p) {
    void* object = *(void**)p;
    _delete(object);
}

void destroy_scene(Scene* self) {
    if (self) {
        dlist_destroy(self->objects, delete_obj);
        con_gotoXY(self->x1, self->y2 + self->n_messages + 2);
        free(self);
    }
    con_deinit();
}

Scene* create_scene(FILE* file) {
    if (!file) return NULL;

    init_console();

    Scene* scene = malloc(sizeof(Scene));
    if (!scene) return NULL;

    void* objects = dlist_create(sizeof(void*));
    if (!objects) {
        free(scene);
        return NULL;
    }
    scene->objects = objects;

    int num_success = fscanf(file, "%d %d %d %d\n", &scene->x1, &scene->y1, &scene->x2, &scene->y2);
    if (num_success != 4) {
        printf("invalid coordinates input\n");
        destroy_scene(scene);
        return NULL;
    }

    scene->n_messages = 0;
    read_from_file(scene, file);
    draw_corners(scene);

    return scene;
}