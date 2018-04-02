/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 19:21:08 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/02 19:21:09 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_COMMANDS_H

# define EXECUTE_COMMANDS_H

# define NOT_BUILTIN (-1)
# define NB_BUILTINS (6)

/*
**	execute_commands.c
*/
int		execute_commands(struct s_msh_cmd *ll_cmd, char *environ[]);

#endif