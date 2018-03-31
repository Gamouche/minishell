/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 19:33:58 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/31 19:34:01 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_cmd.h"

void	special_case_management(char *input)
{
	while (*input != 0)
	{
		if (*input == '&' || *input == '|')
		{
			if (*(input += 2) == 0)
				return ;
			while (is_sep(*input))
				if (*input++ == 0)
					return ;
			if (*input == 0)
				return ;
			else if (*input == ';' && (*input = ' '))
				while (*input != 0)
				{
					if (is_sep(*input))
						++input;
					if (*input == ';')
						*input = ' ';
					if ((is_not_sep(*input) && *input != ';') || *input == 0)
						return ;
				}
		}
		++input;
	}
}

bool	check_if_input_is_full_blank(const char *input)
{
	while (is_sep(*input))
	{
		if (*input == 0)
			return (true);
		++input;
	}
	return (false);
}

bool	input_is_valid(const char *input)
{
	if (input[0] == '&' || input[0] == '|')
		return (false);

	while (*input != '\0')
	{
		if (*input == '&')
		{
			if (*(input + 1) != '&')
				return (false);
			++input;

		}

		if (*input == '&')
		{
			const char *tmp = input;
			++tmp;
			if (*tmp == 0)
				return true;
			++tmp;
			if (*tmp == 0)
				return true;
			while ( is_sep(*tmp) )
			{
				if (*tmp == 0)
					return true;
				++tmp;
			}
			if (*tmp == '&' || *tmp == '|')
				return false;
		}

		if (*input == ';' && *(input + 1) == ';')
			return (false);

		if (*input == ';')
		{
			const char *tmp = input + 1;
			while ( is_sep(*tmp) )
			{
				if (*tmp == 0)
					return true;
				++tmp;
			}
			if (*tmp == '&' || *tmp == '|')
				return false;
		}

		if (*input == '|')
		{
			if (*(input + 1) != '|')
				return (false);
			++input;
		}

		if (*input == '|')
		{
			const char *tmp = input;
			++tmp;
			if (*tmp == 0)
				return true;
			++tmp;
			if (*tmp == 0)
				return true;
			while ( is_sep(*tmp) )
			{
				if (*tmp == 0)
					return true;
				++tmp;
			}
			if (*tmp == '&' || *tmp == '|')
				return false;
		}

		++input;
	}

	return (true);
}
