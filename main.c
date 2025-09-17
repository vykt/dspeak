//standard library
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>


#define ASCII_CAP_MIN 0x41
#define ASCII_CAP_MAX 0x5A
#define ASCII_LOW_MIN 0x61
#define ASCII_LOW_MAX 0x7A
#define ASCII_CAP_LOW_GAP 0x20


static inline __attribute__((always_inline)) bool _is_cap(const char c) {
    return (c >= ASCII_CAP_MIN && c <= ASCII_CAP_MAX) ? true : false;
}


static inline __attribute__((always_inline)) bool _is_low(const char c) {
    return (c >= ASCII_LOW_MIN && c <= ASCII_LOW_MAX) ? true : false;
}


static bool _is_good(const char c) {
    return _is_cap(c) || _is_low(c);
}


static inline __attribute__((always_inline))
    bool _is_enc_cap(const char * inp, const int idx) {

    return (inp[idx / CHAR_BIT]
            & (0b10000000 >> (idx % CHAR_BIT))) > 0 ? true : false;
}


static inline __attribute__((always_inline))
    char _enc_char(const char c, const bool is_enc_cap) {

    if (_is_cap(c) && !is_enc_cap) return c + ASCII_CAP_LOW_GAP;
    if (_is_low(c) && is_enc_cap) return c - ASCII_CAP_LOW_GAP;
    return c;
}


int main(int argc, char ** argv) {

    int ret;

    char c;
    bool in_cap, in_low;
    size_t inp_sz, good_enc_sz, full_enc_sz;


    //exit on improper use
    if (argc != 3) {
        fprintf(stderr, "use: dspeak <input string> <carrier string>\n");
        return -1;
    }

    //count alphabet characters in the encoding string
    full_enc_sz = strlen(argv[2]);
    good_enc_sz = 0;
    for (int i = 0; i < full_enc_sz; ++i) {
        if (_is_good(argv[2][i])) ++good_enc_sz;
    }

    //if good length doesn't match, exit
    inp_sz = strlen(argv[1]);
    if ((good_enc_sz / CHAR_BIT) < inp_sz) {
        fprintf(stderr, "error: Supplied carrier string is needs %ld more "
                        "alphabetic character(s).\n",
                (inp_sz * CHAR_BIT) - good_enc_sz);
        return -1;
    }

    //deliver the benevolent message
    int good_enc_idx = 0;
    int inp_idx      = 0;
    for (int full_enc_idx = 0; full_enc_idx < full_enc_sz; ++full_enc_idx) {
        c = argv[2][full_enc_idx];

        //if reached the end of the input string, skip encoding
        if (inp_idx >= (inp_sz * CHAR_BIT)) goto _display_char;

        //simply print non-encoding characters
        if (!_is_good(c)) goto _display_char;

        //convert encoding character
        c = _enc_char(c, _is_enc_cap(argv[1], inp_idx));
        ++good_enc_idx;
        ++inp_idx;

        _display_char:
        putchar(c);
    }

    putchar('\n');
    return 0;
}
