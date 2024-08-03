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

char	*ft_freeleft(char **left)
{
	free(*left);
	*left = NULL;
	return (NULL);
}

static char	*get_buffer(int fd, char *line, char *buffer)
{
	int		check;

	check = 1;
	while (check > 0)
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check >= 0)
		{
			buffer[check] = '\0';
			line = ft_strjoinn(line, buffer);
		}
		if (ft_strchrr(buffer, 10))
			break ;
	}
	ft_freeleft(&buffer);
	if (check < 0 || (check == 0 && line[0] == '\0'))
		return (ft_freeleft(&line));
	return (line);
}

char	*get_output(char *str)
{
	char	*output;
	int		len;
	int		i;

	len = output_len(str);
	i = 0;
	output = ft_callocc(len + 2, 1);
	if (!output)
		return (ft_freeleft(&str));
	while (i < len)
	{
		output[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		output[i] = '\n';
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	*get_left(char	*str)
{
	char	*left;
	int		llen;
	int		olen;
	int		len;
	int		i;

	i = 0;
	olen = output_len(str);
	len = ft_strleng(str);
	llen = len - olen;
	left = ft_callocc(llen + 1, 1);
	if (!left)
		return (ft_freeleft(&left));
	while (olen < len)
	{
		left[i] = str[olen + 1];
		i++;
		olen++;
	}
	left[i] = '\0';
	ft_freeleft(&str);
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*output;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
	{
		line = ft_callocc(1, 1);
		if (!line)
			return (ft_freeleft(&line));
	}
	buffer = ft_callocc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (ft_freeleft(&line));
	line = get_buffer(fd, line, buffer);
	if (!line)
		return (ft_freeleft(&line));
	output = get_output(line);
	line = get_left(line);
	return (output);
}
