/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:55:53 by carlos-m          #+#    #+#             */
/*   Updated: 2024/08/01 17:55:57 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_callocc(size_t count, size_t size)
{
	void			*b;
	unsigned char	*ptr;
	size_t			i;

	i = count * size;
	b = malloc(i);
	if (!b)
		return (b);
	ptr = b;
	while (i > 0)
	{
		ptr[i - 1] = 0;
		i--;
	}
	return ((void *)ptr);
}

char	*ft_strchrr(char *ptr, int c)
{
	char	a;

	a = (char)c;
	while (*ptr != a && *ptr)
		ptr++;
	if (*ptr != a)
		return (0);
	return (ptr);
}

size_t	ft_strleng(char *s)
{
	size_t	a;

	a = 0;
	while (*s)
	{
		a++;
		s++;
	}
	return (a);
}

char	*ft_strjoinn(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strleng(s1) + ft_strleng(s2);
	str = ft_callocc((len + 1) * sizeof(char), 1);
	if (!str)
		ft_freeleft(&s1);
	while (s1[i])
	{
		str[i] = (char)s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = (char)s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

int	output_len(char *str)
{
	int	len;

	len = 0;
	if (*str == '\n')
		return (0);
	while (*str != '\n' && *str)
	{
		str++;
		len++;
	}
	return (len);
}
