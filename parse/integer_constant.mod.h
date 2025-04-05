#ifndef INTEGER_CONSTANT_H
#define INTEGER_CONSTANT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "parse.h"

#module integer_constant

#struct
chars *v;
dec;
octal;
hex;
long;
unsigned;

#init ()

#include "mod.h"

FUNCTION_INLINE int FUNC(read_chars)(T *p,
		chars *s)
{
	int is_set = 0;
	int is_dec = 0;
	int is_octal = 0;
	int is_hex = 0;
	int is_long = 0;
	int is_unsigned = 0;
	unsigned char c = 0;
	size_t pos = 0;

	if (p)
	{
		if (chars_check(s))
		{
			pos = chars_get_mark(s);
			c = chars_char_get(s);
			if (DIGIT)
			{
				is_dec++;
				if (chars_get_next(s))
				{
					if (DIGIT_0)
					{
						c = chars_char_get(s);
						if (ALPHA_X)
						{
							/* hex */
							c = chars_char_get_next(s);
							while (DIGIT || ALPHA_HEX)
							{
								is_hex++;
								c = chars_char_get_next(s);
							}
						}
						else
						{
							/* octal */
							while (DIGIT_OCTAL)
							{
								is_octal++;
								c = chars_char_get_next(s);
							}
						}
					}
					else
					{
						/* dec */
						c = chars_char_get(s);
						while (DIGIT)
						{
							is_dec++;
							c = chars_char_get_next(s);
						}
					}
					/* suffix */
					if (ALPHA_L || ALPHA_U)
					{
						if (ALPHA_L)
						{
							is_long++;
						}
						else if (ALPHA_U)
						{
							is_unsigned++;
						}
						if (chars_get_next(s))
						{
						}
					}
				}
			}
			if (is_dec == 1)
			{
				if (is_octal > 0)
				{
					p->is_octal = 1;
					is_set++;
				}
				else if (is_hex > 0)
				{
					p->is_hex = 1;
					is_set++;
				}
				else
				{
					p->is_dec = 1;
					is_set++;
				}
			}
			else if (is_dec > 0)
			{
				p->is_dec = 1;
				is_set++;
			}
			if (is_set)
			{
				if (is_long > 0)
				{
					p->is_long = 1;
				}
				if (is_unsigned == 1)
				{
					p->is_unsigned = 1;
				}
			}
			if (!is_set)
			{
				chars_set_mark(s, pos);
			}
		}
	}

	return is_set;
}

#include "mod_undef.h"

#endif	/* INTEGER_CONSTANT_H */
