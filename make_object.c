#include<string.h>
#include"make_object.h"

void* make_object(char str[], Scene* scene) {
    if (!scene)
        return NULL;
    char obj_name[128] = { 0 };
    int coords[4] = { 0, 0, 0, 0 };
    int num_coords = sscanf(str, "%s %d %d %d %d", obj_name, coords, coords + 1, coords + 2, coords + 3);
    if (!strcmp(obj_name, "point") && num_coords == 3) {
        return _new(Point, coords[0], coords[1]);
    }
    else if (!strcmp(obj_name, "rect") && num_coords == 5) {
        return _new(Rect, coords[0], coords[1], coords[2], coords[3]);
    }
    else if (!strcmp(obj_name, "vline") && num_coords == 4) {
        return _new(VLine, coords[0], coords[1], coords[2]);
    }
    else if (!strcmp(obj_name, "hline") && num_coords == 4) {
        return _new(HLine, coords[0], coords[1], coords[2]);
    }
    else {
        if (num_coords == 0 || strcmp(str, "\n"))
            print_message(scene, 2, "invalid input in line: ", str);
        return NULL;
    }
}