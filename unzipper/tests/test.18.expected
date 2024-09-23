#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "bitmap.h"

int main() {
    char command[10];
    int op;
    char *bitmap = NULL;
    int size = 0;

    while (scanf("%s %d", command, &op) == 2) {
        int print = 1;
        if (!strcmp(command, "new")) {
            bitmap = bitmap_new(op);
            size = (op + 7) / 8;
            assert(bitmap);
        } else if (!strcmp(command, "test")) {
            assert(bitmap);
            printf("%d\n", bitmap_test(bitmap, op));
            print = 0;
        } else if (!strcmp(command, "set")) {
            assert(bitmap);
            bitmap_set(bitmap, op);
        } else if (!strcmp(command, "reset")) {
            assert(bitmap);
            bitmap_reset(bitmap, op);
        } else if (!strcmp(command, "toggle")) {
            assert(bitmap);
            bitmap_toggle(bitmap, op);
        } else {
            break;
        }

        if (print) {
            for (int i = 0; i < size; i++){
                printf("%02x ", bitmap[i] & 0xff);
            }
            printf("\n");
        }
    }
    return 0;
}
