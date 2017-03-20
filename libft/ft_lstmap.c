/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 01:14:43 by wdebs             #+#    #+#             */
/*   Updated: 2016/10/01 03:39:09 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*tmpa;

	if (lst == NULL)
		return (NULL);
	tmp = f(lst);
	new = ft_lstnew(tmp->content, tmp->content_size);
	if (new)
	{
		tmpa = new;
		lst = lst->next;
		while (lst)
		{
			tmp = f(lst);
			tmpa->next = ft_lstnew(tmp->content, tmp->content_size);
			tmpa = tmpa->next;
			lst = lst->next;
		}
	}
	return (new);
}
