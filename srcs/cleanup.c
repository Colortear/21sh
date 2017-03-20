/*42 header goes here*/

#include "21sh.h"

void	cleanup(t_shell *shell)
{
	t_history	*prev_tmp;

	end_termcap(shell);
	while (shell->history != NULL)
	{
		prev_tmp = shell->history->prev;
		shell->history->hist_cmd = NULL;
		free(shell->history->hist_cmd);
		free(shell->history);
		shell->history = prev_tmp;
	}
	shell->cmd ? free(shell->cmd) : 0;
	shell->path ? free(shell->path) : 0;
	shell ? free(shell) : 0;
}
