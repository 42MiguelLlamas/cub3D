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

void	check_map(t_data *game)
{
	fill_map(game);
}