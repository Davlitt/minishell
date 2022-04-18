
#include "minishell.h"

void	rem_char(char *str)
{
	while (*str)
	{
		*str = *(str + 1);
		str++;
	}
}

void	remove_quotes_str(char *str)
{
	int	i;
	int	j;
	int	in_s_quotes;
	int	in_d_quotes;

	if (str == 0)
		return;
	i = 0;
	in_s_quotes = 0;
	in_d_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && in_s_quotes == 0 && in_d_quotes == 0)
		{
			in_s_quotes = 1;
			rem_char(&str[i]);
			i--;
		}
		else if (str[i] == '\'' && in_s_quotes == 1)
		{
			in_s_quotes = 0;
			rem_char(&str[i]);
			i--;
		}
		if (str[i] == '\"' && in_d_quotes == 0 && in_s_quotes == 0)
		{
			in_d_quotes = 1;
			rem_char(&str[i]);
			i--;
		}
		else if (str[i] == '\"' && in_d_quotes == 1)
		{
			in_d_quotes = 0;
			rem_char(&str[i]);
			i--;
		}
		i++;
	}
}

void	remove_quotes(t_cmnd *cmnd)
{
	int	i;

	while (cmnd)
	{
		remove_quotes_str(cmnd->prgm);
		i = 0;
		while(cmnd->args[i])
		{
			remove_quotes_str(cmnd->args[i]);
			i++;
		}
		remove_quotes_str(cmnd->file_in);
		remove_quotes_str(cmnd->file_out);
		cmnd = cmnd->next;
	}
}

int	process_cmnd(t_cmnd *cmnd)
{
	remove_quotes(cmnd);

	return (1);
}
