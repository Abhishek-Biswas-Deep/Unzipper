#include <stdio.h>
#include <assert.h>

typedef struct sym {
    unsigned char sym;
    unsigned short len;
    unsigned short bits;
} sym;

static sym * find_sym(sym *symbols, int table_size, int len, unsigned bits) {
    for (int i = 0; i < table_size; i++) {
        if (symbols[i].len == len && symbols[i].bits == bits) {
            return &symbols[i];
        }
    }
    return NULL;
}

int main() {
    int table_size;

    scanf("%x", &table_size);

    sym symbols[table_size];

    for (int i = 0; i < table_size; i++) {
        unsigned int bits[2];
        int c;
        scanf("%x %x %x", &c, &bits[0], &bits[1]);
        symbols[i].sym = c;
        unsigned int len = bits[0] >> 4;
        symbols[i].len = len;
        symbols[i].bits = (bits[0] & 0xf);
        if (len < 4) {
            symbols[i].bits >>= 4 - len;
        } else {
            symbols[i].bits <<= len - 4;
            symbols[i].bits |= bits[1] >> (12 - len);
        }
    }

    int len = 0;
    for (int i = 0; i < 4; i++) {
        unsigned char b;
        scanf("%hhx", &b);
        len = (len << 8) | b;
    }

    if (len == 0) {
        for (int i = 0; i < table_size; i++) {
            printf("0x%2.2x : %d ", symbols[i].sym, symbols[i].len);
            for (int j = symbols[i].len - 1; j >= 0; j--) {
                printf("%u", (symbols[i].bits >> j) & 1);
            }
            printf("\n");
        }
        return 0;
    }

    unsigned char byte;
    unsigned remaining = 0;

    for (int i = 0; i < len; i++) {
        unsigned short bits = 0;
        sym *found = NULL;
        for (int j = 0; !found; j++) {
            assert(j < 13);

            if (remaining == 0) {
                scanf("%hhx", &byte);
                remaining = 8;
            }
            remaining--;
            bits = (bits << 1) | ((byte >> remaining) & 1);

            found = find_sym(symbols, table_size, j + 1, bits);
        }
        printf("%c", found->sym);
    }
    return 0;
}
