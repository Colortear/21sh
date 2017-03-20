/*42 header goes here*/

#include "21sh.h"

void	add_to_history(t_shell *shell)
{
	t_history	*prev_tmp;

	while (shell->history->next != NULL)
		shell->history = shell->history->next;
	prev_tmp = shell->history;
	shell->history->next = (t_history *)malloc(sizeof(t_history));
	shell->history = shell->history->next;
	shell->history->prev = prev_tmp;
	shell->history->hist_cmd = ft_strdup(shell->cmd);
}
