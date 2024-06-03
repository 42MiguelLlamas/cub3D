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
	int		r;
	int		g;
	int		b;
}				t_color;

typedef struct s_mapcheck{
	int			no;
	int			so;
	int 		we;
	int			ea;
	int			f;
	int			c;
	int			player_counter;
	int 		in_map;
	int			start_row;
}				t_mapcheck;

typedef struct s_data{
	char		*mapname;
	char		**map;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_color		floor;
	t_color		ceiling;
	t_mapcheck	mapcheck;
	int			rows;
	int			cols;
}				t_data;


void	init_color(t_color *color, t_ident ident);
void	init_texture(t_texture *texture, t_ident ident);
void	init_mapcheck(t_mapcheck *mc);
void	init_data(t_data *game);

void	fill_map(t_data *game);

void	check_map(t_data *game);
void	fill_texture(char *path, t_ident ident, t_data	*game);
void	fill_color(t_data *game, t_ident ident, t_color	*color, char *rgb);
void	check_color(char *rgb, t_ident ident, t_data *game);
void	check_inmap(t_data *game);

void	free_exit(char **sol, int len, int fd);
void	free_game_data(t_data *game);
void	ft_exit(int yes, t_data *game);
void	ft_free(char **map);

#endif