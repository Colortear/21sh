/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:41:38 by wdebs             #+#    #+#             */
/*   Updated: 2017/03/07 01:00:30 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static t_list	*create_list(t_list **list, int fd)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (fd == (int)tmp->content_size)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", 1);
	tmp->content_size = fd;
	ft_lstadd(list, tmp);
	return (tmp);
}

static char		*gnl_append(char *tmp, char *buf, size_t ret)
{
	char	*str;
	size_t	i;
	char	*copy;

	str = ft_strnew(ft_strlen(tmp) + ++ret);
	i = 0;
	copy = tmp;
	while (*tmp)
		str[i++] = *tmp++;
	while (*buf && --ret > 0)
		str[i++] = *buf++;
	free(copy);
	return (str);
}

int				grab_line(const int fd, char **line)
{
	char			buf[2];
	int				ret;
	static t_list	*list = NULL;
	t_list			*temp;
	char			*copy;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	temp = list;
	list = create_list(&temp, fd);
	while ((ret = read(fd, buf, 1)))
	{
		if (buf[0] == 10)
			break ;
		list->content = gnl_append(list->content, buf, ret);
	}
	ret = 0;
	while (((char*)list->content)[ret] && ((char*)list->content)[ret] != '\n')
		++ret;
	*line = ft_strncpy(ft_strnew(ret + 1), list->content, ret);
	if (((char*)list->content)[ret] == '\n')
		++ret;
	copy = list->content;
	list->content = ft_strdup(list->content + ret);
	free(copy);
	list = temp;
	return (ret ? 1 : 0);
}
