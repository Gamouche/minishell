void debug_print_list(struct s_msh_cmd *ptr)
{							//return;return;return;return;return;return;return;return;return;return;
	        ///// commentaire inutile pour ne pas oublier cette fonction anti norme
		int printf(const char *, ...);
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
	printf("----------\tEND LISTE\n\n");
}