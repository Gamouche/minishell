/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 19:44:12 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/08 19:44:15 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include "../includes/minishell.h"

void	signal_handler(int sig)
{
	bool	was_running;

	was_running = g_cmd_status.cmd_running;
	if (sig == SIGINT && g_cmd_status.cmd_running == true)
	{
		if (kill(g_cmd_status.pid, sig) == -1)
		{
			write(STDERR_FILENO, "minishell: Cannot kill pid: ", 28);
			ft_putnbr_fd(sig, STDERR_FILENO);
			write(STDERR_FILENO, "\n", 1);
		}
		else
			g_cmd_status.cmd_running = false;
	}
	write(STDOUT_FILENO, "\n", 1);
	if (was_running == false)
		msh_prompt(3);
}
