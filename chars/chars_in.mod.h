/*
 * File:  chars_in.mod.h
 * Description: Chars string functions
 * Author: Askar Azhibaev
 * Date: April 2025
 * Copyright (c) 2025  Askar Azhibaev
 * 
 * This file is part of C3 extension.
 */

#ifndef CHARS_IN_H
#define CHARS_IN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"

#module chars_in

#struct
chars *s;		/* pointer */
size_t pos;		/* wpos => s->size */

#init (chars *s)
if (s)
{
	p->s = s;
	pos = 0;
	is_init = 1;
}

#free
p->s = NULL;
pos = 0;

#include "mod.h"

/*
Проверяет возможность записи в chars
*/
FUNCTION_INLINE int FUNC(is_write)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (p->s &&
				p->s->buf &&
				p->pos < p->s->size)
		{
			is_set++;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(char)(T *p,
		char c)
{
	int is_set = 0;

	if (FUNC(is_write)(p))
	{
		p->s->buf[p->pos] = c;
		p->pos++;
		is_set++;
	}

	return is_set;
}

/*
Writes from char *s to (p->s->buf + p->pos)
CHARS_FLAG_NOT_NULL_TERMINATED - does not add NULL at the end of a string
CHARS_FLAG_RESET - writes from the beginning
*/
FUNCTION_INLINE int FUNC(pchar)(T *p,
	const char *s,
	size_t s_size,
	unsigned int flags)
{
	int is_set = 0;
	size_t size = 0;

	if (p)
	{
		if (p->s)
		{
			if (!p->s->is_init)
			{
				chars_init(p->s, s_size ? s_size + 2 : 0);
			}
			if (FUNC(is_write)(p))
			{
				if (s)
				{
					if (CHARS_FLAG_RESET & flags)
					{
					/*
How to call 'reset' in chars_out ?
Call any
chars_in_reset() &&
chars_out_reset()
					*/
						if (!FUNC(reset)(p))
						{
							/* Error */
						}
					}
					/* Check size */
					if (s_size)
					{
						size = s_size;
					}
					else
					{
						size = strlen(s);
					}

					/* Check p->s->size */
					if (p->s->size - p->pos < size + 1 ||
							!p->is_alloc)
					{
						if (!FUNC(realloc)(p, p->wpos + size + 1, CHARS_FLAG_GROWTH_FACTOR))
						{
							/* Error */
						}
					}

					memcpy(p->buf + p->wpos, s, size);
					p->wpos += size;
					if (!(CHARS_FLAG_NOT_NULL_TERMINATED & flags))
					{
						p->buf[p->wpos] = 0;
					}
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

#include "mod_undef.h"

#endif	/* CHARS_IN_H */

