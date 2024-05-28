#include "cube.h"

void	print_amap(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("%s", map[i]);
		i++;
	}
	printf("\n");
}

void free_texture(t_texture *tex)
{
    if (tex->path)
	{
        free(tex->path);
        tex->path = NULL;
    }
}

void free_map(char **map)
{
    if (!map)
		return;
    for (int i = 0; map[i] != NULL; i++) {
        free(map[i]);
    }
    free(map);
}

void free_game_data(t_data *game)
{
    if (!game)
		return;
    free_texture(&game->north);
    free_texture(&game->south);
    free_texture(&game->west);
    free_texture(&game->east);

    free_map(game->map);
    if (game->mapname) {
        free(game->mapname);
        game->mapname = NULL;
    }
}

void	fill_map(t_data *game)
{
	int		fd;
	char	*line;
	int		i;
	int		count;
	int		line_len;

	fd = open(game->mapname, O_RDONLY);
	game->map = (char **)malloc(sizeof(char *) * (game->rows + 1));
	if (!game->map)
	{
		close(fd);
		ft_exit();
	}
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
        if (count >= game->mapcheck.start_row)
		{
            game->map[i] = malloc(game->cols + 1);
            if (!game->map[i])
			{
                close(fd);
                ft_exit();
            }
            line_len = (int)ft_strlen(line);
            if (line[line_len - 1] == '\n')
                line[line_len - 1] = '\0';
            strncpy(game->map[i], line, line_len);
            memset(game->map[i] + line_len, ' ', game->cols - line_len);
            game->map[i][game->cols] = '\0';
            i++;
		}
        free(line);
        line = get_next_line(fd);
        count++;
    }
    game->map[i] = NULL;
    close(fd);
}


int	main(int argc, char **argv)
{
	t_data	game;
	
	if (argc != 2)
		ft_exit();
	if (ft_strncmp(".cub", argv[1] + ft_strlen(argv[1]) - 4, 4) != 0)
		ft_exit();
	init_data(&game);
	game.mapname = ft_strdup(argv[1]);
	check_map(&game);
	fill_map(&game);
	free_game_data(&game);

}