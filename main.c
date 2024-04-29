#include "cube.h"

void	leaks()
{
	system("leaks -q so_long");
}

int	main(int argc, char **argv)
{
	t_data	game;
	
	if (argc != 2)
		ft_exit();
	if (strncmp(".cub", argv[1] + ft_strlen(argv[1]) - 4, 4) != 0)
		ft_exit();
	game.mapname = argv[1];
	check_map(&game);
}