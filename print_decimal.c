#include "print_decimal.h"

void print_bits(const void *value) {
  unsigned char *ptr = (unsigned char *)value;
  int count = 0;
  for (int i = 16 - 1; i >= 0; i--) {
    for (int j = 7; j >= 0; j--) {
      unsigned char bit = (ptr[i] >> j) & 1;
      printf("%hhu", bit);
    }
    printf(" ");
    count++;
    if (count == 4) {
      count = 0;
      printf("\n");
    }
  }
  //	if(count)
  printf("\n");
}

void print_hex(const void *value) {
  unsigned *ptr = (unsigned *)value;
  printf("{{ %#x, ", ptr[0]);
  printf("%#x, ", ptr[1]);
  printf("%#x, ", ptr[2]);
  printf("%#x }};\n", ptr[3]);
}

void print_uints(const void *value) {
  unsigned *ptr = (unsigned *)value;
  printf("{{ %u, ", ptr[0]);
  printf("%u, ", ptr[1]);
  printf("%u, ", ptr[2]);
  printf("%u }};\n", ptr[3]);
}

d_128 import_from_s21_decimal(s21_decimal s21_num) {
  d_128 result = {0};

  result.mantissa = (unsigned __int128)s21_num.bits[0];
  result.mantissa |= (unsigned __int128)s21_num.bits[1] << 32;
  result.mantissa |= (unsigned __int128)s21_num.bits[2] << 64;

  result.sign = (s21_num.bits[3] >> 31) & 1;
  result.scale = (s21_num.bits[3] >> 16) & 0xFF;

  return result;
}

s21_decimal export_to_s21_decimal(d_128 num) {
  s21_decimal result = {0};

  result.bits[0] = (unsigned)(num.mantissa & 0xFFFFFFFF);
  result.bits[1] = (unsigned)((num.mantissa >> 32) & 0xFFFFFFFF);
  result.bits[2] = (unsigned)((num.mantissa >> 64) & 0xFFFFFFFF);

  result.bits[3] = (num.scale & 0xFF) << 16;
  result.bits[3] |= num.sign << 31;

  return result;
}

d_128 d_128_from_string(const char *str) {
  d_128 result = {0};
  int point_seen = 0;

  if (*str == '-') {
    result.sign = 1;
    str++;
  }

  while (*str) {
    if (*str == '.') {
      point_seen = 1;
    } else {
      result.mantissa = result.mantissa * 10 + (*str - '0');
      if (point_seen) {
        result.scale++;
      }
    }
    str++;
  }

  return result;
}

s21_decimal s21_from_string(const char *str) {
  d_128 num = d_128_from_string(str);
  return export_to_s21_decimal(num);
}

char *d_128_to_string(d_128 num) {
  char buffer[50];
  int dot_required = num.scale > 0;
  int i = 0;

  do {
    if (dot_required && !num.scale) {
      buffer[i++] = '.';
      dot_required = 0;
    } else {
      buffer[i++] = (num.mantissa % 10) + '0';
      num.mantissa /= 10;
      if (num.scale) num.scale--;
    }

  } while (num.mantissa > 0);

  if (num.sign) {
    buffer[i++] = '-';
  }

  buffer[i] = '\0';

  char *result = (char *)calloc(i + 1, sizeof(char));
  if (!result) {
    return NULL;
  }

  for (int j = 0; j < i; j++) {
    result[j] = buffer[i - j - 1];
  }
  result[i] = '\0';

  return result;
}

char *s21_to_string(s21_decimal s21_num) {
  d_128 num = import_from_s21_decimal(s21_num);
  return d_128_to_string(num);
}

void print_decimal(s21_decimal s21_num) {
  char *str = s21_to_string(s21_num);
  if (str) {
    puts(str);
    printf("\n");
    free(str);  // Освобождаем память
  } else {
    printf("Ошибка преобразования числа в строку.\n");
  }
}