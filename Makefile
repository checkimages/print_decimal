CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wextra

TARGET := print_decimal.o
SRC := $(TARGET:%.o=%.c)

all: $(TARGET)

clean: 
	$(RM) $(TARGET) *.out

example: $(TARGET)
	gcc example.c $(TARGET)
	./a.out

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

format_clang:
	@find . \( -iname '*.c' -o -iname '*.h' \) -exec clang-format -i --style=Google {} \;