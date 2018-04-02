/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cmd_special_case_management.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 23:47:29 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/31 23:47:30 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
