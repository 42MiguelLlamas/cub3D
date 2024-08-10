/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:55:53 by carlos-m          #+#    #+#             */
/*   Updated: 2024/08/01 17:55:57 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <math.h>
# include "minilibx/mlx.h"

# define WIDTH 1280.00000
# define HEIGHT 896
# define M_PI		3.14159265358979323846
# define HIPO 10

typedef enum e_hook
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}			t_hook;

typedef enum e_orient
{
	N,
	S,
	E,
	W
}			t_orient;

typedef enum e_ident
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}			t_ident;

typedef struct s_texture
{
	t_ident	id;
	char	*path;
}				t_texture;

typedef struct s_color
{
	t_ident	id;
	int		r;
	int		g;
	int		b;
}				t_color;

typedef struct s_mapcheck
{
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
	int			player_counter;
	int			in_map;
	int			start_row;
}				t_mapcheck;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	int		pixel_x;
	int		pixel_y;
	float	angle_v;
}				t_player;

typedef struct s_angle_calc
{
	float	x_dist;
	float	y_dist;
	float	aux_dist;
	int		n_iter;
	int		aux_x;
	int		aux_y;
}				t_angle_calc;

typedef struct s_data
{
	char		*mapname;
	char		**map;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_color		floor;
	t_color		ceiling;
	t_mapcheck	mapcheck;
	t_player	*player;
	int			rows;
	int			cols;
	void		*win;
	void		*mlx_init;
	void		*img;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
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
void	check_textures(char	**split, t_data *game);

void	free_exit(char **sol, int len, int fd);
void	free_game_data(t_data *game);
void	ft_exit(int yes, t_data *game);
void	ft_free(char **map);

int		found_cub(t_data *data, int x_pos, int y_pos);
float	ang_360(t_data *data, float ang);
float	ang_270(t_data *data, float ang);
float	ang_180(t_data *data, float ang);
float	ang_90(t_data *data, float ang);

void	change_vision(t_data *data, int keycode);
int		ft_move(int keycode, t_data *data);
void	draw_img(t_data *data);
float	distancia_a_bloque(t_data *data, float ang);
float	angulo_rayo(t_player *player, int x);

void	gameplay(t_data *data);

#endif