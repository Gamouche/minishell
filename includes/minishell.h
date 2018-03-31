/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 17:15:28 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/23 17:15:29 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdlib.h>
# include "../libft/includes/libft.h"

					#include <stdio.h> // debuggggggg

# define FATAL_ERROR (2)


enum e_msh_connection
{
	MSH_CON_NONE,
	MSH_CON_SEMICOLON,
	MSH_CON_AND,
	MSH_CON_OR
};

struct s_msh_cmd
{
	char					*cmd;
	char					**args_cmd;
	enum e_msh_connection 	connection;
	struct s_msh_cmd		*next;
};



#endif