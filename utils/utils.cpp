#include "utils.hpp"

long le_cast_long(char* buffer, int offset) {

    union {
        char arr[8];
        long l;
    } u;

    u.arr[0] = buffer[offset];
    u.arr[1] = buffer[offset+1];
    u.arr[2] = buffer[offset+2];
    u.arr[3] = buffer[offset+3];
    u.arr[4] = buffer[offset+4];
    u.arr[5] = buffer[offset+5];
    u.arr[6] = buffer[offset+6];
    u.arr[7] = buffer[offset+7];

    return u.l;
}

long be_cast_long(char* buffer, int offset) {

    union {
        char arr[8];
        long l;
    } u;

    u.arr[0] = buffer[offset+7];
    u.arr[1] = buffer[offset+6];
    u.arr[2] = buffer[offset+5];
    u.arr[3] = buffer[offset+4];
    u.arr[4] = buffer[offset+3];
    u.arr[5] = buffer[offset+2];
    u.arr[6] = buffer[offset+1];
    u.arr[7] = buffer[offset];

    return u.l;
}

int le_cast_int(char* buffer, int offset) {

    union {
        char arr[4];
        int i;
    } u;

    u.arr[0] = buffer[offset];
    u.arr[1] = buffer[offset+1];
    u.arr[2] = buffer[offset+2];
    u.arr[3] = buffer[offset+3];

    return u.i;

}

int be_cast_int(char* buffer, int offset) {

    union {
        char arr[4];
        int i;
    } u;

    u.arr[0] = buffer[offset+3];
    u.arr[1] = buffer[offset+2];
    u.arr[2] = buffer[offset+1];
    u.arr[3] = buffer[offset];

    return u.i;

}

short le_cast_short(char* buffer, int offset) {

    union {
        char arr[2];
        short s;
    } u;

    u.arr[0] = buffer[offset];
    u.arr[1] = buffer[offset+1];

    return u.s;

}

short be_cast_short(char* buffer, int offset) {

    union {
        char arr[2];
        short s;
    } u;

    u.arr[0] = buffer[offset+1];
    u.arr[1] = buffer[offset];

    return u.s;

}

float le_cast_float(char* buffer, int offset) {
    
    union {
        char arr[4];
        float f;
    } u;

    u.arr[0] = buffer[offset];
    u.arr[1] = buffer[offset+1];
    u.arr[2] = buffer[offset+2];
    u.arr[3] = buffer[offset+3];

    return u.f;
}

float be_cast_float(char* buffer, int offset) {
    
    union {
        char arr[4];
        float f;
    } u;

    u.arr[0] = buffer[offset+3];
    u.arr[1] = buffer[offset+2];
    u.arr[2] = buffer[offset+1];
    u.arr[3] = buffer[offset];

    return u.f;
}
