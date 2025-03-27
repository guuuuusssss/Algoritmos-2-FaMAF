#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int length = 0;

    for (int i = 0; s[i] != '\0' && i < FIXSTRING_MAX; i++) {
        length++;
    }

    return length;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    unsigned int length1 = fstring_length(s1);
    unsigned int length2 = fstring_length(s2);
    bool is_eq = true;

    if (length1 != length2) { is_eq = false; } 
    else {
        for (int i = 0; i < FIXSTRING_MAX; i++) {
            if (s1[i] != s2[i]) { 
                is_eq = false;
            }
        }
    }
    
    return is_eq;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    unsigned int length1 = fstring_length(s1);
    unsigned int length2 = fstring_length(s2);
    unsigned int min_length = (length1 < length2) ? length1 : length2;
    bool is_less_eq = true;

    for (int i = 0; i < min_length; i++) {
        if (s1[i] != s2[i]) { 
            is_less_eq = s1[i] <= s2[i];
            i = FIXSTRING_MAX;                // no pasa nada por hacer esto como una especie de break?
        }
    }

    if (is_less_eq && length1 > length2) {
        is_less_eq = false;
    }

    return is_less_eq;
}

