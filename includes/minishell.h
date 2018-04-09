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
# include "read_user_input.h"
# include "prompt.h"
# include "get_cmd.h"
# include "execute_commands.h"
# include "environ.h"
# include "search_cmd_path.h"
# include "execute_program.h"
# include "builtins.h"
# include "signal_management.h"

# define FATAL_ERROR (2)

#endif
