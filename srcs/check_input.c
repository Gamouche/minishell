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

#include "../includes/minishell.h"

bool		check_if_input_is_full_blank(const char *input)
{
	while (is_sep(*input))
	{
		if (*input == 0)
			return (true);
		++input;
	}
	return (false);
}

static int	test_ampersand(const char **input)
{
	const char	*tmp = *input;
	int			dummy;

	dummy = 42;
	if (**input == '&')
	{
		++tmp;
		if (*tmp == 0)
			return (true);
		++tmp;
		if (*tmp == 0)
			return (true);
		while (is_sep(*tmp))
		{
			if (*tmp == 0)
				return (true);
			++tmp;
		}
		if (*tmp == '&' || *tmp == '|')
			return (false);
	}
	return (dummy);
}

static int	test_semicolon(const char **input)
{
	const char	*tmp = (*input) + 1;
	int			dummy;

	dummy = 42;
	if (**input == ';')
	{
		while (is_sep(*tmp))
		{
			if (*tmp == 0)
				return (true);
			++tmp;
		}
		if (*tmp == '&' || *tmp == '|')
			return (false);
	}
	return (dummy);
}

static int	test_pipe(const char **input)
{
	const char	*tmp = *input;
	int			dummy;

	dummy = 42;
	if (**input == '|')
	{
		++tmp;
		if (*tmp == 0)
			return (true);
		++tmp;
		if (*tmp == 0)
			return (true);
		while (is_sep(*tmp))
		{
			if (*tmp == 0)
				return (true);
			++tmp;
		}
		if (*tmp == '&' || *tmp == '|')
			return (false);
	}
	return (dummy);
}

bool		input_is_valid(const char *input)
{
	int		check_ret;

	if (input[0] == '&' || input[0] == '|')
		return (false);
	while (*input != '\0')
	{
		if (*input == '&')
			if (*(input + 1) != '&' || (!(input += 1)))
				return (false);
		check_ret = test_ampersand(&input);
		if (check_ret == true || check_ret == false)
			return (check_ret);
		if (*input == ';' && *(input + 1) == ';')
			return (false);
		check_ret = test_semicolon(&input);
		if (check_ret == true || check_ret == false)
			return (check_ret);
		if (*input == '|')
			if (*(input + 1) != '|' || (!(input += 1)))
				return (false);
		if ((check_ret = test_pipe(&input)) != 42)
			return (check_ret);
		++input;
	}
	return (true);
}
