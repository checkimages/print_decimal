#include "print_decimal.h"

int main() {
  printf("Присвоим значения переменным:\n");
  printf(
      "s21_decimal value_1 = "
      "s21_from_string(\"-79228162514264337593543950335\");\n");
  printf(
      "s21_decimal value_2 = "
      "s21_from_string(\"0.0000000000000000000000000001\");\n\n");

  s21_decimal value_1 = s21_from_string("-79228162514264337593543950335");
  s21_decimal value_2 = s21_from_string("0.0000000000000000000000000001");

  printf("Выполним умножение: s21_mul(value_1, value_2, &result);\n\n");
  s21_decimal result = value_1;
  result.bits[3] = (28 << 16) & 0x00FF0000;
  result.bits[3] |= (1 << 31) & 0x80000000;
  printf("Выведем результат в десятичной форме:\n\n");
  print_decimal(result);
  printf("\n");

  printf("Выведем результат в двоичной форме:\n\n");
  print_bits(&result);

  printf(
      "Выведем результат в десятичной форме в разрезе интов нашей "
      "структуры:\n");
  print_uints(&result);
  printf("\n");

  printf("То же, в шестнадцатиричной форме:\n");
  print_hex(&result);
  printf("\n");

  printf("Выведем результат в десятичной форме в строку и напечатаем ее:\n\n");
  char* str = s21_to_string(result);
  if (str) {
    puts(str);
    printf("\n");
    free(str);  // Освобождаем память
  } else {
    printf("Ошибка преобразования числа в строку.\n");
  }

  printf("Присвоим значение переменной при инициализации структуры:\n");
  printf(
      "s21_decimal value_3 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, "
      "0x80000000}};\n\n");
  s21_decimal value_3 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  printf("Выведем результат в десятичной форме:\n\n");
  print_decimal(value_3);
  printf("\n");

  printf("Выведем результат в двоичной форме:\n\n");
  print_bits(&value_3);

  return 0;
}
