/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_argument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 20:09:52 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/31 20:09:52 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/get_cmd.h"

static void	store_first_argument(struct s_msh_cmd *ll, const char *arg,
															size_t *nb)
{
	ll->args_cmd = ft_malloc(sizeof(char *) * 2, FATAL_ERROR);
	(ll->args_cmd)[1] = NULL;
	if ((*(ll->args_cmd) = ft_strdup(arg)) == NULL)
		ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
	*nb = 1;
}

void		store_argument(struct s_msh_cmd *ll, const char *arg)
{
	static size_t	nb = 0;
	char			**tab_tmp;
	size_t			i;

	if (ll->args_cmd == NULL) {	printf("PREMIER ARG A ALLOUER = |%s|\n", arg); // jksfdhgkjs
		store_first_argument(ll, arg, &nb);   }
	else
	{
		nb += 1;
		tab_tmp = ll->args_cmd;				printf("ALLOCATION POUR %zu ARGS\n", nb);
		ll->args_cmd = ft_malloc(sizeof(char *) * (nb + 1), FATAL_ERROR);
		(ll->args_cmd)[nb] = NULL;
		if (((ll->args_cmd)[nb - 1] = ft_strdup(arg)) == NULL)
			ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
		i = 0;
		while (i < nb - 1)
		{
			if (((ll->args_cmd)[i] = ft_strdup(tab_tmp[i])) == NULL)
				ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
			free(tab_tmp[i]);
			++i;
		}
		free(tab_tmp);
	}
}

void		isolate_command_or_argument(char **cmd_input, char tmp[1024])
{
	size_t	i;

	i = 0;
	while (**cmd_input != ';' && **cmd_input != '&' && **cmd_input != '|'
	&& is_not_sep(**cmd_input)
	&& **cmd_input != '\0')
	{
		tmp[i] = **cmd_input;
		++i;
		++(*cmd_input);
	}
	tmp[i] = '\0';
}
