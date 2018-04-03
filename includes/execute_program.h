/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:21:24 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/03 20:21:25 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_PROGRAM_H

# define EXECUTE_PROGRAM_H


/*
**	execute_program.c
*/
int		execute_program(struct s_msh_cmd *cur_node, const char *cmd_path, char **env);



#endif