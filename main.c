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



int	main(int argc, char **argv)
{
	t_data	game;
	
	if (argc != 2)
		ft_exit(0, &game);
	if (ft_strncmp(".cub", argv[1] + ft_strlen(argv[1]) - 4, 4) != 0)
		ft_exit(0, &game);
	init_data(&game);
	game.mapname = ft_strdup(argv[1]);
	check_map(&game);
	printf("Chequeado Mapa.\n");
	fill_map(&game);
	print_amap(game.map);
	free_game_data(&game);
}