#define _CRT_SECURE_NO_WARNINGS

#include <crtdbg.h>
#include <stdio.h>
#include "scene.h"
int main(int argc, char** argv)
{
    FILE* file = NULL;
    if (argc >= 2) {
        file = fopen(argv[1], "r");
        if (!file) {
            printf("can't open this file!\n");
            return 1;
        }
    }
    else if (argc == 1) {
        file = fopen("scene.txt", "r");
        if (!file) {
            printf("can't open this file!\n");
            return 1;
        }
    }
    else {
        printf("invalid input!\n");
        return 1;
    }

    Scene* scene = create_scene(file);
    draw_scene(scene);
    destroy_scene(scene);
    fclose(file);

    _CrtDumpMemoryLeaks();
    return 0;
}