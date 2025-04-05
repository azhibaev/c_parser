#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "integer_constant.h"

int main(int argc, const char *argv[])
{
	chars *s = NULL;
	integer_constant *pint = NULL;

	s = chars_create(1);
	chars_read_pchar(s, "12345", 0, 0);
	chars_print(s, CHARS_FLAG_PRINT_NEWLINE);

	pint = integer_constant_create(1);
	integer_constant_read_chars(pint, s);

	integer_constant_free(pint);
	chars_free(s);

	return 0;
}
