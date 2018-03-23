/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 17:28:40 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/23 17:28:41 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "../includes/minishell.h"

static void			alloc_and_store(char **final_str, size_t old_size, size_t size, char tmp[])
{
	char	*tmp_ptr;

	tmp_ptr = *final_str;
	if ( (*final_str = ft_realloc(*final_str, old_size + 1, size + 1)) == NULL )
		my_exit(FATAL_ERROR, "Call to malloc() failed\n");
	if (tmp_ptr == NULL)
		(*final_str)[0] = '\0';
	ft_strcat(*final_str, tmp);
}

char				*read_user_input(void)
{
	char	tmp[500];
	ssize_t	ret_read;
	char	*final_str;
	//char	*tmp_ptr;
	size_t	size;
	size_t	old_size;

	final_str = NULL;
	size = 0;
	old_size = 0;
	while (1)
	{
		if ( (ret_read = read(STDOUT_FILENO, tmp, sizeof(tmp) - 1)) == -1 )
			my_exit(FATAL_ERROR, "Call to read() failed\n");

		tmp[ret_read] = '\0';

		
		
		size += ret_read;

		alloc_and_store(&final_str, old_size, size, tmp);
/*
		tmp_ptr = final_str;
		if ( (final_str = ft_realloc(final_str, old_size + 1, size + 1)) == NULL )
			my_exit(FATAL_ERROR, "Call to malloc() failed\n");
		if (tmp_ptr == NULL)
			final_str[0] = '\0';
		ft_strcat(final_str, tmp);
*/


		old_size = size;

		if (tmp[ret_read - 1] == '\n')
			break ;

	}

	return (final_str);
}

struct s_msh_cmd	*get_cmd(void)
{
	struct s_msh_cmd 	*ll_cmd;
	char				*cmd_input;

	//ll_cmd = ft_malloc(sizeof(struct s_msh_cmd), FATAL_ERROR);
	cmd_input = read_user_input();
	cmd_input[ft_strlen(cmd_input) - 1] = '\0';
	

	free(cmd_input);

	return 0;
}