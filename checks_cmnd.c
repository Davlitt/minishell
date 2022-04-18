
#include "minishell.h"

int	checks_cmnd(t_cmnd *cmnd)
{
	while (cmnd)
	{
		if (cmnd->type_redir_in > 0 && cmnd->file_in == 0)
			return (0);
		if (cmnd->type_redir_out > 0 && cmnd->file_out == 0)
			return (0);
		cmnd = cmnd->next;
	}
	return (1);
}	
