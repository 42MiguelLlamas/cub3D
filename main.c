#include "cube.h"

void	print_map(char **map)
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

int	main(int argc, char **argv)
{
	t_data	game;
	
	if (argc != 2)
		ft_exit();
	if (ft_strncmp(".cub", argv[1] + ft_strlen(argv[1]) - 4, 4) != 0)
		ft_exit();
	game.mapname = argv[1];
	check_map(&game);
	print_map(game.map);
}