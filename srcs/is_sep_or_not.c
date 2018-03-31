/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sep_or_not.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 19:39:55 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/31 19:39:56 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/get_cmd.h"

int		is_sep(int c)
{
	return (ft_strchr(MSH_CMD_SEPARATORS, c) != NULL);
}

int		is_not_sep(int c)
{
	return (ft_strchr(MSH_CMD_SEPARATORS, c) == NULL);
}
