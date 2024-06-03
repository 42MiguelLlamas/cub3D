#include "../cube.h"

void print_arr(char **array)
{
	printf("Splitted:");
    if (array == NULL) {
        printf("The array is NULL.\n");
        return;
    }
    for (int i = 0; array[i] != NULL; i++) {
        printf("arr %s\n", array[i]);
    }
	printf("End\n");
}


void print_texture(const t_texture *tex) {
    printf("Texture ID: %d, Path: %s\n", tex->id, tex->path ? tex->path : "None");
}

void print_color(const t_color *col) {
    printf("Color ID: %d, RGB: (%d, %d, %d)\n", col->id, col->r, col->g, col->b);
}


void print_map(char **map) {
    if (!map) {
        printf("Map: None\n");
        return;
    }
    printf("Map:\n");
    for (int i = 0; map[i] != NULL; i++) {
        printf("%s\n", map[i]);
    }
}

void print_game_data(const t_data *game) {
    if (!game) {
        printf("Game data is NULL\n");
        return;
    }

    printf("Game Name: %s\n", game->mapname ? game->mapname : "No name provided");
    print_map(game->map);
    printf("Textures:\n");
    printf("North: ");
    print_texture(&game->north);
    printf("South: ");
    print_texture(&game->south);
    printf("West: ");
    print_texture(&game->west);
    printf("East: ");
    print_texture(&game->east);
    printf("Colors:\n");
    printf("Floor: ");
    print_color(&game->floor);
    printf("Ceiling: ");
    print_color(&game->ceiling);
    printf("Rows: %d, Cols: %d\n, StartRow: %d\n", game->rows, game->cols, game->mapcheck.start_row);
}

void	check_textures(char	**split, t_data *game)
{
	if (split[0][0] == 78 && split[0][1] == 79 && split[0][2] == 0)
		fill_texture(split[1], NO, game);
	else if (split[0][0] == 83 && split[0][1] == 79 && split[0][2] == 0)
		fill_texture(split[1], SO, game);
	else if (split[0][0] == 87 && split[0][1] == 69 && split[0][2] == 0)
		fill_texture(split[1], WE, game);
	else if (split[0][0] == 69 && split[0][1] == 65 && split[0][2] == 0)
		fill_texture(split[1], EA, game);
	else if (split[0][0] == 70 && split[0][1] == 0)
		check_color(split[1], F, game);
	else if (split[0][0] == 67 && split[0][1] == 0)
		check_color(split[1], C, game);
	else
		ft_exit(1, game); //Aqui habria que hacer free si ya hay algo guardado.
}

void	check_line(t_data *game, char *line)
{
	char	**split;

	split = ft_split(line, 32);
	if (!split)
		ft_exit(1, game); //Aqui habria que hacer free si ya hay algo guardado.
	if (split[0][0] == '\n')
	{
		check_inmap(game);
		ft_free(split);
		free(line);
		return ;
	}
	if (!split[1] || (split[2] != NULL && split[2][0] != '\n'))
	{
		ft_free(split);
		free(line);
		ft_exit(1, game); //Aqui habria que hacer free si ya hay algo guardado.
	}
	check_textures(split, game);
	check_inmap(game);
	ft_free(split);
	free(line);
}

void	check_chars(t_data *game, char *line)
{
    int		i;
    char	c;

	i = 0;
	c = 0;
    while (line[i] != '\0')
	{
		c = (char)line[i];
        if (c != '1' && c != '0' && c != ' ' && c != 'N'
			&& c != 'S' && c != 'E' && c != 'W' && c != '\n')
		{
			free(line);
            ft_exit(1, game);
		}
        if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
            if (game->mapcheck.player_counter > 0)
			{
				free(line);
                ft_exit(1, game);
			}
            game->mapcheck.player_counter++;
        }
		i++;
    }
}

void	check_mapline(t_data * game, char *line, int count)
{
	if (game->mapcheck.in_map == 1 && line[0] == '\n')
	{
		free(line);
		return;
	}
	if (game->mapcheck.in_map == 1 && line[0] != '\n')
	{
		check_chars(game, line);
		game->mapcheck.start_row = count;
		game->mapcheck.in_map = 2;
	}
	if (game->mapcheck.in_map == 2)
	{
		if (line[0] == '\n')
		{
			free(line);
			return;
		}
		check_chars(game, line);
		if (game->cols < (int)ft_strlen(line))
			game->cols = ft_strlen(line);
	}
	free(line);
}

void	check_map(t_data *game)
{
	char	*line;
	int		fd;
	int		count;

	fd = open(game->mapname, O_RDONLY);
	if (fd < 0)
		ft_exit(1, game);
	count = 1;
	line = get_next_line(fd);
	while (line)
	{
		check_line(game, line);
		line = get_next_line(fd);
		count++;
		if (game->mapcheck.in_map == 1)
			break ;
	}
	while (line)
	{
		check_mapline(game, line, count);
		line = get_next_line(fd);
		count++;
	}
	game->rows = count - game->mapcheck.start_row;
	close(fd);
}
