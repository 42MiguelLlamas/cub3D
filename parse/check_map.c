#include "../cube.h"

void print_arr(char **array)
{
	printf("Splitted:");
    if (array == NULL) {
        printf("The array is NULL.\n");
        return;
    }
    for (int i = 0; array[i] != NULL; i++) {
        printf("%s\n", array[i]);
    }
	printf("End\n");
}

#include <stdio.h>

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
    printf("Rows: %d, Cols: %d\n", game->rows, game->cols);
}


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

void	fill_texture(char *path, t_ident ident, t_data	*game)
{
	if (ident == NO)
	{
		game->mapcheck.no++;
		game->north.path = ft_strdup(path);
	}
	else if (ident == SO)
	{
		game->mapcheck.so++;
		game->south.path = ft_strdup(path);
	}
	else if (ident == WE)
	{
		game->mapcheck.we++;
		game->west.path = ft_strdup(path);
	}
	else if (ident == EA)
	{
		game->mapcheck.ea++;
		game->east.path = ft_strdup(path);
	}
	if (game->mapcheck.no > 1 || game->mapcheck.so > 1 || 
		game->mapcheck.we > 1 || game->mapcheck.ea > 1)
		ft_exit(); //Aqui habria que hacer free si ya hay algo guardado.
}

void	fill_color(t_data *game, t_ident ident, t_color	*color, char *rgb)
{
	char **split;

	if (ident == F)
		game->mapcheck.f++;
	else if (ident == C)
		game->mapcheck.c++;
	if (game->mapcheck.c > 1 || game->mapcheck.f > 1)
		ft_exit(); //Aqui habria que hacer free si ya hay algo guardado.
	split = ft_split(rgb, 44);
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	ft_free(split);
}

void	check_color(char	*rgb, t_ident ident, t_data *game)
{
	char	**split;
	int		r;
	int		g;
	int		b;
	int		i;

	split = ft_split(rgb, 44);
	if (!split)
		ft_exit();//Aqui habria que hacer free si ya hay algo guardado.
	i = 0;
	while (split[i] != NULL)
		i++;
	if (i != 3)
		ft_exit(); //Aqui habria que hacer free si ya hay algo guardado.
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	ft_free(split);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		ft_exit(); //Aqui habria que hacer free si ya hay algo guardado.
	if (ident == F)
		fill_color(game, F, &game->floor, rgb);
	else if (ident == C)
		fill_color(game, C, &game->ceiling, rgb);
}

void	check_inmap(t_data *game)
{
	if (game->mapcheck.no == 1 && game->mapcheck.so == 1 && 
		game->mapcheck.we == 1 && game->mapcheck.ea == 1 &&
		game->mapcheck.f == 1 && game->mapcheck.c == 1)
		game->mapcheck.in_map = 1;
}

void	check_line(t_data *game, char *line)
{
	char	**split;

	split = ft_split(line, 32);
	if (!split)
		ft_exit(); //Aqui habria que hacer free si ya hay algo guardado.
	if (split[0][0] == '\n')
	{
		check_inmap(game);
		ft_free(split);
		return ;
	}
	if (!split[1] || (split[2] != NULL && split[2][0] != '\n'))
	{
		ft_free(split);
		ft_exit(); //Aqui habria que hacer free si ya hay algo guardado.
	}
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
		ft_exit(); //Aqui habria que hacer free si ya hay algo guardado.
	check_inmap(game);
	ft_free(split);
}



void	check_mapline(t_data * game, char *line, int count)
{
	if (game->mapcheck.in_map == 1 && line[0] == '\n')
		return ;
	if (game->mapcheck.in_map == 1 && line[0] != '\n')
	{
		printf("Count: %d\n", count);
		game->mapcheck.start_row = count;
		game->mapcheck.in_map = 2;
	}
}

void	check_textures(t_data *game)
{
	char	*line;
	int		fd;
	int		count;

	fd = open(game->mapname, O_RDONLY);
	if (fd < 0)
		ft_exit();
	count = 1;
	line = get_next_line(fd);
	while (line)
	{
		check_line(game, line);
		free(line);
		line = get_next_line(fd);
		count++;
		if (game->mapcheck.in_map == 1)
			break ;
	}
	print_game_data(game);
	while (line)
	{
		check_mapline(game, line, count);
		printf("Linea inmap %d; nº%d: %s",  game->mapcheck.in_map, count, line);
		free(line);
		line = get_next_line(fd);
		count++;
	}
	printf("Fin check\n");
	close(fd);
}

void	check_map(t_data *game)
{
	check_textures(game);
	//fill_map(game);
}