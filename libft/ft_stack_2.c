#include "libft.h"

void	del_stack(t_stack *s)
{
	t_s_data	*tmp;

	if (!s)
		return ;
	while (s->data)
	{
		tmp = s->data;
		s->data = s->data->prev;
		free(tmp);
	}
	free(s);
}
