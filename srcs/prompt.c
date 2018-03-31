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

void	msh_prompt(void)
{
	const char *prompt = "\e[1m\x1B[32mSERGE $> \x1B[0m";

	ft_putstr(prompt);
}

void	msh_prompt_complete_cmd(void)
{
	const char *prompt = "\e[1m\x1B[32mSERGE SUITE $> \x1B[0m";

	ft_putstr(prompt);
}
