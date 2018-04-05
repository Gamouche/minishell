/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 19:14:21 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/31 19:14:22 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void debug_print_list(struct s_msh_cmd *ptr)
{							return;return;return;return;return;return;return;return;return;return;
	if (ptr == 00)         ///// commentaire inutile pour ne pas oublier cette fonction anti norme
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
	printf("----------\tEND LISTE\n\n");
}

static struct s_msh_cmd	*skip_semicolon(char **cmd_input, struct s_msh_cmd *ll_cmd)
{
	if ((*cmd_input)[0] == ';') // passer les ; genre "; ; ; ; cmd" 
	{
		++(*cmd_input);
		while (is_sep(**cmd_input))
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

static struct s_msh_cmd	*init_variables_and_check_some_things_on_the_input(
	struct s_get_cmd_list_var_norme_lol *variables, char *cmd_input)
{
	variables->need_new_node = false;
	variables->keep = cmd_input;
	if (cmd_input[0] == '\0' || check_if_input_is_full_blank(cmd_input) == true)
		return (CMD_EMPTY);
	if (input_is_valid(cmd_input) == false)
		return (PARSE_ERROR);
	special_case_management(cmd_input); // genre cmd1   &&  ; cmd2  => cmd2 a pour connection le AND et non le SEMICOLON
	return (NULL);
}

static struct s_msh_cmd	*skip_sep_and_semicolon(char **cmd_input,
										struct s_msh_cmd *ll_cmd)
{
	while (is_sep(**cmd_input))
		++(*cmd_input);
	if (skip_semicolon(cmd_input, ll_cmd) == CMD_EMPTY)
		return (CMD_EMPTY);
	return (NULL);
}

static struct s_msh_cmd	*get_cmd_list(char *cmd_input, struct s_msh_cmd *ll_cmd,
							struct s_msh_cmd *check_func_ret, char tmp[1024])
{
	struct s_get_cmd_list_var_norme_lol		variables;

	if ((check_func_ret = init_variables_and_check_some_things_on_the_input(
	&variables, cmd_input)) != NULL)
		return (check_func_ret);
	ll_cmd = init_first_node(&(variables.cur_ll)); // on sait ici que l'input nest pas vide, on cree donc un premier element pour la liste.
	if (skip_sep_and_semicolon(&cmd_input, ll_cmd) == CMD_EMPTY)  // passer les blancs genre "      xxxx"  // passer les ; genre "; ; ; ; cmd"
		return (CMD_EMPTY);				//printf("AVANT MEGA LOOP INPUT = |%s|\n", cmd_input);
	while (*cmd_input != '\0') // mega loop
	{
		if (variables.need_new_node == true)
			create_new_node(&(variables.cur_ll), variables.connec);
		variables.connec = MSH_CON_NONE;
		isolate_command_or_argument(&cmd_input, tmp);       //printf("tmp = |%s|\n", tmp); // dsrce
		if (manage_arg_and_reinput(&cmd_input, &variables, tmp, ll_cmd)
		== PARSE_ERROR)
			return (PARSE_ERROR);
		if (*cmd_input == '\0')
			break ;
		if ((check_func_ret = manage_connections(
		&cmd_input, &variables, ll_cmd)) == PARSE_ERROR)
			return (PARSE_ERROR);
		//printf("\n=> |%s|\n", cmd_input); // reft
	}
	free(variables.keep);
	return (ll_cmd);
}

struct s_msh_cmd	*get_cmd(void)
{
	struct s_msh_cmd 	*ll_cmd;
	char				*cmd_input;
	char				array_for_get_cmd_list_func[1024];

	cmd_input = read_user_input();

	if (cmd_input[ft_strlen(cmd_input) - 1] == '\n')
		cmd_input[ft_strlen(cmd_input) - 1] = '\0';

				//	if (ft_strcmp(cmd_input, "qq") == 0) {/*puts("a plus dans l\'bus");*/free(cmd_input);exit(42);} // jkjhouew
	
	ll_cmd = get_cmd_list(cmd_input, NULL, NULL, array_for_get_cmd_list_func);
	if (ll_cmd == PARSE_ERROR)
	{
		ft_putstr_fd("minishell: parse error in command line input\n",
		STDERR_FILENO);
		return (NULL);
	}
	else if (ll_cmd == CMD_EMPTY)
	{
		free(cmd_input);
		return (CMD_EMPTY);
	}

	debug_print_list(ll_cmd); // dsofjkef

	return (ll_cmd);
}
