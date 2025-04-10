/*
 * File:  chars_out.mod.h
 * Description: Chars string functions
 * Author: Askar Azhibaev
 * Date: April 2025
 * Copyright (c) 2025  Askar Azhibaev
 * 
 * This file is part of C3 extension.
 */

#ifndef CHARS_OUT_H
#define CHARS_OUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"

#module chars_out

#struct
chars *s;		/* pointer */
size_t pos;		/* read position */
size_t *size;	/* size pointer */

#init (chars *s)
if (s)
{
	p->s = s;
	p->size = &s->size;	/* emulation */
	pos = 0;
	is_init = 1;
}

#free
p->s = NULL;
pos = 0;

#include "mod.h"

/*
Имитация замены chars_in->pos => s->size
*/
FUNCTION_INLINE int FUNC(init_size)(T *p,
		size_t *size)
{
	int is_set = 0;

	if (p)
	{
		if (size)
		{
			p->size = size;
		}
	}

	return is_set;
}

/*
Проверяет chars на чтение
*/
FUNCTION_INLINE int FUNC(is_read)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (p->s &&
				p->s->buf &&
				p->size &&
				p->pos < *p->size &&
				*p->size <= p->s->size)
		{
			is_set++;
		}
	}

	return is_set;
}

/*
Читает из chars
и выводит char
*/
FUNCTION_INLINE unsigned char FUNC(char)(T *p)
{
	unsigned char c = 0;

	if (FUNC(is_read)(p))
	{
		c = s->buf[p->s->rpos];
	}

	return c;
}

/*
Прибавляет позицию на следующий символ
Читает из chars
и выводит char
*/
FUNCTION_INLINE unsigned char FUNC(next_char)(T *p)
{
	unsigned char c = 0;

	if (FUNC(is_read)(p))
	{
		p->pos++;
		c = s->buf[p->s->rpos];
	}

	return c;
}

/*
Прибавляет позицию на следующий символ
*/
FUNCTION_INLINE int FUNC(next)(T *p)
{
	int is_set = 0;

	if (FUNC(is_read)(p))
	{
		p->pos++;
		is_set++;
	}

	return is_set;
}

/*
Copy from (p->s->buf + p->pos) of length s_size
returns a pointer,
size of s must be 1 byte larger than s_size,
CHARS_FLAG_ALLOC - allocate memory, call free() after use,
CHARS_FLAG_POINTER - returns a pointer to (p->s->buf + p->pos),
CHARS_FLAG_NOT_NULL_TERMINATED - does not add NULL at the end of a string
CHARS_FLAG_ADVANCE_READ_POS - shift read position by size
CHARS_FLAG_RESET - reads from the beginning
*/
FUNCTION_INLINE char* FUNC(pchar)(T *p,
		char *s,
		size_t s_size,
		unsigned int flags)
{
	size_t size = 0;
	char *buf = NULL;

	if (FUNC(is_read)(p))
	{
		/* Check size */
		size = *p->size - p->pos;
		if (!size ||
				size < s_size)
		{
			s_size = size;
		}

		if (CHARS_FLAG_RESET & flags)
		{
			p->pos = 0;
		}
		if (CHARS_FLAG_POINTER & flags)
		{
			buf = p->s->buf + p->pos;
		}
		else if (CHARS_FLAG_ALLOC & flags)
		{
			if (CHARS_FLAG_NOT_NULL_TERMINATED & flags)
			{
				buf = malloc((s_size) * sizeof(char));
				if (buf)
				{
					memcpy(buf, p->s->buf + p->pos, s_size);
				}
			}
			else
			{
				buf = malloc((s_size + 2) * sizeof(char));
				if (buf)
				{
					memcpy(buf, p->s->buf + p->pos, s_size);
					buf[s_size] = 0;
				}
			}
		}
		else
		{
			memcpy(s, p->s->buf + p->pos, s_size);
			if (!(CHARS_FLAG_NOT_NULL_TERMINATED & flags))
			{
				s[s_size] = 0;
			}
			buf = s;
		}

		p->pos += s_size;
	}

	return buf;
}

#include "mod_undef.h"

#endif	/* CHARS_OUT_H */

