/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 18:41:32 by wdebs             #+#    #+#             */
/*   Updated: 2017/04/27 21:51:17 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strlcmp(const char *s1, const char *s2, int size, int e)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (s1 && s2 && (s1[i] || s2[i]) && i < size)
	{
		if (s1[i] == 0 || s2[i] == 0)
			ret = -1;
		else if (s1[i] - s2[i] != 0)
			ret = 1;
		if (ret != 0)
			break ;
		i++;
	}
	if (e && i == size && s1[size] != '=')
		ret = -1;
	return (ret);
}
