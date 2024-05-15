#include "../cube.h"

void	count_rows(t_data *game)
{
	char	*line;
	int		fd;
	int		row_aux;

	row_aux = game->mapcheck->start_row;
	fd = open(game->mapname, O_RDONLY);
	if (fd < 0)
		ft_exit();
	line = get_next_line(fd);
	game->cols = (int)ft_strlen(line);
	game->rows++;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (row_aux <= 0)
		{
			if ((int)ft_strlen(line) > game->cols)
				game->cols = (int)ft_strlen(line);
			game->rows++;
		}
		row_aux--;
	}
	close(fd);
}

