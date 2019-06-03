#include "hamming_16_11.h"

/*
generator matrix accodring to etsi B.3.4

1 0 0 0 0 0 0 0 0 0 0 1 0 0 1 1
0 1 0 0 0 0 0 0 0 0 0 1 1 0 1 0
0 0 1 0 0 0 0 0 0 0 0 1 1 1 1 1
0 0 0 1 0 0 0 0 0 0 0 1 1 1 0 0
0 0 0 0 1 0 0 0 0 0 0 0 1 1 1 0
0 0 0 0 0 1 0 0 0 0 0 1 0 1 0 1
0 0 0 0 0 0 1 0 0 0 0 0 1 0 1 1
0 0 0 0 0 0 0 1 0 0 0 1 0 1 1 0
0 0 0 0 0 0 0 0 1 0 0 1 1 0 0 1
0 0 0 0 0 0 0 0 0 1 0 0 1 1 0 1
0 0 0 0 0 0 0 0 0 0 1 0 0 1 1 1

parity check matrix according to H = [-PT|In-k]

1 1 1 1 0 1 0 1 1 0 0 1 0 0 0 0
0 1 1 1 1 0 1 0 1 1 0 0 1 0 0 0
0 0 1 1 1 1 0 1 0 1 1 0 0 1 0 0
1 1 1 0 1 0 1 1 0 0 1 0 0 0 1 0
1 0 1 0 0 1 1 0 1 1 1 0 0 0 0 1
*/

// parity check matrix as code
uint16_t hamming_16_11_parity_check_matrix[] = {
    0b1111010110010000,
    0b0111101011001000,
    0b0011110101100100,
    0b1110101100100010,
    0b1010011011100001
};

struct correction {
    uint16_t syndrome;
    uint16_t error_pattern;
};

