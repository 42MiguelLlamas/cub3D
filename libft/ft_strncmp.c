/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mllamas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:52:18 by mllamas-          #+#    #+#             */
/*   Updated: 2023/09/26 19:49:44 by mllamas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	p1;
	unsigned char	p2;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && s1[i])
	{
		p1 = (unsigned char )s1[i];
		p2 = (unsigned char )s2[i];
		if (p1 > p2)
			return (1);
		if (p1 < p2)
			return (-1);
		i++;
	}
	if (i == n)
		return (0);
	if (s1[i])
		return (1);
	else if (s2[i])
		return (-1);
	return (0);
}
