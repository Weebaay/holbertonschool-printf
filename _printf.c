#include <unistd.h>
#include <stdarg.h>
#include "main.h"
/**
 * print_number - Helper function to print an integer
 * @n: The integer to print
 */
void print_number(int n)
{
	unsigned int num = n;

	if (n < 0)
	{
		_putchar('-');
		num = -num;
	}

	if (num / 10)
		print_number(num / 10);

	_putchar((num % 10) + '0');
}

/**
 * print_unsigned_number - Helper function to print an unsigned integer
 * @n: The unsigned integer to print
 */
void print_unsigned_number(unsigned int n)
{
	if (n / 10)
		print_unsigned_number(n / 10);

	_putchar((n % 10) + '0');
}

/**
 * handle_specifier - Handles a format specifier
 * @specifier: The format specifier
 * @args: The va_list of arguments
 * 
 * Return: The number of characters printed
 */
int handle_specifier(char specifier, va_list args)
{
	char *str;
	unsigned int u;
	void *ptr;
	unsigned long addr;
	char buffer[20];
	int j, count = 0;
	char c, offset;

	if (specifier == 'c')
	{
		c = va_arg(args, int);
		count += _putchar(c);
	}
	else if (specifier == 's')
	{
		str = va_arg(args, char *);
		if (!str)
			str = "(null)";
		while (*str)
			count += _putchar(*str++);
	}
	else if (specifier == '%')
		count += _putchar('%');
	else if (specifier == 'd' || specifier == 'i')
	{
		print_number(va_arg(args, int));
		count++;
	}
	else if (specifier == 'u')
	{
		print_unsigned_number(va_arg(args, unsigned int));
		count++;
	}
	else if (specifier == 'o')
	{
		u = va_arg(args, unsigned int);
		j = 0;
		do {
			buffer[j++] = (u % 8) + '0';
			u /= 8;
		} while (u != 0);
		while (--j >= 0)
			count += _putchar(buffer[j]);
	}
	else if (specifier == 'x' || specifier == 'X')
	{
		u = va_arg(args, unsigned int);
		j = 0;
		offset = (specifier == 'x') ? 'a' - 10 : 'A' - 10;
		do {
			int digit = u % 16;
			buffer[j++] = (digit < 10) ? digit + '0' : digit + offset;
			u /= 16;
		} while (u != 0);
		while (--j >= 0)
			count += _putchar(buffer[j]);
	}
	else if (specifier == 'p')
	{
		ptr = va_arg(args, void *);
		addr = (unsigned long)ptr;
		count += _putchar('0') + _putchar('x');
		j = 0;
		do {
			int digit = addr % 16;
			buffer[j++] = (digit < 10) ? digit + '0' : digit + 'a' - 10;
			addr /= 16;
		} while (addr != 0);
		while (--j >= 0)
			count += _putchar(buffer[j]);
	}
	else
	{
		count += _putchar('%');
		count += _putchar(specifier);
	}
	return (count);
}

/**
 * handle_format - Handles the format string
 * @format: The format string
 * @args: The va_list of arguments
 * 
 * Return: The number of characters printed
 */
int handle_format(const char *format, va_list args)
{
	int i = 0, count = 0;

	while (format && format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '\0')
				return (-1);
			count += handle_specifier(format[i], args);
		}
		else
		{
			count += _putchar(format[i]);
		}
		i++;
	}
	return (count);
}

/**
 * _printf - Produces output according to a format
 * @format: The format string containing the characters and the specifiers
 * 
 * Return: The number of characters printed (excluding the null byte used to
 * end output to strings)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count;

	if (!format)
		return (-1);

	va_start(args, format);
	count = handle_format(format, args);
	va_end(args);

	return (count);
}
