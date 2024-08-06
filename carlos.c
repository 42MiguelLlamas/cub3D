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

#include "cube.h"

int	found_cub(t_data *data, int x_pos, int y_pos)
{
	if (x_pos < 0 || y_pos < 0 || y_pos >= data->rows || x_pos >= data->cols)
		return (-2);
	if (data->map[y_pos][x_pos] == '1')
		return (1);
	return (-1);
}

float	ang_360(t_data *data, float ang)
{
	float	x_dist;
	float	y_dist;
	float	aux_dist;
	int		n_iter;
	int		aux_x;
	int		aux_y;

	ang = ang - 270;
	x_dist = 0;
	n_iter = 0;
	aux_x = data->player->pos_x;
	aux_y = data->player->pos_y;
	while (found_cub(data, aux_x, aux_y) == -1)
	{
		x_dist = ((64 - data->player->pixel_y + (64 * n_iter)) / \
		(cos(ang * (M_PI / 180))));
		aux_dist = x_dist * sin(ang * (M_PI / 180));
		aux_y++;
		aux_x = data->player->pos_x + ((aux_dist + data->player->pixel_x) / 64);
		if (found_cub(data, aux_x, aux_y) == -2)
			x_dist = 100000000;
		n_iter++;
	}
	y_dist = 0;
	n_iter = 0;
	aux_x = data->player->pos_x;
	aux_y = data->player->pos_y;
	while (found_cub(data, aux_x, aux_y) == -1)
	{
		y_dist = (((64 - data->player->pixel_x) + (64 * n_iter)) / \
		sin(ang * (M_PI / 180)));
		aux_dist = y_dist * cos(ang * (M_PI / 180));
		aux_x++;
		aux_y = data->player->pos_y + ((aux_dist + data->player->pixel_y) / 64);
		if (found_cub(data, aux_x, aux_y) == -2)
			y_dist = 100000000;
		n_iter++;
	}
	if (x_dist > y_dist)
		return (y_dist);
	if (x_dist == 100000000)
		return (-1);
	return (x_dist);
}

float	ang_270(t_data *data, float ang)
{
	float	x_dist;
	float	y_dist;
	float	aux_dist;
	int		n_iter;
	int		aux_x;
	int		aux_y;

	ang = ang - 180;
	x_dist = 0;
	n_iter = 0;
	aux_x = data->player->pos_x;
	aux_y = data->player->pos_y;
	while (found_cub(data, aux_x, aux_y) == -1)
	{
		x_dist = (((64 - data->player->pixel_y) + (64 * n_iter)) / \
		(sin(ang * (M_PI / 180))));
		aux_dist = x_dist * cos(ang * (M_PI / 180));
		aux_y++;
		aux_x = data->player->pos_x - ((aux_dist - data->player->pixel_x) / 64);
		if (found_cub(data, aux_x, aux_y) == -2)
			x_dist = 100000000;
		n_iter++;
	}
	y_dist = 0;
	n_iter = 0;
	aux_x = data->player->pos_x;
	aux_y = data->player->pos_y;
	while (found_cub(data, aux_x, aux_y) == -1)
	{
		y_dist = ((data->player->pixel_x + (64 * n_iter)) / \
		cos(ang * (M_PI / 180)));
		aux_dist = y_dist * sin(ang * (M_PI / 180));
		aux_x--;
		aux_y = data->player->pos_y + ((aux_dist + data->player->pixel_y) / 64);
		if (found_cub(data, aux_x, aux_y) == -2)
			y_dist = 100000000;
		n_iter++;
	}
	if (x_dist > y_dist)
		return (y_dist);
	if (x_dist == 100000000)
		return (-1);
	return (x_dist);
}

