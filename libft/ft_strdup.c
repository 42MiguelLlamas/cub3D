/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mllamas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:53:53 by mllamas-          #+#    #+#             */
/*   Updated: 2023/09/19 13:15:39 by mllamas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		len;
	char	*ptr;
	char	*s;
	int		i;

	len = 0;
	i = 0;
	s = (char *)src;
	while (s[len])
		len++;
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (ptr);
	while (i <= len)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}
