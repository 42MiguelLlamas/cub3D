#include "../cube.h"

void	count_rows(t_data *game)
{
	char	*line;
	int		count;
	int		fd;

	fd = open(game->mapname, O_RDONLY);
	if (fd < 0)
		ft_exit();
	line = get_next_line(fd);
	game->cols = (int)ft_strlen(line);
	count = 0;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	game->rows = count;
	close(fd);
	if (game->cols < 3 || count < 3)
		ft_exit();
}

