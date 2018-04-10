/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 21:33:18 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/31 21:33:19 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*cut_prompt_string(char *cwd)
{
	char	*cut_cwd;
	size_t	index;

	cut_cwd = cwd;
	index = ft_strlen(cwd) - 1;
	while (cut_cwd + index != cwd)
	{
		if (cut_cwd[index] == '/')
		{
			++index;
			break ;
		}
		--index;
	}
	return (cut_cwd + index);
}

static void	display_arrow(int last_ret_value)
{
	char	arrow[100];

	arrow[0] = '\0';
	ft_strcat(arrow, BOLD);
	if (last_ret_value == 0)
		ft_strcat(arrow, GREEN);
	else
		ft_strcat(arrow, RED);
	ft_strcat(arrow, " $> ");
	ft_strcat(arrow, EOC);
	ft_putstr(arrow);
}

static void	prompt_error(int last_ret_value)
{
	ft_putstr_fd("Error while displaying the minishell\'s prompt\n",
	STDERR_FILENO);
	display_arrow(last_ret_value);
}

void		msh_prompt(int last_ret_value)
{
	char	*cut_cwd;
	char	*cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		prompt_error(last_ret_value);
		return ;
	}
	cut_cwd = cut_prompt_string(cwd);
	prompt = ft_malloc(ft_strlen(cut_cwd) + ft_strlen(GREEN) + ft_strlen(BOLD) +
	ft_strlen(EOC) + 1, FATAL_ERROR);
	ft_strcpy(prompt, BOLD);
	ft_strcat(prompt, GREEN);
	ft_strcat(prompt, cut_cwd);
	ft_strcat(prompt, EOC);
	ft_putstr(prompt);
	display_arrow(last_ret_value);
	free(cwd);
	free(prompt);
}

void		msh_prompt_complete_cmd(void)
{
	const char *prompt = GREEN"cmd > "EOC;

	ft_putstr(prompt);
}
