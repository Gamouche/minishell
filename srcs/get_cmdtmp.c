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
#include <stdbool.h>
#include "../includes/minishell.h"
#include "../includes/read_user_input.h" // fgkjh

# define SUITECMD "\e[1m\x1B[32mSUITE CMD $> \x1B[0m" // kjerhefn

int is_sep(int c) { return (ft_strchr(MSH_CMD_SEPARATORS, c) != NULL);  }
int is_not_sep(int c) { return (ft_strchr(MSH_CMD_SEPARATORS, c) == NULL);  }

void	special_case_management(char *input)
{
	while (*input != 0)
	{
		if (*input == '&' || *input == '|')
		{
			if (*(input += 2) == 0)
				return ;
			while (is_sep(*input))
				if (*input++ == 0)
					return ;
			if (*input == 0)
				return ;
			else if (*input == ';' && (*input = ' '))
				while (*input != 0)
				{
					if (is_sep(*input))
						++input;
					if (*input == ';')
						*input = ' ';
					if ((is_not_sep(*input) && *input != ';') || *input == 0)
						return ;
				}
		}
		++input;
	}
}


bool	need_reinput(char *input)
{
	char c = *input;
	//printf(" == |%s|\n", input);

	++input;
	if (*input == 0)
		return false;
	while ( is_sep(*input) )
	{
		if (*input == 0)
			break ;
		++input;
	}
	if (*input == 0 && c != ';')
		return true;

	return false;
}

bool	input_is_valid(const char *input)
{
	if (input[0] == '&' || input[0] == '|')
		return (false);

	while (*input != '\0')
	{
		if (*input == '&')
		{
			if (*(input + 1) != '&')
				return (false);
			++input;

		}

		if (*input == '&')
		{
			const char *tmp = input;
			++tmp;
			if (*tmp == 0)
				return true;
			++tmp;
			if (*tmp == 0)
				return true;
			while ( is_sep(*tmp) )
			{
				if (*tmp == 0)
					return true;
				++tmp;
			}
			if (*tmp == '&' || *tmp == '|')
				return false;
		}

		if (*input == ';' && *(input + 1) == ';')
			return (false);

		if (*input == ';')
		{
			const char *tmp = input + 1;
			while ( is_sep(*tmp) )
			{
				if (*tmp == 0)
					return true;
				++tmp;
			}
			if (*tmp == '&' || *tmp == '|')
				return false;
		}

		if (*input == '|')
		{
			if (*(input + 1) != '|')
				return (false);
			++input;
		}

		if (*input == '|')
		{
			const char *tmp = input;
			++tmp;
			if (*tmp == 0)
				return true;
			++tmp;
			if (*tmp == 0)
				return true;
			while ( is_sep(*tmp) )
			{
				if (*tmp == 0)
					return true;
				++tmp;
			}
			if (*tmp == '&' || *tmp == '|')
				return false;
		}

		++input;
	}

	return (true);
}

bool	check_if_input_is_full_blank(const char *input)
{
	while ( is_sep(*input) )
	{
		if (*input == 0)
			return (true);
		++input;
	}

	return (false);
}

void debug_print_list(struct s_msh_cmd *ptr)
{
	if (ptr == 00)
	{
		printf("\n----------\tPAS DE LISTE\n");
		return ;
	}

	printf("\n----------\tLISTE\n");
	while (ptr != NULL)
	{
		printf("cmd = |%s|\n", ptr->cmd);
		printf("connec = ");
		switch (ptr->connection)
		{
			case (MSH_CON_NONE) :
				printf("NONE\n");
				break ;
			case (MSH_CON_AND) :
				printf("AND\n");
				break ;
			case (MSH_CON_SEMICOLON) :
				printf("SEMICOLON\n");
				break ;
			case (MSH_CON_OR) :
				printf("OR\n");
				break ;
			default :
				printf("DEFAULT\n");
				break ;
		}

		if (ptr->args_cmd)
			for (int i = 0 ; (ptr->args_cmd)[i] ; ++i)
				printf("ARG = |%s|\n", (ptr->args_cmd)[i]);

		ptr = ptr->next;
		printf("\n");
	}
}
// cmd1 un deux trois;cmd2 un deux       trois&&cmd3 un deux trois||cmd4 un    deux trois  ;


