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


int	main(int argc, char **argv)
{
	t_data	game;
	
	if (argc != 2)
		ft_exit();
	if (ft_strncmp(".cub", argv[1] + ft_strlen(argv[1]) - 4, 4) != 0)
		ft_exit();
	init_data(&game);
	game.mapname = ft_strdup(argv[1]);
	printf("Data iniciado\n");
	check_map(&game);
	printf("Fin\n");
	free_game_data(&game);
	//print_amap(game.map);
}