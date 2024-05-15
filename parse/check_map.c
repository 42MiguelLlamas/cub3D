#include "../cube.h"

void	fill_map(t_data *game)
{
	int		fd;
	char	*line;
	int		i;

	count_rows(game);
	if (game->rows < 3)
		ft_exit();
	fd = open(game->mapname, O_RDONLY);
	game->map = (char **)malloc(sizeof(char *) * (game->rows + 1));
	if (!game->map)
		ft_exit();
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		game->map[i] = line;
		if (!game->map[i])
		{
			ft_free(game->map);
			ft_exit();
		}
		line = get_next_line(fd);
		i++;
	}
	game->map[i] = line;
}

void	check_line(t_data *game, char *line)
{
	char	**split;

	split = ft_split(line, 32);
	if (!split || (split[2] != NULL && split[2][0] != '\n'))
		ft_exit();
	if (split[0][0] == 78 && split[0][1] == 79 && split[0][2] == 0)
	{
		fill_texture(split[1], WE)
		game->north->id = NO;
		game->north->path = ft_strdup(split[1]);
	}
	else if (split[0][0] == 83 && split[0][1] == 79 && split[0][2] == 0)
	{
		fill_texture(split[1], WE)
		game->south->id = SO;
		game->south->path = ft_strdup(split[1]);
	}
	else if (split[0][0] == 87 && split[0][1] == 69 && split[0][2] == 0)
	{
		fill_texture(split[1], WE)
		game->west->id = WE;
		game->west->path = ft_strdup(split[1]);
	}
	else if (split[0][0] == 69 && split[0][1] == 65 && split[0][2] == 0)
	{
		fill_texture(split[1], WE)
		game->east->id = EA;
		game->east->path = ft_strdup(split[1]);
	}
	else if (split[0][0] == 70 && split[0][1] == 0)
	{
		fill_color(split[1], C);
		game->floor->id = F;
		game->floor->path = ft_strdup(split[1]);
	}
	else if (split[0][0] == 67 && split[0][1] == 0)
	{
		fill_color(split[1], C);
		game->ceiling->id = C;
		game->ceiling->path = ft_strdup(split[1]);
	}
	else
	{
		ft_exit();
	}

	ft_free(split);

}


void	check_textures(t_data *game)
{
	char	*line;
	int		fd;

	fd = open(game->mapname, O_RDONLY);
	if (fd < 0)
		ft_exit();
	line = get_next_line(fd);
	while (line)
	{
		check_line(game, line);
		free(line);
		line = get_next_line(fd);
	}

	close(fd);
}

void	check_map(t_data *game)
{
	check_textures(game);
	//fill_map(game);
}