// dans terminal faire "ls &&" ca demande a taper la cmd suivante, a reproduire ?

//  ls -l;  pwd  && ls&&pwd;ls -l -a libft ;

void	store_first_argument(struct s_msh_cmd *ll, const char *arg, size_t *nb)
{
	ll->args_cmd = ft_malloc(sizeof(char *) * 2, FATAL_ERROR);
	(ll->args_cmd)[1] = NULL;
	if ( (*(ll->args_cmd) = ft_strdup(arg)) == NULL)
		ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
	*nb = 1;
}

void	store_argument(struct s_msh_cmd *ll, const char *arg)
{
	static size_t 	nb = 0;
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
		if ( ((ll->args_cmd)[nb - 1] = ft_strdup(arg)) == NULL )
			ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
		i = 0;
		while (i < nb - 1)
		{
			if ( ((ll->args_cmd)[i] = ft_strdup(tab_tmp[i])) == NULL )
				ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
			free(tab_tmp[i]);
			++i;
		}
		free(tab_tmp);
	}
}

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

struct s_msh_cmd	*skip_semicolon(char **cmd_input, struct s_msh_cmd *ll_cmd)
{
	if ((*cmd_input)[0] == ';') // passer les ; genre "; ; ; ; cmd" 
	{
		++(*cmd_input);
		while ( is_sep(**cmd_input) )
		{
			if (**cmd_input == 0)
			{
				free(ll_cmd);
				return (CMD_EMPTY);
			}

			++(*cmd_input);
			if (**cmd_input == ';')
			{
				++(*cmd_input);
				if (**cmd_input == 0)
				{
					free(ll_cmd);
					return (CMD_EMPTY);
				}
			}
		}
	}
	return (NULL);
}

void	create_new_node(struct s_msh_cmd **cur_ll, enum e_msh_connection connec)
{									printf("\t\tCREATION\n"); // eergr
	struct s_msh_cmd	*new_elem;
				
	new_elem = ft_malloc(sizeof(*new_elem), FATAL_ERROR);
	new_elem->cmd = NULL;
	new_elem->args_cmd = NULL;
	new_elem->connection = connec;
	new_elem->next = NULL;

	(*cur_ll)->next = new_elem;
	*cur_ll = new_elem;
}

void	isolate_command_or_argument(char **cmd_input, char tmp[1024])
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

struct s_msh_cmd	*complete_input_command(char **cmd_input, char **keep, struct s_msh_cmd *ll_cmd)
{				printf("%s", SUITECMD); fflush(stdout); // efas

	char 	*suite_cmd;
	char	*tmp;

	suite_cmd = read_user_input();
	tmp = *cmd_input;
	*cmd_input = malloc( ft_strlen(tmp) + ft_strlen(suite_cmd) + 1 ); // dhfeow
	(*cmd_input)[0] = 0;

	ft_strcat(*cmd_input, suite_cmd);
	free(suite_cmd);
	free(*keep);
	*keep = *cmd_input;
	if ((*cmd_input)[ft_strlen(*cmd_input) - 1] == '\n')
		(*cmd_input)[ft_strlen(*cmd_input) - 1] = '\0';
	if ( input_is_valid(*cmd_input) == false )
	{
		func_destroy_list(ll_cmd);
		free(*keep);
		return (PARSE_ERROR);
	}
	special_case_management(*cmd_input); // genre cmd1   &&  ; cmd2  => cmd2 a pour connection le AND et non le SEMICOLON
	while (**cmd_input != 0)
	{
		while (**cmd_input == 0x20 || **cmd_input == 0x09 || **cmd_input == 0x0a)
			++(*cmd_input);
		if (**cmd_input == 0)
			break ;
		if (**cmd_input == ';')
			++(*cmd_input);
		if ( is_not_sep(**cmd_input) )
			break ;
	}
	return (NULL);
}