// generated by applying possible combinations of errors
static struct correction corrections[] = {
    { 1, 1 },
    { 3, 3 },
    { 5, 5 },
    { 9, 9 },
    { 17, 17 },
    { 6, 33 },
    { 12, 65 },
    { 24, 129 },
    { 23, 257 },
    { 10, 513 },
    { 20, 1025 },
    { 15, 2049 },
    { 29, 4097 },
    { 30, 8193 },
    { 27, 16385 },
    { 18, 32769 },
    { 2, 2 },
    { 3, 3 },
    { 6, 6 },
    { 10, 10 },
    { 18, 18 },
    { 5, 34 },
    { 15, 66 },
    { 27, 130 },
    { 20, 258 },
    { 9, 514 },
    { 23, 1026 },
    { 12, 2050 },
    { 30, 4098 },
    { 29, 8194 },
    { 24, 16386 },
    { 17, 32770 },
    { 4, 4 },
    { 5, 5 },
    { 6, 6 },
    { 12, 12 },
    { 20, 20 },
    { 3, 36 },
    { 9, 68 },
    { 29, 132 },
    { 18, 260 },
    { 15, 516 },
    { 17, 1028 },
    { 10, 2052 },
    { 24, 4100 },
    { 27, 8196 },
    { 30, 16388 },
    { 23, 32772 },
    { 8, 8 },
    { 9, 9 },
    { 10, 10 },
    { 12, 12 },
    { 24, 24 },
    { 15, 40 },
    { 5, 72 },
    { 17, 136 },
    { 30, 264 },
    { 3, 520 },
    { 29, 1032 },
    { 6, 2056 },
    { 20, 4104 },
    { 23, 8200 },
    { 18, 16392 },
    { 27, 32776 },
    { 16, 16 },
    { 17, 17 },
    { 18, 18 },
    { 20, 20 },
    { 24, 24 },
    { 23, 48 },
    { 29, 80 },
    { 9, 144 },
    { 6, 272 },
    { 27, 528 },
    { 5, 1040 },
    { 30, 2064 },
    { 12, 4112 },
    { 15, 8208 },
    { 10, 16400 },
    { 3, 32784 },
    { 7, 32 },
    { 6, 33 },
    { 5, 34 },
    { 3, 36 },
    { 15, 40 },
    { 23, 48 },
    { 10, 96 },
    { 30, 160 },
    { 17, 288 },
    { 12, 544 },
    { 18, 1056 },
    { 9, 2080 },
    { 27, 4128 },
    { 24, 8224 },
    { 29, 16416 },
    { 20, 32800 },
    { 13, 64 },
    { 12, 65 },
    { 15, 66 },
    { 9, 68 },
    { 5, 72 },
    { 29, 80 },
    { 10, 96 },
    { 20, 192 },
    { 27, 320 },
    { 6, 576 },
    { 24, 1088 },
    { 3, 2112 },
    { 17, 4160 },
    { 18, 8256 },
    { 23, 16448 },
    { 30, 32832 },
    { 25, 128 },
    { 24, 129 },
    { 27, 130 },
    { 29, 132 },
    { 17, 136 },
    { 9, 144 },
    { 30, 160 },
    { 20, 192 },
    { 15, 384 },
    { 18, 640 },
    { 12, 1152 },
    { 23, 2176 },
    { 5, 4224 },
    { 6, 8320 },
    { 3, 16512 },
    { 10, 32896 },
    { 22, 256 },
    { 23, 257 },
    { 20, 258 },
    { 18, 260 },
    { 30, 264 },
    { 6, 272 },
    { 17, 288 },
    { 27, 320 },
    { 15, 384 },
    { 29, 768 },
    { 3, 1280 },
    { 24, 2304 },
    { 10, 4352 },
    { 9, 8448 },
    { 12, 16640 },
    { 5, 33024 },
    { 11, 512 },
    { 10, 513 },
    { 9, 514 },
    { 15, 516 },
    { 3, 520 },
    { 27, 528 },
    { 12, 544 },
    { 6, 576 },
    { 18, 640 },
    { 29, 768 },
    { 30, 1536 },
    { 5, 2560 },
    { 23, 4608 },
    { 20, 8704 },
    { 17, 16896 },
    { 24, 33280 },
    { 21, 1024 },
    { 20, 1025 },
    { 23, 1026 },
    { 17, 1028 },
    { 29, 1032 },
    { 5, 1040 },
    { 18, 1056 },
    { 24, 1088 },
    { 12, 1152 },
    { 3, 1280 },
    { 30, 1536 },
    { 27, 3072 },
    { 9, 5120 },
    { 10, 9216 },
    { 15, 17408 },
    { 6, 33792 },
    { 14, 2048 },
    { 15, 2049 },
    { 12, 2050 },
    { 10, 2052 },
    { 6, 2056 },
    { 30, 2064 },
    { 9, 2080 },
    { 3, 2112 },
    { 23, 2176 },
    { 24, 2304 },
    { 5, 2560 },
    { 27, 3072 },
    { 18, 6144 },
    { 17, 10240 },
    { 20, 18432 },
    { 29, 34816 },
    { 28, 4096 },
    { 29, 4097 },
    { 30, 4098 },
    { 24, 4100 },
    { 20, 4104 },
    { 12, 4112 },
    { 27, 4128 },
    { 17, 4160 },
    { 5, 4224 },
    { 10, 4352 },
    { 23, 4608 },
    { 9, 5120 },
    { 18, 6144 },
    { 3, 12288 },
    { 6, 20480 },
    { 15, 36864 },
    { 31, 8192 },
    { 30, 8193 },
    { 29, 8194 },
    { 27, 8196 },
    { 23, 8200 },
    { 15, 8208 },
    { 24, 8224 },
    { 18, 8256 },
    { 6, 8320 },
    { 9, 8448 },
    { 20, 8704 },
    { 10, 9216 },
    { 17, 10240 },
    { 3, 12288 },
    { 5, 24576 },
    { 12, 40960 },
    { 26, 16384 },
    { 27, 16385 },
    { 24, 16386 },
    { 30, 16388 },
    { 18, 16392 },
    { 10, 16400 },
    { 29, 16416 },
    { 23, 16448 },
    { 3, 16512 },
    { 12, 16640 },
    { 17, 16896 },
    { 15, 17408 },
    { 20, 18432 },
    { 6, 20480 },
    { 5, 24576 },
    { 9, 49152 },
    { 19, 32768 },
    { 18, 32769 },
    { 17, 32770 },
    { 23, 32772 },
    { 27, 32776 },
    { 3, 32784 },
    { 20, 32800 },
    { 30, 32832 },
    { 10, 32896 },
    { 5, 33024 },
    { 24, 33280 },
    { 6, 33792 },
    { 29, 34816 },
    { 15, 36864 },
    { 12, 40960 },
    { 9, 49152 }
};

uint16_t hamming_16_11_parity(uint16_t* data) {
    uint16_t parity = 0;

    uint8_t k;
    for (k = 0; k < 5; k++) {
        uint8_t bit = 0, l;
        for (l = 0; l < 16; l++) {
            if ((hamming_16_11_parity_check_matrix[k] >> l) & 1) {
                bit ^= ((*data >> l) & 1);
            }
        }

        parity = (parity << 1) | (bit & 1);
    }

    return parity;
}

bool hamming_16_11(uint16_t* data) {
    uint16_t parity = hamming_16_11_parity(data);

    if (parity == 0) return true;

    int num_corrections = sizeof(corrections)/sizeof(corrections[0]);
    for (int i = 0; i < num_corrections; i++) {
        if (corrections[i].syndrome == parity) {
            *data = *data ^ corrections[i].error_pattern;
            return true;
        }
    }

    return false;
}