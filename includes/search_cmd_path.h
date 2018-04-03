/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd_path.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 18:10:53 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/03 18:10:59 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCH_CMD_PATH_H

# define SEARCH_CMD_PATH_H

# define CMD_NOPERM ((char *)-1)
# define CMD_NOT_FOUND ((char *)-2)


/*
**	search_cmd_path.c
*/
char	*search_cmd_path(const char *cmd, char **env);

#endif