void	manage_semicolon_connection(char **cmd_input, bool *need_new_node, enum e_msh_connection *connec)
{													printf("IF SEMICOLON\n"); // rwef
	*connec = MSH_CON_SEMICOLON;
	*need_new_node = true;
	while ( is_sep(**cmd_input) || **cmd_input == ';' )
	{
		if (**cmd_input == '\0')
			break ;
		++(*cmd_input);
	}
}

struct s_msh_cmd 	*manage_and_connection(struct s_get_cmd_list_var_norme_lol *variables, char **cmd_input, struct s_msh_cmd *ll_cmd)
{						printf("IF AND\n"); // ear
	variables->connec = MSH_CON_AND;
	variables->need_new_node = true;
	(*cmd_input) += 2;
	while ( is_sep(**cmd_input) )
	{
		if (**cmd_input == '\0')
		{
			if ( complete_input_command(cmd_input, &(variables->keep), ll_cmd) == PARSE_ERROR )
				return (PARSE_ERROR);
			break ;
		}
		++(*cmd_input);
	}
	return (NULL);
}

struct s_msh_cmd 	*manage_or_connection(struct s_get_cmd_list_var_norme_lol *variables, char **cmd_input, struct s_msh_cmd *ll_cmd)
{					printf("IF OR\n"); // fssds
	variables->connec = MSH_CON_OR;
	variables->need_new_node = true;
	(*cmd_input) += 2;
	while ( is_sep(**cmd_input) )
	{
		if (**cmd_input == '\0')
		{
			if ( complete_input_command(cmd_input, &(variables->keep), ll_cmd) == PARSE_ERROR )
				return (PARSE_ERROR);
			break ;
		}
		++(*cmd_input);
	}
	return (NULL);
}

void	manage_separators(struct s_get_cmd_list_var_norme_lol *variables, char **cmd_input)
{			printf("IF SEP\n"); // sdvsdv
	variables->need_new_node = false;
	while ( is_sep(**cmd_input) )
	{
		if (**cmd_input == '\0')
			break ;
		++(*cmd_input);
	}
}

struct s_msh_cmd	*skip_sep_and_semicolon(char **cmd_input, struct s_msh_cmd *ll_cmd)
{
	while ( is_sep(**cmd_input) ) 
		++(*cmd_input);
	if ( skip_semicolon(cmd_input, ll_cmd) == CMD_EMPTY )
		return (CMD_EMPTY);
	return (NULL);
}

struct s_msh_cmd	*init_variables_and_check_some_things_on_the_input(struct s_get_cmd_list_var_norme_lol *variables, char *cmd_input)
{
	variables->need_new_node = false;
	variables->keep = cmd_input;
	if (cmd_input[0] == '\0' || check_if_input_is_full_blank(cmd_input) == true )
		return (CMD_EMPTY);
	if ( input_is_valid(cmd_input) == false )
		return (PARSE_ERROR);
	special_case_management(cmd_input); // genre cmd1   &&  ; cmd2  => cmd2 a pour connection le AND et non le SEMICOLON
	return (NULL);
}

struct s_msh_cmd	*manage_connections(char **cmd_input, struct s_get_cmd_list_var_norme_lol *variables, struct s_msh_cmd *ll_cmd)
{
	if (**cmd_input == ';')
		manage_semicolon_connection(cmd_input, &(variables->need_new_node), &(variables->connec));
	else if (**cmd_input == '&')
	{
		if ( manage_and_connection(variables, cmd_input, ll_cmd) == PARSE_ERROR )
			return (PARSE_ERROR);
	}
	else if (**cmd_input == '|')
	{
		if ( manage_or_connection(variables, cmd_input, ll_cmd) == PARSE_ERROR )
			return (PARSE_ERROR);
	}
	else if ( is_sep(**cmd_input) )
		manage_separators(variables, cmd_input);
	else
		printf("\t\t\t\tIF VIDE MDRRRRRR\n"); // fddf
	return (NULL);
}

