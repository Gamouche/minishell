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

# define SUITECMD "\e[1m\x1B[32mSUITE CMD $> \x1B[0m" // kjerhefn

int is_sep(int c) { return (ft_strchr(MSH_CMD_SEPARATORS, c) != NULL);  }
int is_not_sep(int c) { return (ft_strchr(MSH_CMD_SEPARATORS, c) == NULL);  }


void	arrangement_de_cas_special(char *input)
{
	while (*input != 0)
	{
		if (*input == '&' || *input == '|')
		{
			input += 2;
			if (*input == 0)
				return ;
			while ( is_sep(*input) )
			{
				if (*input == 0)
					return ;
				++input;
			}
			if (*input == 0)
				return ;
			else if (*input == ';')
				*input = ' ';
		}

		++input;
	}
}


bool	need_suite(char *input)
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

void	argument(struct s_msh_cmd *ll, const char *s)
{
	static int 	nb = 0;
	char		**tab_tmp;

	if (ll->args_cmd == NULL)
	{
											printf("PREMIER ARG A ALLOUER = |%s|\n", s); // jksfdhgkjs
		ll->args_cmd = malloc(sizeof(char *) * 2); // dsvs
		(ll->args_cmd)[1] = NULL;
		*(ll->args_cmd) = ft_strdup(s); // fzdz
		nb = 1;
	}
	else
	{
											//printf("PAS PREMIER ARG A ALLOUER\n");
		nb += 1;
		tab_tmp = ll->args_cmd;				printf("ALLOCATION POUR %d ARGS\n", nb);
		ll->args_cmd = malloc(sizeof(char *) * (nb + 1)); // isdgr
		(ll->args_cmd)[nb] = NULL;
		(ll->args_cmd)[nb - 1] = ft_strdup(s); // kjfjsrd 

		for (int i = 0 ; i < nb - 1 ; ++i)
		{
											//printf("DUP DE LARG |%s|\n",tab_tmp[i] );
			(ll->args_cmd)[i] = ft_strdup(tab_tmp[i]); // khdgddsf
			free(tab_tmp[i]);
		}

		free(tab_tmp);

	}
	
}

struct s_msh_cmd	*get_cmd_list(char *cmd_input)
{
	struct s_msh_cmd		*ll_cmd;
	struct s_msh_cmd		*cur_ll;
	char					tmp[1024];
	size_t					i;
	enum e_msh_connection	connec;
	int						new = 0;
	char					*keep = cmd_input;

	if (cmd_input[0] == '\0' || check_if_input_is_full_blank(cmd_input) == true )
		return (CMD_EMPTY);
	if ( input_is_valid(cmd_input) == false )
		return (PARSE_ERROR);
	arrangement_de_cas_special(cmd_input); // genre cmd1   &&  ; cmd2  => cmd2 a pour connection le AND et non le SEMICOLON

	// on sait ici que l'input nest pas vide, on cree donc un premier element pour la liste.
	ll_cmd = malloc(sizeof(struct s_msh_cmd)); // dsfw
	ll_cmd->cmd = NULL; ll_cmd->args_cmd = NULL ; ll_cmd->connection = MSH_CON_NONE ; ll_cmd->next = NULL;
	cur_ll = ll_cmd;


	while ( is_sep(*cmd_input) ) // passer les blancs genre "      xxxx"
	{
		++cmd_input;
	}


	if (cmd_input[0] == ';') // passer les ; genre "; ; ; ; cmd"
	{
		++cmd_input;
		while ( is_sep(*cmd_input) )
		{
			if (*cmd_input == 0)
			{
				free(ll_cmd);
				return (CMD_EMPTY);
			}

			++cmd_input;
			if (*cmd_input == ';')
			{
				++cmd_input;
				if (*cmd_input == 0)
				{
					free(ll_cmd);
					return (CMD_EMPTY);
				}
			}
		}

		//cmd_input = keep;
	}

