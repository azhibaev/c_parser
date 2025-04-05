/*
 * File:  parse_c.h
 * Description: C language parser created with grammar from Section A13 of The C programming language, 2nd edition, by Brian W. Kernighan and Dennis M. Ritchie,Prentice Hall, 1988.
 * Author: Askar Azhibaev
 * Date: May 2023
 * Copyright (c) 2023  Askar Azhibaev
 * 
 * This file is part of C3 extension.
 * URL: https://azhibaev.com/c3.zip
 * License: CPOL http://www.codeproject.com/info/cpol10.aspx
 */

#ifndef PARSE_C_H
#define PARSE_C_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

FUNCTION_INLINE int FUNC(translation_unit)(chars *s);
FUNCTION_INLINE int FUNC(external_declaration)(chars *s);
FUNCTION_INLINE int FUNC(function_definition)(chars *s);
FUNCTION_INLINE int FUNC(declaration)(chars *s);
FUNCTION_INLINE int FUNC(declaration_list)(chars *s);
FUNCTION_INLINE int FUNC(declaration_specifiers)(chars *s);
FUNCTION_INLINE int FUNC(storage_class_specifier)(chars *s);
FUNCTION_INLINE int FUNC(type_specifier)(chars *s);
FUNCTION_INLINE int FUNC(type_qualifier)(chars *s);
FUNCTION_INLINE int FUNC(struct_or_union_specifier)(chars *s);
FUNCTION_INLINE int FUNC(struct_or_union)(chars *s);
FUNCTION_INLINE int FUNC(struct_declaration_list)(chars *s);
FUNCTION_INLINE int FUNC(init_declarator_list)(chars *s);
FUNCTION_INLINE int FUNC(init_declarator)(chars *s);
FUNCTION_INLINE int FUNC(struct_declaration)(chars *s);
FUNCTION_INLINE int FUNC(specifier_qualifier_list)(chars *s);
FUNCTION_INLINE int FUNC(struct_declarator_list)(chars *s);
FUNCTION_INLINE int FUNC(struct_declarator)(chars *s);
FUNCTION_INLINE int FUNC(enum_specifier)(chars *s);
FUNCTION_INLINE int FUNC(enumerator_list)(chars *s);
FUNCTION_INLINE int FUNC(enumerator)(chars *s);
FUNCTION_INLINE int FUNC(declarator)(chars *s);
FUNCTION_INLINE int FUNC(direct_declarator)(chars *s);
FUNCTION_INLINE int FUNC(pointer)(chars *s);
FUNCTION_INLINE int FUNC(type_qualifier_list)(chars *s);
FUNCTION_INLINE int FUNC(parameter_type_list)(chars *s);
FUNCTION_INLINE int FUNC(parameter_list)(chars *s);
FUNCTION_INLINE int FUNC(parameter_declaration)(chars *s);
FUNCTION_INLINE int FUNC(identifier_list)(chars *s);
FUNCTION_INLINE int FUNC(initializer)(chars *s);
FUNCTION_INLINE int FUNC(initializer_list)(chars *s);
FUNCTION_INLINE int FUNC(type_name)(chars *s);
FUNCTION_INLINE int FUNC(abstract_declarator)(chars *s);
FUNCTION_INLINE int FUNC(direct_abstract_declarator)(chars *s);
FUNCTION_INLINE int FUNC(typedef_name)(chars *s);
FUNCTION_INLINE int FUNC(statement)(chars *s);
FUNCTION_INLINE int FUNC(labeled_statement)(chars *s);
FUNCTION_INLINE int FUNC(expression_statement)(chars *s);
FUNCTION_INLINE int FUNC(compound_statement)(chars *s);
FUNCTION_INLINE int FUNC(statement_list)(chars *s);
FUNCTION_INLINE int FUNC(selection_statement)(chars *s);
FUNCTION_INLINE int FUNC(iteration_statement)(chars *s);
FUNCTION_INLINE int FUNC(jump_statement)(chars *s);
FUNCTION_INLINE int FUNC(expression)(chars *s);
FUNCTION_INLINE int FUNC(assignment_expression)(chars *s);
FUNCTION_INLINE int FUNC(assignment_operator)(chars *s);
FUNCTION_INLINE int FUNC(conditional_expression)(chars *s);
FUNCTION_INLINE int FUNC(constant_expression)(chars *s);
FUNCTION_INLINE int FUNC(logical_or_expression)(chars *s);
FUNCTION_INLINE int FUNC(logical_and_expression)(chars *s);
FUNCTION_INLINE int FUNC(inclusive_or_expression)(chars *s);
FUNCTION_INLINE int FUNC(exclusive_or_expression)(chars *s);
FUNCTION_INLINE int FUNC(and_expression)(chars *s);
FUNCTION_INLINE int FUNC(equality_expression)(chars *s);
FUNCTION_INLINE int FUNC(relational_expression)(chars *s);
FUNCTION_INLINE int FUNC(shift_expression)(chars *s);
FUNCTION_INLINE int FUNC(additive_expression)(chars *s);
FUNCTION_INLINE int FUNC(multiplicative_expression)(chars *s);
FUNCTION_INLINE int FUNC(cast_expression)(chars *s);
FUNCTION_INLINE int FUNC(unary_expression)(chars *s);
FUNCTION_INLINE int FUNC(unary_operator)(chars *s);
FUNCTION_INLINE int FUNC(postfix_expression)(chars *s);
FUNCTION_INLINE int FUNC(primary_expression)(chars *s);
FUNCTION_INLINE int FUNC(constant)(chars *s);
FUNCTION_INLINE int FUNC(assignment_expression_list)(chars *s);
FUNCTION_INLINE int FUNC(constant)(chars *s);
FUNCTION_INLINE int FUNC(enumeration_constant)(chars *s);
FUNCTION_INLINE int FUNC(program)(chars *s);
FUNCTION_INLINE int FUNC(external_definition)(chars *s);
FUNCTION_INLINE int FUNC(function_body)(chars *s);
FUNCTION_INLINE int FUNC(function_statement)(chars *s);
FUNCTION_INLINE int FUNC(data_definition)(chars *s);

