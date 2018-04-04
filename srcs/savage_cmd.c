/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:45:32 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/04 15:45:32 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "../includes/minishell.h"

char		*test_savage_cmd(const char *cmd)
{
	struct stat	s_stat;
	char		*ret;

	if (ft_strchr(cmd, '/') == NULL)
		return (CMD_NOT_FOUND);
	if (stat(cmd, &s_stat) == -1)
		return (CMD_NOT_FOUND);
	if (s_stat.st_mode & S_IXOTH)
	{
		if ((ret = ft_strdup(cmd)) == NULL)
			ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
		return (ret);
	}
	return (CMD_NOPERM);
}
