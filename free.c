
#include "minishell.h"

void	free_split(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_cmnd(t_cmnd *cmnd)
{
	int	i;
	t_cmnd	*tmp;

	if (!cmnd)
		return ;
	while (cmnd->prev != 0)
		cmnd = cmnd->prev;
	while (cmnd)
	{
		if (cmnd->prev)
			free(cmnd->prev);
		if (cmnd->prgm)
			free(cmnd->prgm);
		i = 0;
		while (cmnd->args[i])
		{
			free(cmnd->args[i]);
			i++;
		}
		free(cmnd->args);
		if (cmnd->file_in)
			free(cmnd->file_in);
		if (cmnd->file_out)
			free(cmnd->file_out);
		tmp = cmnd;
		cmnd = cmnd->next;
	}
	free(tmp);
}
