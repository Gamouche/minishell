/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 19:14:21 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/31 19:14:22 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/read_user_input.h"

struct s_msh_cmd	*get_cmd(void)
{
	struct s_msh_cmd 	*ll_cmd;
	char				*cmd_input;

	cmd_input = read_user_input();

	if (cmd_input[ft_strlen(cmd_input) - 1] == '\n')
		cmd_input[ft_strlen(cmd_input) - 1] = '\0';		

					if (ft_strcmp(cmd_input, "clear") == 0) system("clear");
					else if (ft_strcmp(cmd_input, "qq") == 0) {free(cmd_input);exit(42);} // jkjhouew
	
	ll_cmd = get_cmd_list(cmd_input);
	if (ll_cmd == PARSE_ERROR)
	{
		ft_putstr_fd("minishell: parse error in command line input\n", STDERR_FILENO);
		return (NULL);
	}
	else if (ll_cmd == CMD_EMPTY)
	{
		free(cmd_input);
		return (CMD_EMPTY);
	}

	debug_print_list(ll_cmd); // dsofjkef

	//free(cmd_input);

	return (ll_cmd);
}