#include "utils.hpp"

long le_cast_long(char* buffer, int position) {

    union {
        char arr[8];
        long l;
    } u;

    u.arr[0] = buffer[position];
    u.arr[1] = buffer[position+1];
    u.arr[2] = buffer[position+2];
    u.arr[3] = buffer[position+3];
    u.arr[4] = buffer[position+4];
    u.arr[5] = buffer[position+5];
    u.arr[6] = buffer[position+6];
    u.arr[7] = buffer[position+7];

    return u.l;
}

long be_cast_long(char* buffer, int position) {

    union {
        char arr[8];
        long l;
    } u;

    u.arr[0] = buffer[position+7];
    u.arr[1] = buffer[position+6];
    u.arr[2] = buffer[position+5];
    u.arr[3] = buffer[position+4];
    u.arr[4] = buffer[position+3];
    u.arr[5] = buffer[position+2];
    u.arr[6] = buffer[position+1];
    u.arr[7] = buffer[position];

    return u.l;
}

int le_cast_int(char* buffer, int position) {

    union {
        char arr[4];
        int i;
    } u;

    u.arr[0] = buffer[position];
    u.arr[1] = buffer[position+1];
    u.arr[2] = buffer[position+2];
    u.arr[3] = buffer[position+3];

    return u.i;

}

int be_cast_int(char* buffer, int position) {

    union {
        char arr[4];
        int i;
    } u;

    u.arr[0] = buffer[position+3];
    u.arr[1] = buffer[position+2];
    u.arr[2] = buffer[position+1];
    u.arr[3] = buffer[position];

    return u.i;

}

short le_cast_short(char* buffer, int position) {

    union {
        char arr[2];
        short s;
    } u;

    u.arr[0] = buffer[position];
    u.arr[1] = buffer[position+1];

    return u.s;

}

short be_cast_short(char* buffer, int position) {

    union {
        char arr[2];
        short s;
    } u;

    u.arr[0] = buffer[position+1];
    u.arr[1] = buffer[position];

    return u.s;

}

float le_cast_float(char* buffer, int position) {
    
    union {
        char arr[4];
        float f;
    } u;

    u.arr[0] = buffer[position];
    u.arr[1] = buffer[position+1];
    u.arr[2] = buffer[position+2];
    u.arr[3] = buffer[position+3];

    return u.f;
}

float be_cast_float(char* buffer, int position) {
    
    union {
        char arr[4];
        float f;
    } u;

    u.arr[0] = buffer[position+3];
    u.arr[1] = buffer[position+2];
    u.arr[2] = buffer[position+1];
    u.arr[3] = buffer[position];

    return u.f;
}
