#include "cube.h"

void	ft_exit(void)
{
	write (1, "Error\n", 6);
	exit(0);
}

void	ft_free(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}