float	ang_180(t_data *data, float ang)
{
	float	x_dist;
	float	y_dist;
	float	aux_dist;
	int		n_iter;
	int		aux_x;
	int		aux_y;

	ang = ang - 90;
	x_dist = 0;
	n_iter = 0;
	aux_x = data->player->pos_x;
	aux_y = data->player->pos_y;
	while (found_cub(data, aux_x, aux_y) == -1)
	{
		x_dist = ((data->player->pixel_y + (64 * n_iter)) / \
		(cos(ang * (M_PI / 180))));
		aux_dist = x_dist * sin(ang * (M_PI / 180));
		aux_y--;
		aux_x = data->player->pos_x - ((aux_dist - data->player->pixel_x) / 64);
		if (found_cub(data, aux_x, aux_y) == -2)
			x_dist = 100000000;
		n_iter++;
	}
	y_dist = 0;
	n_iter = 0;
	aux_x = data->player->pos_x;
	aux_y = data->player->pos_y;
	while (found_cub(data, aux_x, aux_y) == -1)
	{
		y_dist = (data->player->pixel_x + (64 * n_iter) / \
		(sin(ang * (M_PI / 180))));
		aux_dist = y_dist * cos(ang * (M_PI / 180));
		aux_x--;
		aux_y = data->player->pos_y - ((aux_dist - data->player->pixel_y) / 64);
		if (found_cub(data, aux_x, aux_y) == -2)
			y_dist = 100000000;
		n_iter++;
	}
	if (x_dist > y_dist)
		return (y_dist);
	if (x_dist == 100000000)
		return (-1);
	return (x_dist);
}

float	ang_90(t_data *data, float ang)
{
	float	x_dist;
	float	y_dist;
	float	aux_dist;
	int		n_iter;
	int		aux_x;
	int		aux_y;

	x_dist = 0;
	n_iter = 0;
	aux_x = data->player->pos_x;
	aux_y = data->player->pos_y;
	while (found_cub(data, aux_x, aux_y) == -1)
	{
		x_dist = ((data->player->pixel_y + (64 * n_iter)) / \
		(sin(ang * (M_PI / 180))));
		aux_dist = x_dist * cos(ang * (M_PI / 180));
		aux_y--;
		aux_x = data->player->pos_x + ((aux_dist + data->player->pixel_x) / 64);
		if (found_cub(data, aux_x, aux_y) == -2)
			x_dist = 100000000;
		n_iter++;
	}
	y_dist = 0;
	n_iter = 0;
	aux_x = data->player->pos_x;
	aux_y = data->player->pos_y;
	while (found_cub(data, aux_x, aux_y) == -1)
	{
		y_dist = ((64 - data->player->pixel_x + (64 * n_iter)) / \
		(cos(ang * (M_PI / 180))));
		aux_dist = y_dist * sin(ang * (M_PI / 180));
		aux_x++;
		aux_y = data->player->pos_y - ((aux_dist - data->player->pixel_y) / 64);
		if (found_cub(data, aux_x, aux_y) == -2)
			y_dist = 100000000;
		n_iter++;
	}
	if (x_dist > y_dist)
		return (y_dist);
	if (x_dist == 100000000)
		return (-1);
	return (x_dist);
}

float	distancia_a_bloque(t_data *data, float ang)
{
	if (ang >= 0 && ang < 90)
		return (ang_90(data, ang));
	else if (ang >= 90 && ang < 180)
		return (ang_180(data, ang));
	if (ang >= 180 && ang < 270)
		return (ang_270(data, ang));
	else if (ang >= 270 && ang < 360)
		return (ang_360(data, ang));
	return (0);
}

float	angulo_rayo(t_player *player, int x)
{
	float	result;

	result = player->angle_v + 45;
	result = result - (x * (90 / WIDTH));
	if (result >= 360)
		return (result - 360);
	if (result < 0)
		return (result + 360);
	return (result);
}

int	destroy(t_data *data)
{
	mlx_destroy_window((*data).mlx_init, (*data).win);
	exit(0);
}

void put_pixel_to_image(t_data *data, int x, int y, int color) {
    int pixel;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        pixel = (y * data->size_line) + (x * (data->bpp / 8));
        data->img_data[pixel] = color;
        data->img_data[pixel + 1] = color >> 8;
        data->img_data[pixel + 2] = color >> 16;
    }
}

void draw_vertical_line(t_data *data, int x, int start, int end, int color) {
    int y;

    y = start;
    while (y <= end) {
        put_pixel_to_image(data, x, y, color);
        y++;
    }
}

