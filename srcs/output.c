/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 19:32:15 by wdebs             #+#    #+#             */
/*   Updated: 2017/03/16 00:33:37 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	insert_char(char *c)
{
	INSERT_MODE_ON;
	ft_putchar(*c);
	INSRT_MODE_OFF;
}

void	delete_char(t_shell *shell)
{
	int		size;
	char	*tmp;
	
	size = shell->cmd ? ft_strlen(shell->cmd) : 0;
	if (size > 0)
	{
		LEFT;
		DEL_CHAR;
		tmp = ft_strnew(size - 1);
		ft_strncpy(tmp, shell->cmd, size - 1);
		free(shell->cmd);
		shell->cmd = ft_strdup(tmp);
		free(tmp);
	}
}
