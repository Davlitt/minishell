
#include "minishell.h"

int	strstr_len(char **str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

int	nbr_args(char **split_cmnd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (split_cmnd[i])
	{
		if (split_cmnd[i][0] == '<' || split_cmnd[i][0] == '>')
			j--;
		else
			j++;
		i++;
	}
	j--;
	if (j < 0)
		j = 0;
	return (j);
}

char	**get_args(char **split_cmnd)
{
	int	i;
	int	j;
	char	**args;

	args = malloc((nbr_args(split_cmnd) + 1) * sizeof(char *));
	if (!args)
		return (0);
	args[nbr_args(split_cmnd)] = 0;
	i = 0;
	j = -1;
	while (split_cmnd[i])
	{
		if (split_cmnd[i][0] == '<' || split_cmnd[i][0] == '>')
		{
			i++;
			if (split_cmnd[i] != 0)
				i++;
		}
		else
		{
			if (j >= 0)
				args[j] = ft_strdup(split_cmnd[i]);
			j++;
			i++;
		}
	}
	return (args);
}

void	get_file_in(t_cmnd *cmnd, char **split_cmnd)
{
	int	i;

	i = 0;
	cmnd->file_in = 0;
	cmnd->type_redir_in = 0;
	while (split_cmnd[i])
	{
		if ((split_cmnd)[i][0] == '<')
		{
			cmnd->type_redir_in = 1;
			if ((split_cmnd)[i][1] == '<')
				cmnd->type_redir_in = 2;
			i++;
			if (split_cmnd[i])
			{
				if (cmnd->file_in != 0)
					free(cmnd->file_in);
				cmnd->file_in = ft_strdup(split_cmnd[i]);
			}
		}
		if (split_cmnd[i])
			i++;
	}
}

void	get_file_out(t_cmnd *cmnd, char **split_cmnd)
{
	int	i;

	i = 0;
	cmnd->file_out = 0;
	cmnd->type_redir_out = 0;
	while (split_cmnd[i])
	{
		if (split_cmnd[i][0] == '>')
		{
			cmnd->type_redir_out = 1;
			if (split_cmnd[i][1] == '>')
				cmnd->type_redir_out = 2;
			i++;
			if (split_cmnd[i])
			{
				if (cmnd->file_out != 0)
					free(cmnd->file_out);
				cmnd->file_out = ft_strdup(split_cmnd[i]);
			}
		}
		if (split_cmnd[i])
			i++;
	}
}

char *get_prgm(char **split_cmnd)
{
	int	i;
	char	*prgm;

	i = 0;
	prgm = 0;
	while (split_cmnd[i])
	{
		if (split_cmnd[i][0] == '<' || split_cmnd[i][0] == '>')
		{
			if (split_cmnd[i + 1] != 0)
				i++;
		}
		else
			return (ft_strdup(split_cmnd[i]));
		i++;
	}
	return (0);
}

int	get_cmnd(t_cmnd **cmnd, char *line, int i)
{
	char**	split_cmnd;

	if (i == 0)
	{
		(*cmnd) = malloc(sizeof(t_cmnd));
		if (!(*cmnd))
			return (-1);
		(*cmnd)->prev = 0;
	}
	else
	{
		while ((*cmnd)->next != 0)
			(*cmnd) = (*cmnd)->next;
		(*cmnd)->next = malloc(sizeof(t_cmnd));
		if (!(*cmnd)->next)
			return (-1);
		(*cmnd)->next->prev = (*cmnd);
		(*cmnd) = (*cmnd)->next;
	}
	(*cmnd)->next = 0;
//	split_cmnd = ft_strsplit(line, 26);
	split_cmnd = ft_strsplit(line, '$');
	(*cmnd)->prgm = get_prgm(split_cmnd);
	(*cmnd)->args = get_args(split_cmnd);
	get_file_in((*cmnd), split_cmnd);
	get_file_out((*cmnd), split_cmnd);
	free_split(split_cmnd);
	return (1);
}

t_cmnd	*parsing(char *str)
{
	char	**split_line;
	t_cmnd	*cmnd;
	int	i;

	i = 0;
	cmnd = 0;
	split_line = ft_strsplit(str, '|');
	while (split_line[i])
	{
		get_cmnd(&cmnd, split_line[i], i);
		i++;
	}
	free_split(split_line);
	while (cmnd && cmnd->prev != 0)
		cmnd = cmnd->prev;
	return (cmnd);
}


