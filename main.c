#include "cube.h"

void print_amap(char **map)
{
    int i, j;
    char c;

    i = 0;
    while (map[i] != NULL)
    {
        j = 0;
        while ((c = map[i][j]) != '\0')
        {
            if (c == ' ')
                printf("b");
            else
                printf("%c", c);
            j++;
        }
        printf("\n");
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

void	fill_line(t_data *game, int *i, int fd, char *line)
{
	int		line_len;
	int		j;

	game->map[*i] = malloc(game->cols + 1);
	if (!game->map[*i])
	{
		close(fd);
		ft_exit();
	}
	line_len = (int)ft_strlen(line);
	printf("Entra aqui. Longitud %d\n", line_len);
	if (line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
	j = -1;
	printf("Linea nº%d\n: %s", (*i), line);
	while (j++ < game->cols)
	{
		printf("Char nº%d: %c",j, line[j]);
		if (j < line_len)
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
	{
		close(fd);
		ft_exit();
	}
	i = 0;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		printf("Linea nº%d: %s", count, line);
        if (count >= game->mapcheck.start_row - 1)
			fill_line(game, &i, fd, line);
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
	printf("Chequeado Mapa.\n");
	fill_map(&game);
	print_amap(game.map);
	free_game_data(&game);
}