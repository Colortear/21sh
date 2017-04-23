/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 00:57:29 by wdebs             #+#    #+#             */
/*   Updated: 2016/10/01 03:22:28 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*forward;

	tmp = *alst;
	while (tmp != NULL)
	{
		forward = tmp->next;
		del(tmp->content, tmp->content_size);
		free(tmp);
		tmp = forward;
	}
	*alst = NULL;
}
