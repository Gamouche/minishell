printf("%s", SUITECMD); fflush(stdout); // efas
char *suite_cmd = read_user_input();
char *tmp = cmd_input; // dfdf
cmd_input = malloc( ft_strlen(tmp) + ft_strlen(suite_cmd) + 1 ); // dhfeow
cmd_input[0] = 0;

//ft_strcat(cmd_input, tmp);
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
arrangement_de_cas_special(cmd_input); // genre cmd1   &&  ; cmd2  => cmd2 a pour connection le AND et non le SEMICOLON
while (*cmd_input != 0)
{
while (*cmd_input == 0x20 || *cmd_input == 0x09 || *cmd_input == 0x0a)
++cmd_input;
if (*cmd_input == 0)
break ;
if (*cmd_input == ';')
++cmd_input;
if ( is_not_sep(*cmd_input) )
break ;
}