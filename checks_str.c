
#include "minishell.h"

int	check_redirections(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '|' && (str[i - 1] == '<' || str[i - 1] == '>'))
			return (0);
		i++;
	}
	if (str[i - 1] == '<' || str[i - 1] == '>')
		return (0);
	if (ft_strlen(str) < 3)
		return (1);
	i = 0;
	while (str[i + 2])
	{
		if ((str[i] == '<' || str[i] == '>')
			&& str[i + 1] == '$'
//			&& str[i + 1] == 26
			&& (str[i + 2] == '<' || str[i + 2] == '>'))
			return (0);
		i++;
	}
	return (1);
}

int	check_pipes(char *str)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	if (str[0] == '|' || str[ft_strlen(str) - 1] == '|')
		return (0);
	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (d_quotes % 2 == 0))
			s_quotes++;
		if (str[i] == '\"' && (s_quotes % 2 == 0))
			d_quotes++;
		if ((s_quotes % 2 == 0) && (d_quotes % 2 == 0)
			&& str[i] == '|' && str[i + 1] == '|')
			return (0);
		i++;
	}
	return (1);
}

int	check_quotes(char *str)
{
	int	s_quotes;
	int	d_quotes;

	s_quotes = 0;
	d_quotes = 0;
	while (*str)
	{
		if (*str == '\'' && (d_quotes % 2 == 0))
			s_quotes++;
		if (*str == '\"' && (s_quotes % 2 == 0))
			d_quotes++;
		str++;
	}
	if ((s_quotes % 2 != 0) || (d_quotes % 2 != 0))
		return (0);
	return (1);
}

int	checks_str(char *str)
{
	if (!check_quotes(str))
		return (0);
	if (!check_pipes(str))
		return (0);
	if (!check_redirections(str))
		return (0);
	
	return (1);
}
