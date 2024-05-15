#ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
//# include "ft_printf/ft_printf.h"
# include <math.h>
//# include <mlx.h>

typedef enum e_orient{
	N,
	S,
	E,
	W
}			t_orient;

typedef enum e_ident{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}			t_ident;

typedef struct s_texture{
	t_ident	id;
	char	*path;
}				t_texture;

typedef struct s_color{
	t_ident	id;
	int		R;
	int		G;
	int		B;
}				t_color;

typedef struct s_data{
	char		*mapname;
	char		**map;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_color		floor;
	t_color		ceiling;
	int			rows;
	int			cols;
}				t_data;

void	ft_free(char **map);
void	ft_exit(void);

void	check_map(t_data *game);
void	fill_map(t_data *game);
void	count_rows(t_data *game);
#endif