	while (*cmd_input != '\0')
	{
		if (new)
		{
																	printf("\t\tCREATION\n");
			struct s_msh_cmd	*new_elem;
			new_elem = malloc(sizeof(*new_elem)); // protect
			new_elem->cmd = NULL;
			new_elem->args_cmd = NULL;
			new_elem->connection = connec;
			new_elem->next = NULL;

			cur_ll->next = new_elem;
			cur_ll = new_elem;
		}


		connec = MSH_CON_NONE;
		i = 0;
		while (*cmd_input != ';' && *cmd_input != '&' && *cmd_input != '|'
		&& is_not_sep(*cmd_input)
		&& *cmd_input != '\0') 
		{
			tmp[i] = *cmd_input;
			++i;
			++cmd_input;
		}
		tmp[i] = '\0';

													//printf("tmp = |%s|\n", tmp); // dsrce
		if (cur_ll->cmd == NULL && tmp[0] != '\0') // si cest le premier mot de la cmd en fait
			cur_ll->cmd = ft_strdup(tmp); // protect
		else if (tmp[0] != '\0')
			argument(cur_ll, tmp);
		else if ( need_suite(cmd_input) == true )
		{
			//printf("NEED SUITE CMD\n"); // drse
			printf("%s", SUITECMD); fflush(stdout); // efas
			char *suite_cmd = read_user_input();
			char *tmp = cmd_input; // dfdf
			cmd_input = malloc( ft_strlen(tmp) + ft_strlen(suite_cmd) + 1 ); // dhfeow
			cmd_input[0] = 0;

			ft_strcat(cmd_input, tmp);
			ft_strcat(cmd_input, suite_cmd);
			free(suite_cmd);
			free(keep);
			keep = cmd_input;
			if (cmd_input[ft_strlen(cmd_input) - 1] == '\n')
				cmd_input[ft_strlen(cmd_input) - 1] = '\0';
			if ( input_is_valid(cmd_input) == false )
			{
				// free la liste
				// enfin tout free quoi, le keep etc ?
				func_destroy_list(ll_cmd);
				free(keep);
				return (PARSE_ERROR);
			}
		}
		else
			;//printf("RIEN\n");
		

		if (*cmd_input == '\0')
			break ;
		else if (*cmd_input == ';')
		{																			printf("IF SEMICOLON\n");
			connec = MSH_CON_SEMICOLON;
			new = 1;
			while ( is_sep(*cmd_input) || *cmd_input == ';' )
			{
				if (*cmd_input == '\0')
					break ;
				++cmd_input;
			}

		}
		else if (*cmd_input == '&')
		{																			printf("IF AND\n");
			connec = MSH_CON_AND;
			new = 1;
			cmd_input += 2;
			while ( is_sep(*cmd_input) )
			{
				if (*cmd_input == '\0')
				{
					//if ( need_suite(cmd_input) == true )
				//	printf("NEED SUITE CMD 2\n"); // drse
					printf("%s", SUITECMD); fflush(stdout); // efas

					char *suite_cmd = read_user_input();
					char *tmp = cmd_input; // dfdf
					cmd_input = malloc( ft_strlen(tmp) + ft_strlen(suite_cmd) + 1 ); // dhfeow
					cmd_input[0] = 0;

					ft_strcat(cmd_input, tmp);
					ft_strcat(cmd_input, suite_cmd);
					free(suite_cmd);
					free(keep);
					keep = cmd_input;
					if (cmd_input[ft_strlen(cmd_input) - 1] == '\n')
						cmd_input[ft_strlen(cmd_input) - 1] = '\0';
					if ( input_is_valid(cmd_input) == false )
					{
						// free la liste
						// enfin tout free quoi, le keep etc ?
						func_destroy_list(ll_cmd);
						free(keep);
						return (PARSE_ERROR);
					}
					break ;
				}
				++cmd_input;
			}

		}
		else if (*cmd_input == '|')
		{																			printf("IF OR\n");
			connec = MSH_CON_OR;
			new = 1;
			cmd_input += 2;
			while ( is_sep(*cmd_input) )
			{
				if (*cmd_input == '\0')
				{
					printf("NEED SUITE CMD 2\n"); // drse
					printf("%s", SUITECMD); fflush(stdout); // efas

					char *suite_cmd = read_user_input();
					char *tmp = cmd_input; // dfdf
					cmd_input = malloc( ft_strlen(tmp) + ft_strlen(suite_cmd) + 1 ); // dhfeow
					cmd_input[0] = 0;

					ft_strcat(cmd_input, tmp);
					ft_strcat(cmd_input, suite_cmd);
					free(suite_cmd);
					free(keep);
					keep = cmd_input;
					if (cmd_input[ft_strlen(cmd_input) - 1] == '\n')
						cmd_input[ft_strlen(cmd_input) - 1] = '\0';
					if ( input_is_valid(cmd_input) == false )
					{
						// free la liste
						// enfin tout free quoi, le keep etc ?
						func_destroy_list(ll_cmd);
						free(keep);
						return (PARSE_ERROR);
					}
					break ;
				}
				++cmd_input;
			}
		}
		else if ( is_sep(*cmd_input) )
		{																			printf("IF SEP\n");
			new = 0;
			while ( is_sep(*cmd_input) )
			{
				if (*cmd_input == '\0')
					break ;
				++cmd_input;
			}
		}
		else
		{
																					printf("\t\t\t\tIF VIDE MDRRRRRR\n");
		}


		printf("\n=> |%s|\n", cmd_input);
		//getchar(); // dsklfjr
	}



	free(keep);
	return (ll_cmd);
}


struct s_msh_cmd	*get_cmd(void)
{
	struct s_msh_cmd 	*ll_cmd;
	char				*cmd_input;

	cmd_input = read_user_input();

	if (cmd_input[ft_strlen(cmd_input) - 1] == '\n')
		cmd_input[ft_strlen(cmd_input) - 1] = '\0';		

					if (ft_strcmp(cmd_input, "clear") == 0) system("clear");//else if (ft_strcmp(cmd_input, "qq") == 0) {free(cmd_input);exit(42);} // jkjhouew
	
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
}