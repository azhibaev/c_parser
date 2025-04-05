/*
 * File:  chars_char.h
 * Description: Chars string functions
 * Author: Askar Azhibaev
 * Date: June 2023
 * Copyright (c) 2023  Askar Azhibaev
 * 
 * This file is part of C3 extension.
 * URL: https://azhibaev.com/c3.zip
 * License: CPOL http://www.codeproject.com/info/cpol10.aspx
 */

/*
Reads the letter in the reading position
*/
FUNCTION_INLINE unsigned char FUNC(char_read)(T *s)
{
	unsigned char c = 0;

	if (FUNC(check_read)(s))
	{
		c = s->buf[s->rpos];
	}

	return c;
}

/*
Reads the next letter in the reading position
*/
FUNCTION_INLINE unsigned char FUNC(char_read_next)(T *s)
{
	unsigned char c = 0;

	if (FUNC(check_read)(s))
	{
		if (s->rpos < s->wpos)
		{
			s->rpos++;
			c = s->buf[s->rpos];
		}
	}

	return c;
}

/*
Moves to the next reading position
*/
FUNCTION_INLINE int FUNC(read_next)(T *s)
{
	int is_set = 0;

	if (FUNC(check_read)(s))
	{
		if (s->rpos < s->wpos)
		{
			s->rpos++;
			is_set = 1;
		}
	}

	return is_set;
}

/*
Reads the letter at position get
Note: Why do we need the get position?
To be able to read in both directions.
*/
FUNCTION_INLINE unsigned char FUNC(char_get)(T *s)
{
	unsigned char c = 0;

	if (FUNC(check_read)(s))
	{
		if (s->rpos > s->gpos)
		{
			s->gpos = s->rpos;
		}
		if (s->rpos < s->wpos &&
				s->rpos <= s->gpos &&
				s->gpos < s->wpos)
		{
			c = s->buf[s->gpos];
		}
	}

	return c;
}

/*
Reads the next letter at position get
*/
FUNCTION_INLINE unsigned char FUNC(char_get_next)(T *s)
{
	unsigned char c = 0;

	if (FUNC(check_read)(s))
	{
		if (s->rpos < s->wpos)
		{
			if (s->rpos <= s->gpos &&
					s->gpos < s->wpos)
			{
				s->gpos++;
				c = s->buf[s->gpos];
			}
		}
	}

	return c;
}

/*
Moves to the next position get
*/
FUNCTION_INLINE int FUNC(get_next)(T *s)
{
	int is_set = 0;

	if (FUNC(check_read)(s))
	{
		if (s->rpos < s->wpos)
		{
			if (s->rpos <= s->gpos &&
					s->gpos < s->wpos)
			{
				s->gpos++;
				is_set = 1;
			}
		}
	}

	return is_set;
}

/*
Reads the first letter in the reading position
*/
FUNCTION_INLINE unsigned char FUNC(char_get_first)(T *s)
{
	unsigned char c = 0;

	if (FUNC(check_read)(s))
	{
		s->gpos = s->rpos;
		c = s->buf[s->gpos];
	}

	return c;
}

/*
Reads the last letter in the reading area
*/
FUNCTION_INLINE unsigned char FUNC(char_get_last)(T *s)
{
	unsigned char c = 0;

	if (FUNC(check_read)(s))
	{
		s->gpos = s->wpos - 1;
		c = s->buf[s->gpos];
	}

	return c;
}

/*
Reads the previous letter at position get
*/
FUNCTION_INLINE unsigned char FUNC(char_get_prev)(T *s)
{
	unsigned char c = 0;

	if (FUNC(check_read)(s))
	{
		if (s->rpos < s->wpos &&
				s->rpos < s->gpos &&
				s->gpos < s->wpos)
		{
			s->gpos--;
			c = s->buf[s->gpos];
		}
	}

	return c;
}

/*
Moves to the previous position get
*/
FUNCTION_INLINE int FUNC(get_prev)(T *s)
{
	int is_set = 0;

	if (FUNC(check_read)(s))
	{
		if (s->rpos < s->wpos &&
				s->rpos < s->gpos &&
				s->gpos < s->wpos)
		{
			s->gpos--;
			is_set = 1;
		}
	}

	return is_set;
}

/*
Sets the get position to the read position
*/
FUNCTION_INLINE int FUNC(set_get_pos)(T *s)
{
	int is_set = 0;

	if (FUNC(check_read)(s))
	{
		s->gpos = s->rpos;
		is_set++;
	}

	return is_set;
}

/*
Sets the get position to zero
*/
FUNCTION_INLINE int FUNC(reset_get_pos)(T *s)
{
	int is_set = 0;

	if (FUNC(check_read)(s))
	{
		s->gpos = 0;
		is_set++;
	}

	return is_set;
}

/*
Sets the read position to position get
The line is read up to this position
*/
FUNCTION_INLINE int FUNC(flush_read_pos)(T *s)
{
	int is_set = 0;

	if (FUNC(check_read)(s))
	{
		if (s->rpos < s->wpos &&
				s->rpos < s->gpos &&
				s->gpos < s->wpos)
		{
			s->rpos = s->gpos;
			is_set++;
		}
	}

	return is_set;
}

/*
Returns the size to read up to position get
*/
FUNCTION_INLINE unsigned int FUNC(get_size)(T *s)
{
	unsigned int size = 0;

	if (FUNC(check_read)(s))
	{
		if (s->rpos < s->wpos &&
				s->rpos < s->gpos &&
				s->gpos < s->wpos)
		{
			size = s->gpos - s->rpos;
		}
	}

	return size;
}