FUNCTION_INLINE int FUNC(translation_unit)(chars *s)
{
	int is_set = 1;

	if (chars_check(s))
	{
		while (FUNC(external_declaration)(s))
		{
			is_set++;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(external_declaration)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(function_definition)(s))
		{
			is_set = 1;
		}
		else if (FUNC(declaration)(s))
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(function_definition)(chars *s)
{
	int is_set = 0;
	int is_declarator = 0;
	int is_compound_statement = 0;

	if (chars_check(s))
	{
		if (FUNC(declaration_specifiers))
		{
			is_set++;
		}
		if (FUNC(declarator)(s))
		{
			is_declarator = 1;
		}
		if (FUNC(declaration_list))
		{
			is_set++;
		}
		if (FUNC(compound_statement)(s))
		{
			is_compound_statement = 1;
		}
	}

	if (is_declarator &&
			is_compound_statement)
	{
		is_set++;
	}
	else
	{
		is_set = 0;
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(declaration)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(declaration_specifiers)(s))
		{
			is_set++;
			if (FUNC(init_declarator_list)(s))
			{
				is_set++;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(declaration_list)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		while (FUNC(declaration)(s))
		{
			is_set++;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(declaration_specifiers)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(storage_class_specifier)(s))
		{
			is_set = 1;
			if (FUNC(declaration_specifiers)(s))
			{
			}
		}
		else if (FUNC(type_specifier)(s))
		{
			is_set = 1;
			if (FUNC(declaration_specifiers)(s))
			{
			}
		}
		else if (FUNC(type_qualifier)(s))
		{
			is_set = 1;
			if (FUNC(declaration_specifiers)(s))
			{
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(storage_class_specifier)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(pchar)(s, "auto"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "register"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "static"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "extern"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "typedef"))
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(type_specifier)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(pchar)(s, "void"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "char"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "short"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "int"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "long"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "float"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "double"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "signed"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "unsigned"))
		{
			is_set = 1;
		}
		else if (FUNC(struct_or_union_specifier)(s))
		{
			is_set = 1;
		}
		else if (FUNC(enum_specifier)(s))
		{
			is_set = 1;
		}
		else if (FUNC(typedef_name)(s))
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(type_qualifier)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(pchar)(s, "const"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "volatile"))
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(struct_or_union_specifier)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(struct_or_union)(s))
		{
			if (FUNC(identifier)(s))
			{
			}
			if (FUNC(char)(s, '{'))
			{
				if (FUNC(struct_declaration_list)(s))
				{
					if (FUNC(char)(s, '}'))
					{
						is_set = 1;
						return is_set;
					}
				}
			}
		}
		if (FUNC(struct_or_union)(s))
		{
			if (FUNC(identifier)(s))
			{
				is_set = 1;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(struct_or_union)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(pchar)(s, "struct"))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "union"))
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(struct_declaration_list)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		while (FUNC(struct_declaration)(s))
		{
			is_set++;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(init_declarator_list)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(init_declarator)(s))
		{
			is_set++;
		}
		else if (FUNC(init_declarator_list)(s))
		{
			if (FUNC(char)(s, ','))
			{
				if (FUNC(init_declarator)(s))
				{
					is_set++;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(init_declarator)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(declarator)(s))
		{
			is_set++;
			if (FUNC(char)(s, '='))
			{
				if (FUNC(initializer)(s))
				{
					is_set++;
				}
			}
		}
	}

	return is_set;
}


FUNCTION_INLINE int FUNC(struct_declaration)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(specifier_qualifier_list)(s))
		{
			if (FUNC(struct_declarator_list)(s))
			{
				if (FUNC(char)(s, ';'))
				{
					is_set++;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(specifier_qualifier_list)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(type_specifier)(s))
		{
			is_set = 1;
			if (FUNC(specifier_qualifier_list)(s))
			{
			}
		}
		else if (FUNC(type_qualifier)(s))
		{
			is_set = 1;
			if (FUNC(specifier_qualifier_list)(s))
			{
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(struct_declarator_list)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(struct_declarator)(s))
		{
			is_set = 1;
		}
		else if (FUNC(struct_declarator_list)(s))
		{
			if (FUNC(char)(s, ','))
			{
				if (FUNC(struct_declarator)(s))
				{
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(struct_declarator)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(declarator)(s))
		{
			is_set++;
		}
		if (FUNC(char)(s, ':'))
		{
			if (FUNC(constant_expression)(s))
			{
				is_set++;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(enum_specifier)(chars *s)
{
	int is_set = 0;
	int is_identifier = 0;

	if (chars_check(s))
	{
		if (FUNC(pchar)(s, "enum"))
		{
			if (FUNC(identifier)(s))
			{
				is_identifier = 1;
			}
			if (FUNC(char)(s, '{'))
			{
				if (FUNC(enumerator_list)(s))
				{
					if (FUNC(char)(s, '}'))
					{
						is_set++;
						return is_set;
					}
				}
			}
			if (is_identifier)
			{
				is_set++;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(enumerator_list)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(enumerator)(s))
		{
			is_set++;
		}
		else if (FUNC(enumerator_list)(s))
		{
			if (FUNC(char)(s, ','))
			{
				if (FUNC(enumerator)(s))
				{
					is_set++;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(enumerator)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(identifier)(s))
		{
			is_set++;
			if (FUNC(char)(s, '='))
			{
				if (FUNC(constant_expression)(s))
				{
					is_set++;
				}
			}
		}
	}

	return is_set;
}


FUNCTION_INLINE int FUNC(declarator)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(pointer)(s))
		{
		}
		if (FUNC(direct_declarator)(s))
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(direct_declarator)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(identifier)(s))
		{
			is_set = 1;
		}
		else if (FUNC(char)(s, '('))
		{
			if (FUNC(declarator)(s))
			{
				if (FUNC(char)(s, ')'))
				{
					is_set = 1;
					return is_set;
				}
			}
		}
		if (FUNC(direct_declarator)(s))
		{
			if (FUNC(char)(s, '['))
			{
				if (FUNC(constant_expression)(s))
				{
				}
				if (FUNC(char)(s, ']'))
				{
					is_set = 1;
					return is_set;
				}
			}
			if (FUNC(char)(s, '('))
			{
				if (FUNC(parameter_type_list)(s))
				{
					if (FUNC(char)(s, ')'))
					{
						is_set = 1;
						return is_set;
					}
				}
			}
			if (FUNC(char)(s, '('))
			{
				if (FUNC(identifier_list)(s))
				{
				}
				if (FUNC(char)(s, ')'))
				{
					is_set = 1;
					return is_set;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(pointer)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(char)(s, '*'))
		{
			if (FUNC(type_qualifier_list)(s))
			{
				is_set++;
			}
			if (FUNC(pointer)(s))
			{
				is_set++;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(type_qualifier_list)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		while (FUNC(type_qualifier)(s))
		{
			is_set++;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(parameter_type_list)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(parameter_list)(s))
		{
			is_set++;
		}
		if (FUNC(char)(s, ','))
		{
			if (FUNC(pchar)(s, "..."))
			{
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(parameter_list)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(parameter_declaration)(s))
		{
			is_set++;
		}
		else if (FUNC(parameter_list)(s))
		{
			if (FUNC(char)(s, ','))
			{
				if (FUNC(parameter_declaration)(s))
				{
					is_set++;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(parameter_declaration)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(declaration_specifiers)(s))
		{
			if (FUNC(declaration)(s))
			{
				is_set++;
			}
			else
			{
				if (FUNC(abstract_declarator)(s))
				{
				}
				is_set++;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(identifier_list)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(identifier)(s))
		{
			is_set++;
		}
		else if (FUNC(identifier_list)(s))
		{
			if (FUNC(char)(s, ','))
			{
				if (FUNC(identifier)(s))
				{
					is_set++;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(initializer)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(assignment_expression)(s))
		{
			is_set++;
		}
		else if (FUNC(char)(s, '{'))
		{
			if (FUNC(initializer_list)(s))
			{
				if (FUNC(char)(s, ','))
				{
				}
				if (FUNC(char)(s, '}'))
				{
					is_set++;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(initializer_list)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(initializer)(s))
		{
			is_set++;
		}
		else if (FUNC(initializer_list)(s))
		{
			if (FUNC(char)(s, ','))
			{
				if (FUNC(initializer)(s))
				{
					is_set++;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(type_name)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(specifier_qualifier_list)(s))
		{
			is_set++;
			if (FUNC(abstract_declarator)(s))
			{
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(abstract_declarator)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(pointer)(s))
		{
			is_set++;
		}
		if (FUNC(direct_abstract_declarator)(s))
		{
			is_set++;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(direct_abstract_declarator)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(char)(s, '('))
		{
			if (FUNC(abstract_declarator)(s))
			{
				if (FUNC(char)(s, ')'))
				{
					is_set++;
					return is_set;
				}
			}
		}
		if (FUNC(direct_abstract_declarator)(s))
		{
		}
		if (FUNC(char)(s, '['))
		{
			if (FUNC(constant_expression)(s))
			{
			}
			if (FUNC(char)(s, ']'))
			{
				is_set++;
				return is_set;
			}
		}
		if (FUNC(char)(s, '('))
		{
			if (FUNC(parameter_type_list)(s))
			{
			}
			if (FUNC(char)(s, ')'))
			{
				is_set++;
				return is_set;
			}
		}

	}

	return is_set;
}

FUNCTION_INLINE int FUNC(typedef_name)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(identifier)(s))
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(statement)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(labeled_statement)(s))
		{
			is_set++;
		}
		else if (FUNC(expression_statement)(s))
		{
			is_set++;
		}
		else if (FUNC(compound_statement)(s))
		{
			is_set++;
		}
		else if (FUNC(selection_statement)(s))
		{
			is_set++;
		}
		else if (FUNC(iteration_statement)(s))
		{
			is_set++;
		}
		else if (FUNC(jump_statement)(s))
		{
			is_set++;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(labeled_statement)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(identifier)(s))
		{
			if (FUNC(char)(s, ':'))
			{
				if (FUNC(statement)(s))
				{
					is_set++;
					return is_set;
				}
			}
		}
		if (FUNC(pchar)(s, "case"))
		{
			if (FUNC(constant_expression)(s))
			{
				if (FUNC(char)(s, ':'))
				{
					if (FUNC(statement)(s))
					{
						is_set++;
						return is_set;
					}
				}
			}		
		}		
		if (FUNC(pchar)(s, "default"))
		{
			if (FUNC(char)(s, ':'))
			{
				if (FUNC(statement)(s))
				{
					is_set++;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(expression_statement)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(expression)(s))
		{
		}
		is_set++;
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(compound_statement)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(char)(s, '{'))
		{
			if (FUNC(declaration_list)(s))
			{
				is_set++;
			}
			if (FUNC(statement_list)(s))
			{
				is_set++;
			}
			if (FUNC(char)(s, '}'))
			{
				is_set++;
			}
			else
			{
				is_set = 0;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(statement_list)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		while (FUNC(statement)(s))
		{
			is_set++;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(selection_statement)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(pchar)(s, "if"))
		{
			if (FUNC(char)(s, '('))
			{
				if (FUNC(expression)(s))
				{
					if (FUNC(char)(s, ')'))
					{
						if (FUNC(statement)(s))
						{
							if (FUNC(pchar)(s, "else"))
							{
								if (FUNC(statement)(s))
								{
									is_set++;
									return is_set;
								}
							}
							else
							{
								is_set++;
								return is_set;
							}
						}
					}
				}
			}
		}
		if (FUNC(pchar)(s, "switch"))
		{
			if (FUNC(char)(s, '('))
			{
				if (FUNC(expression)(s))
				{
					if (FUNC(char)(s, ')'))
					{
						if (FUNC(statement)(s))
						{
							is_set++;
							return is_set;
						}
					}
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(iteration_statement)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(pchar)(s, "while"))
		{
			if (FUNC(char)(s, '('))
			{
				if (FUNC(expression)(s))
				{
					if (FUNC(char)(s, ')'))
					{
						if (FUNC(statement)(s))
						{
							is_set++;
							return is_set;
						}
					}
				}
			}
		}
		if (FUNC(pchar)(s, "do"))
		{
			if (FUNC(statement)(s))
			{
				if (FUNC(pchar)(s, "while"))
				{
					if (FUNC(char)(s, '('))
					{
						if (FUNC(expression)(s))
						{
							if (FUNC(char)(s, ')'))
							{
								if (FUNC(char)(s, ';'))
								{
									is_set++;
									return is_set;
								}
							}
						}
					}
				}
			}
		}
		if (FUNC(pchar)(s, "for"))
		{
			if (FUNC(char)(s, '('))
			{
				if (FUNC(expression)(s))
				{
				}
				if (FUNC(char)(s, ';'))
				{
					if (FUNC(expression)(s))
					{
					}
					if (FUNC(char)(s, ';'))
					{
						if (FUNC(expression)(s))
						{
						}
						if (FUNC(char)(s, ')'))
						{
							if (FUNC(statement)(s))
							{
								is_set++;
								return is_set;
							}
						}
					}
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(jump_statement)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(pchar)(s, "goto"))
		{
			if (FUNC(identifier)(s))
			{
				if (FUNC(char)(s, ';'))
				{
					is_set++;
					return is_set;
				}
			}
		}
		if (FUNC(pchar)(s, "continue"))
		{
			if (FUNC(char)(s, ';'))
			{
				is_set++;
				return is_set;
			}
		}
		if (FUNC(pchar)(s, "break"))
		{
			if (FUNC(char)(s, ';'))
			{
				is_set++;
				return is_set;
			}
		}
		if (FUNC(pchar)(s, "return"))
		{
			if (FUNC(expression)(s))
			{
			}
			is_set++;
			return is_set;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(assignment_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(expression)(s))
		{
			if (FUNC(char)(s, ','))
			{
				if (FUNC(assignment_expression)(s))
				{
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(assignment_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(conditional_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(unary_expression)(s))
		{
			if (FUNC(assignment_operator)(s))
			{
				if (FUNC(assignment_expression)(s))
				{
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(assignment_operator)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(char)(s, '='))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "*="))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "/="))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "%="))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "+="))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "-="))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "<<="))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, ">>="))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "&="))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "^="))
		{
			is_set = 1;
		}
		else if (FUNC(pchar)(s, "|="))
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(conditional_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(logical_or_expression)(s))
		{
			is_set++;
		}
		if (FUNC(char)(s, '?'))
		{
			if (FUNC(expression)(s))
			{
				if (FUNC(char)(s, ':'))
				{
					if (FUNC(conditional_expression)(s))
					{
						is_set++;
					}
				}
			}
		}
	}

	return is_set;
}


FUNCTION_INLINE int FUNC(constant_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(conditional_expression)(s))
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(logical_or_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(logical_and_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(logical_or_expression)(s))
		{
			if (FUNC(pchar)(s, "||"))
			{
				if (FUNC(logical_and_expression)(s))
				{
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(logical_and_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(inclusive_or_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(logical_and_expression)(s))
		{
			if (FUNC(pchar)(s, "&&"))
			{
				if (FUNC(inclusive_or_expression)(s))
				{
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(inclusive_or_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(exclusive_or_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(inclusive_or_expression)(s))
		{
			if (FUNC(char)(s, '|'))
			{
				if (FUNC(exclusive_or_expression)(s))
				{
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(exclusive_or_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(and_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(exclusive_or_expression)(s))
		{
			if (FUNC(char)(s, '^'))
			{
				if (FUNC(and_expression)(s))
				{
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(and_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(equality_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(and_expression)(s))
		{
			if (FUNC(char)(s, '&'))
			{
				if (FUNC(equality_expression)(s))
				{
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(equality_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(relational_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(equality_expression)(s))
		{
			if (FUNC(pchar)(s, "=="))
			{
				if (FUNC(relational_expression)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
			if (FUNC(pchar)(s, "!="))
			{
				if (FUNC(relational_expression)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(relational_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(shift_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(relational_expression)(s))
		{
			if (FUNC(char)(s, '<'))
			{
				if (FUNC(shift_expression)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
			if (FUNC(char)(s, '>'))
			{
				if (FUNC(shift_expression)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
			if (FUNC(pchar)(s, "<="))
			{
				if (FUNC(shift_expression)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
			if (FUNC(pchar)(s, ">="))
			{
				if (FUNC(shift_expression)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(shift_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(additive_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(shift_expression)(s))
		{
			if (FUNC(pchar)(s, "<<"))
			{
				if (FUNC(additive_expression)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
			if (FUNC(pchar)(s, ">>"))
			{
				if (FUNC(additive_expression)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(additive_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(multiplicative_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(additive_expression)(s))
		{
			if (FUNC(char)(s, '+'))
			{
				if (FUNC(multiplicative_expression)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
			if (FUNC(char)(s, '-'))
			{
				if (FUNC(multiplicative_expression)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(multiplicative_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(cast_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(multiplicative_expression)(s))
		{
			if (FUNC(char)(s, '*'))
			{
				if (FUNC(cast_expression)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
			if (FUNC(char)(s, '/'))
			{
				if (FUNC(cast_expression)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
			if (FUNC(char)(s, '%'))
			{
				if (FUNC(cast_expression)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
		}

	}

	return is_set;
}

FUNCTION_INLINE int FUNC(cast_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(unary_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(char)(s, '('))
		{
			if (FUNC(type_name)(s))
			{
				if (FUNC(char)(s, ')'))
				{
					if (FUNC(cast_expression)(s))
					{
						is_set = 1;
					}
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(unary_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(postfix_expression)(s))
		{
			is_set = 1;
			return is_set;
		}
		if (FUNC(pchar)(s, "++"))
		{
			if (FUNC(unary_expression)(s))
			{
				is_set = 1;
				return is_set;
			}
		}
		if (FUNC(pchar)(s, "--"))
		{
			if (FUNC(unary_expression)(s))
			{
				is_set = 1;
				return is_set;
			}
		}
		if (FUNC(unary_operator)(s))
		{
			if (FUNC(cast_expression)(s))
			{
				is_set = 1;
				return is_set;
			}
		}
		if (FUNC(pchar)(s, "sizeof"))
		{
			if (FUNC(unary_expression)(s))
			{
				is_set = 1;
				return is_set;
			}
			else if (FUNC(char)(s, '('))
			{
				if (FUNC(type_name)(s))
				{
					if (FUNC(char)(s, ')'))
					{
						is_set = 1;
						return is_set;
					}
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(unary_operator)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(char)(s, '&'))
		{
			is_set = 1;
		}
		else if (FUNC(char)(s, '*'))
		{
			is_set = 1;
		}
		else if (FUNC(char)(s, '+'))
		{
			is_set = 1;
		}
		else if (FUNC(char)(s, '-'))
		{
			is_set = 1;
		}
		else if (FUNC(char)(s, '~'))
		{
			is_set = 1;
		}
		else if (FUNC(char)(s, '!'))
		{
			is_set = 1;
		}
	}

	return is_set;
}


FUNCTION_INLINE int FUNC(postfix_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(primary_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(postfix_expression)(s))
		{
			if (FUNC(char)(s, '['))
			{
				if (FUNC(expression)(s))
				{
					if (FUNC(char)(s, ']'))
					{
						is_set = 1;
						return is_set;
					}
				}
			}
			if (FUNC(char)(s, '('))
			{
				if (FUNC(assignment_expression_list)(s))
				{
				}
				if (FUNC(char)(s, ')'))
				{
					is_set = 1;
					return is_set;
				}
			}
			if (FUNC(char)(s, '.'))
			{
				if (FUNC(identifier)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
			if (FUNC(pchar)(s, "->"))
			{
				if (FUNC(identifier)(s))
				{
					is_set = 1;
					return is_set;
				}
			}
			if (FUNC(pchar)(s, "++"))
			{
				is_set = 1;
				return is_set;
			}
			if (FUNC(pchar)(s, "--"))
			{
				is_set = 1;
				return is_set;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(primary_expression)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(identifier)(s))
		{
			is_set = 1;
		}
		else if (FUNC(constant)(s))
		{
			is_set = 1;
		}
		else if (FUNC(string)(s))
		{
			is_set = 1;
		}
		else if (FUNC(char)(s, '('))
		{
			if (FUNC(expression)(s))
			{
				if (FUNC(char)(s, ')'))
				{
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(assignment_expression_list)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(assignment_expression)(s))
		{
			is_set = 1;
		}
		else if (FUNC(assignment_expression_list)(s))
		{
			if (FUNC(char)(s, ','))
			{
				if (FUNC(assignment_expression)(s))
				{
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(constant)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(integer_constant)(s))
		{
			is_set = 1;
		}
		else if (FUNC(character_constant)(s))
		{
			is_set = 1;
		}
		else if (FUNC(floating_constant)(s))
		{
			is_set = 1;
		}
		else if (FUNC(enumeration_constant)(s))
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(enumeration_constant)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(identifier)(s))
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(keyword)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (0)
		{
		}
#define ITEM(s_i) \
		else if (FUNC(pchar)(s, s_i)) \
		{ \
			is_set = 1; \
		}
#include "parse_c_keyword.h"
#undef ITEM
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(program)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		while (FUNC(external_definition)(s))
		{
			is_set++;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(external_definition)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(function_definition)(s))
		{
			is_set++;
		}
		else if (FUNC(data_definition)(s))
		{
			is_set++;
		}
	}

	return is_set;
}
/*
FUNCTION_INLINE int FUNC(function_definition)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(type_specifier)(s))
		{
		}
		if (FUNC(function_declarator)(s))
		{
			if (FUNC(function_body)(s))
			{
				is_set++;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(function_declarator)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(declarator)(s))
		{
			if (FUNC(char)(s, '('))
			{
				if (FUNC(parameter_list))
				{
				}
				if (FUNC(char)(s, ')'))
				{
					is_set++;
				}
			}
		}
	}

	return is_set;
}
*/

FUNCTION_INLINE int FUNC(function_body)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(type_decl_list)(s))
		{
			if (FUNC(function_statement))
			{
				is_set++;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(function_statement)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(char)(s, '{'))
		{
			if (FUNC(declaration_list)(s))
			{
			}
			if (FUNC(statement_list))
			{
				if (FUNC(char)(s, '}'))
				{
					is_set++;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(data_definition)(chars *s)
{
	int is_set = 0;

	if (chars_check(s))
	{
		if (FUNC(pchar)(s, 'extern'))
		{
		}
		if (FUNC(type_specifier)(s))
		{
		}
		if (FUNC(init_declarator_list)(s))
		{
		}
		if (FUNC(char)(s, ';'))
		{
			is_set++;
		}
	}

	return is_set;
}

#endif	/* PARSE_C_H */

