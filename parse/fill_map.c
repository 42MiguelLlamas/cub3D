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

#include "../cube.h"

void	check_spaces(t_data *game, int *i, int *j)
{
	int	row;
	int	col;

	row = *i;
	col = *j;
	if (game->map[row][col] == ' ')
	{
		if ((row == 0 || game->map[row - 1][col] == ' ' || \
		game->map[row - 1][col] == '1') && (row == game->rows - 1 || \
		game->map[row + 1][col] == ' ' || game->map[row + 1][col] == '1') \
		&& (col == 0 || game->map[row][col - 1] == ' ' || \
		game->map[row][col - 1] == '1') && (col == game->cols - 1 || \
		game->map[row][col + 1] == ' ' || game->map[row][col + 1] == '1'))
			return ;
		else
			ft_exit(1, game);
	}
}

void	check_valid(t_data *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (i == 0 || j == 0 || j == game->cols - 1 || i == game->rows - 1)
			{
				if (game->map[i][j] == '0')
					ft_exit(1, game);
			}
			check_spaces(game, &i, &j);
			j++;
		}
		i++;
	}
}

void	fill_line(t_data *game, int *i, int fd, char *line)
{
	int		line_len;
	int		j;

	game->map[*i] = malloc(game->cols + 1);
	if (!game->map[*i])
		free_exit(game->map, *i, fd);
	line_len = (int)ft_strlen(line);
	if (line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
	j = -1;
	while (j++ < game->cols)
	{
		if (j < line_len && line[j] != '\0')
			game->map[*i][j] = line[j];
		else
			game->map[*i][j] = ' ';
	}
	game->map[*i][game->cols] = '\0';
	(*i)++;
}

void	fill_map(t_data *game)
{
	int		fd;
	char	*line;
	int		i;
	int		count;

	fd = open(game->mapname, O_RDONLY);
	game->map = (char **)malloc(sizeof(char *) * (game->rows + 1));
	if (!game->map)
		free_exit(game->map, 0, fd);
	i = 0;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (count >= game->mapcheck.start_row - 1)
			fill_line(game, &i, fd, line);
		free(line);
		line = get_next_line(fd);
		count++;
	}
	game->map[i] = NULL;
	close(fd);
	check_valid(game);
}
