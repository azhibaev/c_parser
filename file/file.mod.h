/*
 * File:  file.mod.h
 * Description: File functions
 * Author: Askar Azhibaev
 * Date: February 2021
 * Copyright (c) 2021-2023  Askar Azhibaev
 * 
 * This file is part of C3 extension.
 * URL: https://azhibaev.com/c3.zip
 * License: CPOL http://www.codeproject.com/info/cpol10.aspx
 */

#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "chars.h"

#module file

#struct
FILE *f;
create chars *s;
create chars *file_name;
size_t read_bytes;
size_t write_bytes;
read;
write;

#define FILE_FLAG_READ (1 << 1)
#define FILE_FLAG_WRITE (1 << 2)
#define FILE_FLAG_READ_LINE (1 << 3)
#define FILE_FLAG_WRITE_LINE (1 << 4)
#define FILE_FLAG_SKIP_NEWLINE (1 << 5)
#define FILE_MODE_BINARY "b"

#init (const char *file_name, unsigned int flags)
if (file_name)
{
	chars_read_pchar(p->file_name, file_name, strlen(file_name), CHARS_FLAG_RESET);
	if (FILE_FLAG_READ & flags)
	{
		p->f = fopen(file_name, "r" FILE_MODE_BINARY);
		if (p->f)
		{
			p->is_read = 1;
			is_init = 1;
			chars_init(p->s, 32);
			//chars_init(p->s, 4 KB);
		}
	}
	else if (FILE_FLAG_WRITE & flags)
	{
		p->f = fopen(file_name, "w" FILE_MODE_BINARY);
		if (p->f)
		{
			p->is_write = 1;
			is_init = 1;
			chars_init(p->s, 4 KB);
		}
	}
}

#free
if (p->f)
{
	fclose(p->f);
	p->f = 0;
}

#include "mod.h"

FUNCTION_INLINE int FUNC(read)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (p->is_read)
		{
			if (p->s->is_init &&
					p->s->is_alloc)
			{
				if (p->s->wpos < p->s->size)
				{
					p->read_bytes = fread(p->s->buf + p->s->wpos, 1, p->s->size - p->s->wpos, p->f);
					if (p->read_bytes)
					{
						p->s->wpos += p->read_bytes;
						is_set++;
					}
				}
				else if (p->s->rpos < p->s->wpos)
				{
					is_set++;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(write_chars)(T *p,
		chars *s,
		unsigned int flags)
{
	int is_set = 0;
	size_t pos1 = 0;
	size_t pos2 = 0;
	size_t size = 0;

	if (p)
	{
		if (s)
		{
			if (FILE_FLAG_WRITE_LINE & flags)
			{
				while (!is_set)
				{
					pos1 = chars_get_mark(p->s);
					if (chars_find_crlf(p->s))
					{
						pos2 = chars_get_mark(p->s);
						size = pos2 - pos1;
						chars_set_mark(p->s, pos1);
						if (size)
						{
							if (chars_copy(s, p->s, size, CHARS_FLAG_ADVANCE_READ_POS))
							{
								is_set++;
								break;
							}
						}
					}
					else
					{
						chars_set_mark(p->s, pos1);
						size = p->s->wpos - p->s->rpos;
						if (size)
						{
							chars_copy(s, p->s, size, CHARS_FLAG_ADVANCE_READ_POS);
						}
						chars_compact(p->s);
						if (!FUNC(read)(p))
						{
							if (!size)
							{
								break;
							}
						}
					}
				}
			}
			else
			{
				if (chars_check(p->s))
				{
					if (chars_read_pchar(s, p->s->buf + p->s->rpos, p->s->wpos - p->s->rpos, 0))
					{
						chars_reset(p->s);
						is_set++;
					}
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(read_chars)(T *p,
		chars *s,
		size_t s_size,
		unsigned int flags)
{
	int is_set = 0;
	size_t pos1 = 0;
	size_t pos2 = 0;
	size_t size = 0;

	if (p)
	{
		if (s)
		{
			if (FILE_FLAG_READ_LINE & flags)
			{
				pos1 = chars_get_mark(s);
				if (chars_find_crlf(s))
				{
					pos2 = chars_get_mark(s);
					size = pos2 - pos1;
					chars_set_mark(s, pos1);
					if (size)
					{
						p->write_bytes = fwrite(s->buf + s->rpos, sizeof(char), size, p->f);
						if (p->write_bytes)
						{
							s->rpos += p->write_bytes;
							is_set++;
						}
					}
				}
				else
				{
					chars_set_mark(s, pos1);
					size = s->wpos - s->rpos;
					if (size)
					{
						p->write_bytes = fwrite(s->buf + s->rpos, sizeof(char), size, p->f);
						if (p->write_bytes)
						{
							s->rpos += p->write_bytes;
							is_set++;
						}
					}
				}
			}
			else
			{
				if (chars_check(s))
				{
					p->write_bytes = fwrite(s->buf + s->rpos, sizeof(char), s->wpos - s->rpos, p->f);
					if (p->write_bytes)
					{
						s->rpos += p->write_bytes;
						is_set++;
					}
				}
			}
		}
	}

	return is_set;
}

#include "mod_undef.h"

#endif	/* FILE_H */
