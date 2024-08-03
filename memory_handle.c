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

#include "cube.h"

void	free_texture(t_texture *tex)
{
	if (tex->path)
	{
		free(tex->path);
		tex->path = NULL;
	}
}

void	free_game_data(t_data *game)
{
	if (!game)
		return ;
	free_texture(&game->north);
	free_texture(&game->south);
	free_texture(&game->west);
	free_texture(&game->east);
	free(game->player);
	ft_free(game->map);
	if (game->mapname)
	{
		free(game->mapname);
		game->mapname = NULL;
	}
}

void	free_exit(char **sol, int len, int fd)
{
	int	i;

	i = 0;
	if (len > 0)
	{
		while (i < len)
		{
			free(sol[i]);
			i++;
		}
		free(sol);
		sol = NULL;
	}
	if (fd != -1)
		close(fd);
	write (1, "Error\n", 6);
	exit(0);
}

void	ft_free(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	ft_exit(int yes, t_data *game)
{
	if (yes)
		free_game_data(game);
	write (1, "Error\n", 6);
	exit(0);
}