void	draw_img(t_data *data)
{
	float ang_pocilga;
    float dist_bloque;
    int x;
    int wall_height;
    int start;
    int end;
    float perpendicular_dist;
    float correction_angle;

	data->img = mlx_new_image(data->mlx_init, WIDTH, HEIGHT);
    if (!data->img) {
        fprintf(stderr, "Error creating image\n");
        return;
    }

    data->img_data = mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endian);

    x = 0;
    while (x < WIDTH) {
        ang_pocilga = angulo_rayo(data->player, x);
        dist_bloque = distancia_a_bloque(data, ang_pocilga) / 64;

        // Corregir distorsión de perspectiva
        correction_angle = data->player->angle_v - ang_pocilga;
        perpendicular_dist = dist_bloque * cos(correction_angle * (M_PI / 180));

        // Calcular la altura de la pared a dibujar
        wall_height = (int)(HEIGHT / perpendicular_dist);

        // Calcular el punto de inicio y fin de la línea vertical
        start = (HEIGHT / 2) - (wall_height / 2);
        end = start + wall_height;

        // Dibujar la pared
        draw_vertical_line(data, x, start, end, 0xABFCFA);

        x++;
    }
    mlx_put_image_to_window(data->mlx_init, data->win, data->img, 0, 0);
}

/*void	try_move(t_data *data, int keycode)
{
	if ()
	if (keycode == 119)
	{
	}
	if (keycode == 115)
	{
	}
	if (keycode == 97)
	{
	}
	if (keycode == 100)
	{
	}
}*/

void	change_vision(t_data *data, int keycode)
{
	if (keycode == 65361) //flecha izq, cambiar vision
		data->player->angle_v = data->player->angle_v + 5;
	if (keycode == 65363) //flecha dcha, cambiar vision
		data->player->angle_v = data->player->angle_v - 5;
	draw_img(data);
}

int	ft_move(int keycode, t_data *data)
{
	printf("%d\n", keycode);
	if (keycode == 65307)
	{
		mlx_destroy_window((*data).mlx_init, (*data).win);
		exit (0);
	}
	else if (keycode == 65361) //flecha izq, cambiar vision
		change_vision(data, keycode);
	else if (keycode == 65363) //flecha dcha, cambiar vision
		change_vision(data, keycode);
	/*else if (keycode == 119) //W
		try_move(data, 119);
	else if (keycode == 115)//S
		try_move(data, 115);
	else if (keycode == 97)//A
		try_move(data, 97);
	else if (keycode == 100)//D
		try_move(data, 100);*/
	return (0);
}

void gameplay(t_data *data)
{
    float ang_pocilga;
    float dist_bloque;
    int x;
    int wall_height;
    int start;
    int end;
    float perpendicular_dist;
    float correction_angle;

    data->mlx_init = mlx_init();
    if (!data->mlx_init) {
        fprintf(stderr, "Error initializing MLX\n");
        return;
    }

    data->win = mlx_new_window(data->mlx_init, WIDTH, HEIGHT, "Cub3D");
    if (!data->win) {
        fprintf(stderr, "Error creating window\n");
        return;
    }
    data->img = mlx_new_image(data->mlx_init, WIDTH, HEIGHT);
    if (!data->img) {
        fprintf(stderr, "Error creating image\n");
        return;
    }

    data->img_data = mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endian);

    x = 0;
    while (x < WIDTH) {
        ang_pocilga = angulo_rayo(data->player, x);
        dist_bloque = distancia_a_bloque(data, ang_pocilga) / 64;

        // Corregir distorsión de perspectiva
        correction_angle = data->player->angle_v - ang_pocilga;
        perpendicular_dist = dist_bloque * cos(correction_angle * (M_PI / 180));

        // Calcular la altura de la pared a dibujar
        wall_height = (int)(HEIGHT / perpendicular_dist);

        // Calcular el punto de inicio y fin de la línea vertical
        start = (HEIGHT / 2) - (wall_height / 2);
        end = start + wall_height;

        // Dibujar la pared
        draw_vertical_line(data, x, start, end, 0xABFCFA);

        x++;
    }

    mlx_put_image_to_window(data->mlx_init, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, ft_move, data);
    mlx_hook(data->win, ON_DESTROY, 0, destroy, data);
    mlx_loop(data->mlx_init);
}
