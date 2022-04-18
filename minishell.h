#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct	s_cmnd
{
	char	*prgm;
	char	**args;

	char	*file_in; //0 si y en a pas, sinon nom du fichier
	int	type_redir_in; //0 si aucune redirection, 1 pour <, 2 pour <<

	char	*file_out; //pareil
	int	type_redir_out;

	struct s_cmnd	*next;
	struct s_cmnd	*prev;
}		t_cmnd;

int	strstr_len(char **str);
int	nbr_args(char **split_cmnd);
t_cmnd	*parsing(char *str);
int	checks_cmnd(t_cmnd *cmnd);
int	checks_str(char *str);
int	clean_line(char **str);
char	*ft_strdup(char *src);
void	rem_char(char *str);
int	ft_strlen(char *str);
void	free_cmnd(t_cmnd *cmnd);
void	free_split(char **str);
int	process_cmnd(t_cmnd *cmnd);
char	**ft_strsplit(char const *s, char c);

#endif
