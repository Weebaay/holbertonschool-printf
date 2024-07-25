#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stddef.h>

int _printf(const char *format, ...);
int _putchar(char c);
void print_number(int n);
void print_unsigned_number(unsigned int n);
int handle_format(const char *format, va_list args);
int handle_specifier(char specifier, va_list args);

#endif
