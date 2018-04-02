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
#include "../includes/prompt.h"

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

void		msh_prompt(void)
{
	char	*cut_cwd;
	char	*cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		ft_exit(FATAL_ERROR, "Error while displaying the minishell \'s prompt\n");
	cut_cwd = cut_prompt_string(cwd);
	prompt = ft_malloc(ft_strlen(cut_cwd) + ft_strlen(GREEN) + ft_strlen(BOLD) + ft_strlen(EOC) + 5, FATAL_ERROR);
	ft_strcpy(prompt, BOLD);
	ft_strcat(prompt, GREEN);
	ft_strcat(prompt, cut_cwd);
	ft_strcat(prompt, " $> ");
	ft_strcat(prompt, EOC);
	ft_putstr(prompt);
	free(cwd);
	free(prompt);
}

void		msh_prompt_complete_cmd(void)
{
	const char *prompt = GREEN"cmd > "EOC;

	ft_putstr(prompt);
}
