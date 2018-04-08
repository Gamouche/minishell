/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_llist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 20:04:11 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/31 20:04:12 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

struct s_msh_cmd	*init_first_node(struct s_msh_cmd **cur_ll)
{
	struct s_msh_cmd	*ll_cmd;

	ll_cmd = ft_malloc(sizeof(struct s_msh_cmd), FATAL_ERROR);
	ll_cmd->cmd = NULL;
	ll_cmd->args_cmd = NULL;
	ll_cmd->connection = MSH_CON_NONE;
	ll_cmd->next = NULL;
	*cur_ll = ll_cmd;
	return (ll_cmd);
}

void				create_new_node(struct s_msh_cmd **cur_ll,
								enum e_msh_connection connec)
{
	struct s_msh_cmd	*new_elem;

	new_elem = ft_malloc(sizeof(*new_elem), FATAL_ERROR);
	new_elem->cmd = NULL;
	new_elem->args_cmd = NULL;
	new_elem->connection = connec;
	new_elem->next = NULL;
	(*cur_ll)->next = new_elem;
	*cur_ll = new_elem;
}

void				func_destroy_list(struct s_msh_cmd *ll)
{
	struct s_msh_cmd	*del;
	size_t				i;

	while (ll != NULL)
	{
		del = ll;
		ll = ll->next;
		free(del->cmd);
		if (del->args_cmd)
		{
			i = 0;
			while ((del->args_cmd)[i] != NULL)
			{
				free((del->args_cmd)[i]);
				++i;
			}
		}
		free(del->args_cmd);
		free(del);
	}
}