struct s_msh_cmd	*manage_arg_and_reinput(char **cmd_input, struct s_get_cmd_list_var_norme_lol *variables,
																const char *tmp, struct s_msh_cmd *ll_cmd)
{
	if (variables->cur_ll->cmd == NULL && tmp[0] != '\0') // si cest le premier mot de la cmd en fait
	{
		if ( (variables->cur_ll->cmd = ft_strdup(tmp)) == NULL )
			ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
	}
	else if (tmp[0] != '\0')
		store_argument(variables->cur_ll, tmp);
	else if ( need_reinput(*cmd_input) == true )
	{
		if ( complete_input_command(cmd_input, &(variables->keep), ll_cmd) == PARSE_ERROR )
			return (PARSE_ERROR);
	}


	return (NULL);
}

struct s_msh_cmd	*get_cmd_list(char *cmd_input)
{
	struct s_msh_cmd						*ll_cmd;
	struct s_msh_cmd						*check_func_ret;
	char									tmp[1024];
	struct s_get_cmd_list_var_norme_lol		variables;

	if ( (check_func_ret = init_variables_and_check_some_things_on_the_input(&variables, cmd_input)) != NULL )
		return (check_func_ret);
	ll_cmd = init_first_node(&(variables.cur_ll)); // on sait ici que l'input nest pas vide, on cree donc un premier element pour la liste.
	if ( skip_sep_and_semicolon(&cmd_input, ll_cmd) == CMD_EMPTY )  // passer les blancs genre "      xxxx"  // passer les ; genre "; ; ; ; cmd"
		return (CMD_EMPTY);				//printf("AVANT MEGA LOOP INPUT = |%s|\n", cmd_input);
	while (*cmd_input != '\0') // mega loop
	{
		if (variables.need_new_node == true)
			create_new_node(&(variables.cur_ll), variables.connec);
		variables.connec = MSH_CON_NONE;
		isolate_command_or_argument(&cmd_input, tmp);       printf("tmp = |%s|\n", tmp); // dsrce
		if ( manage_arg_and_reinput(&cmd_input, &variables, tmp, ll_cmd) == PARSE_ERROR )
			return (PARSE_ERROR);
		if (*cmd_input == '\0')
			break ;
		if ( (check_func_ret = manage_connections(&cmd_input, &variables, ll_cmd)) == PARSE_ERROR )
			return (PARSE_ERROR);
		printf("\n=> |%s|\n", cmd_input); // reft
	}
	free(variables.keep);
	return (ll_cmd);
}

/*
struct s_msh_cmd	*get_cmd(void)
{
	struct s_msh_cmd 	*ll_cmd;
	char				*cmd_input;

	cmd_input = read_user_input();

	if (cmd_input[ft_strlen(cmd_input) - 1] == '\n')
		cmd_input[ft_strlen(cmd_input) - 1] = '\0';		

					if (ft_strcmp(cmd_input, "clear") == 0) system("clear");
					else if (ft_strcmp(cmd_input, "qq") == 0) {free(cmd_input);exit(42);} // jkjhouew
	
	ll_cmd = get_cmd_list(cmd_input);
	if (ll_cmd == PARSE_ERROR)
	{
		ft_putstr_fd("minishell: parse error in command line input\n", STDERR_FILENO);
		return (NULL);
	}
	else if (ll_cmd == CMD_EMPTY)
	{
		free(cmd_input);
		return (CMD_EMPTY);
	}

	debug_print_list(ll_cmd); // dsofjkef

	//free(cmd_input);

	return (ll_cmd);
}*/