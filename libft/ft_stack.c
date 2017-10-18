#include "libft.h"

int		is_empty(t_stack *stack)
{
	if (!stack->size)
		return (1);
	else
		return (0);
}

int		peek(t_stack *stack)
{
	if (!stack->size)
		return (0);
	return (stack->data->data);
}

int		pop(t_stack *stack)
{
	t_s_data	*tmp;

	if (!stack->size)
		return (0);
	tmp = stack->data;
	stack->data = stack->data->prev;
	free(tmp);
	stack->size--;
	return (1);
}

void	push(t_stack *stack, int data)
{
	t_s_data	*new;

	new = malloc(sizeof(t_s_data));
	new->data = data;
	new->prev = stack->data;
	stack->data = new;
	stack->size++;
}
