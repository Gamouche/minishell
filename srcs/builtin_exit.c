/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:17:32 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/04 18:17:54 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"

int		builtin_exit(struct s_msh_cmd *cur_node, char **env)
{
	func_destroy_list(cur_node);
	ft_del_2d_char_array(&env);
	exit(EXIT_SUCCESS);
}
