#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

void print_bits(const void* value);
void print_hex(const void* value);
void print_uints(const void* value);

typedef struct {
  unsigned sign;
  unsigned scale;
  unsigned __int128 mantissa;
} d_128;

d_128 import_from_s21_decimal(s21_decimal s21_num);
s21_decimal export_to_s21_decimal(d_128 num);
d_128 d_128_from_string(const char* str);
s21_decimal s21_from_string(const char* str);
char* d_128_to_string(d_128 num);
char* s21_to_string(s21_decimal s21_num);
void print_decimal(s21_decimal s21_num);
