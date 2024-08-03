/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mllamas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:46:32 by mllamas-          #+#    #+#             */
/*   Updated: 2024/04/11 19:13:17 by mllamas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	nb;
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		nb = -n;
		len++;
	}
	else
		nb = n;
	while (nb != 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static int	ft_min(int n, char *str)
{
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		n = 147483648;
	}
	return (n);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_len(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	if (n == 0)
		str[0] = '0';
	n = ft_min(n, str);
	if (len == 0)
		str[0] = '0';
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	str[len] = '\0';
	while (n != 0)
	{
		str[len - 1] = '0' + n % 10;
		n = n / 10;
		len--;
	}
	return (str);
}
