
#include "minishell.h"

int	main(int argc, char **argv)
{
	t_cmnd	*cmnd;
	char	*str;

	str = ft_strdup(argv[1]);
	clean_line(&str);
	if (!checks_str(str))
	{
		printf("invalid line\n");
		free(str);
		return (2);
	}
	cmnd = parsing(str);
/*	if (!checks_cmnd(cmnd))
	{
		printf("invalid line\n");
		free_cmnd(cmnd);
		free(str);
		return (2);
	}
*/	process_cmnd(cmnd);

	t_cmnd *tmp = cmnd;
	while (tmp)
	{
		printf("prgm:		|%s|\n", tmp->prgm);
		int i = 0;
		while(tmp->args[i])
		{
			printf("arg:		|%s|\n", tmp->args[i]);
			i++;
		}
		printf("file_in:	|%s|\n", tmp->file_in);
		printf("type_redir_in:	|%i|\n", tmp->type_redir_in);
		printf("file_out:	|%s|\n", tmp->file_out);
		printf("type_redir_out:	|%i|\n", tmp->type_redir_out);
		printf("\n");

		tmp = tmp->next;
	}
	free_cmnd(cmnd);
	free(str);
	return (0);
}
