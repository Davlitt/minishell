
#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	convert_spaces(char *str)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (d_quotes % 2 == 0))
			s_quotes++;
		if (str[i] == '\"' && (s_quotes % 2 == 0))
			d_quotes++;
		if ((str[i] == '\t' || str[i] == '\r')
			&& (s_quotes % 2 == 0) && (d_quotes % 2 == 0))
			str[i] = ' ';
		i++;
	}
}

void	remove_multi_spaces(char *str)
{
	int	i;
	int	j;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (d_quotes % 2 == 0))
			s_quotes++;
		if (str[i] == '\"' && (s_quotes % 2 == 0))
			d_quotes++;
		if (str[i] && str[i] == ' ' && str[i + 1] == ' '
			&& (s_quotes % 2 == 0) && (d_quotes % 2 == 0))
		{
			j = i + 1;
			while (str[j])
			{
				str[j] = str[j + 1];
				j++;
			}
		}
		else
			i++;
	}
}

int	insert_space(char **str, int pos)
{
	int	i;
	char	*tmp;

	tmp = malloc((ft_strlen(*str) + 1) * sizeof(char));
	if (!tmp)
		return (-1);
	tmp[ft_strlen(*str) + 1] = 0;
	i = 0;
	while (i < pos)
	{
		tmp[i] = (*str)[i];
		i++;
	}
	tmp[i] = ' ';
	while ((*str)[i])
	{
		tmp[i + 1] = (*str)[i];
		i++;
	}
	free(*str);
	*str = tmp;
	return (1);
}

int	add_spaces_before(char **str)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 1;
	s_quotes = 0;
	d_quotes = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' && (d_quotes % 2 == 0))
			s_quotes++;
		if ((*str)[i] == '\"' && (s_quotes % 2 == 0))
			d_quotes++;
		if (((*str)[i] == '>' || (*str)[i] == '<')
			&& (s_quotes % 2 == 0) && (d_quotes % 2 == 0))
		{
			if ((*str)[i - 1] != ' ' && (*str)[i - 1] != (*str)[i])
			{
				if (!insert_space(str, i))
					return (-1);
				i++;
			}
		}
		i++;
	}
	return (1);
}

int	add_spaces_after(char **str)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' && (d_quotes % 2 == 0))
			s_quotes++;
		if ((*str)[i] == '\"' && (s_quotes % 2 == 0))
			d_quotes++;
		if (((*str)[i] == '>' || (*str)[i] == '<')
			&& (s_quotes % 2 == 0) && (d_quotes % 2 == 0))
		{
			if ((*str)[i + 1] != ' ' && (*str)[i + 1] != (*str)[i])
			{
				if (!insert_space(str, i + 1))
					return (-1);
				i++;
			}
		}
		i++;
	}
	return (1);
}

int	add_spaces(char **str)
{
	if (!add_spaces_before(str))
		return (-1);
	if (!add_spaces_after(str))
		return (-1);
	return (1);
}

void	remove_space_begin(char *str)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	if (str[0] == ' ')
		rem_char(&str[0]);
	while (str[i])
	{
		if (str[i] == '\'' && (d_quotes % 2 == 0))
			s_quotes++;
		if (str[i] == '\"' && (s_quotes % 2 == 0))
			d_quotes++;
		if (str[i] == '|' && str[i + 1] == ' '
			&& (s_quotes % 2 == 0) && (d_quotes % 2 == 0))
			rem_char(&str[i + 1]);
		i++;
	}	
}

void	remove_space_end(char *str)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (d_quotes % 2 == 0))
			s_quotes++;
		if (str[i] == '\"' && (s_quotes % 2 == 0))
			d_quotes++;
		if (str[i] == ' ' && str[i + 1] == '|'
			&& (s_quotes % 2 == 0) && (d_quotes % 2 == 0))
			rem_char(&str[i]);
		i++;
	}
	if (str[i - 1] == ' ')
		rem_char(&str[i - 1]);
}

void	replace_spaces(char *str)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (d_quotes % 2 == 0))
			s_quotes++;
		if (str[i] == '\"' && (s_quotes % 2 == 0))
			d_quotes++;
		if (str[i] == ' ' && (s_quotes % 2 == 0) && (d_quotes % 2 == 0))
//			str[i] = 26;
			str[i] = '$';
		i++;
	}
}

int	clean_line(char **str)
{
	
	printf("original:		|%s|\n", *str);
	convert_spaces(*str);
	printf("convert_tabs_returns:	|%s|\n", *str);
	remove_multi_spaces(*str);
	printf("remove_multi_spaces:	|%s|\n", *str);
	remove_space_begin(*str);
	printf("remove_space_begin:	|%s|\n", *str);
	if (!add_spaces(str))
		return (-1);
	printf("add_spaces:		|%s|\n", *str);
	remove_space_end(*str);
	printf("remove_space_end:	|%s|\n", *str);
	replace_spaces(*str);
	printf("replace_spaces:		|%s|\n", *str);
	printf("\n");
	return (1);
}
