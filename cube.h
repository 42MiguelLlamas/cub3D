#ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "gnl/get_next_line.h"
//# include "libft/libft.h"
//# include "ft_printf/ft_printf.h"
# include <math.h>
//# include <mlx.h>

typedef enum e_orient{
	N,
	S,
	E,
	W
}			t_orient;

typedef struct s_data{
	char		*mapname;
	int			playercount;
	char		**map;
	int			playerx;
	int			playery;
	t_orient	orientation;
	int			in_map;

	


}				t_data;

void	ft_free(char **map);
void	ft_exit(void);

void	check_map(t_data *game);
void	fill_map(t_data *game);
void	count_rows(t_data *game);
#endif