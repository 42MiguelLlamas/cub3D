/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:39:29 by carlos-m          #+#    #+#             */
/*   Updated: 2024/08/10 13:39:30 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	found_cub(t_data *data, int x_pos, int y_pos)
{
	if (x_pos < 0 || y_pos < 0 || y_pos >= data->rows || x_pos >= data->cols)
		return (-2);
	if (data->map[y_pos][x_pos] == '1')
		return (1);
	return (-1);
}

void	pixel_distances(float *pix_x, float *pix_y, t_data *data, int keycode)
{
	if (keycode == 119)
	{
		*pix_x = cos(data->player->angle_v * (M_PI / 180)) * HIPO;
		*pix_y = sin(data->player->angle_v * (M_PI / 180)) * HIPO;
	}
	else if (keycode == 115)
	{
		*pix_x = -cos(data->player->angle_v * (M_PI / 180)) * HIPO;
		*pix_y = -sin(data->player->angle_v * (M_PI / 180)) * HIPO;
	}
	else if (keycode == 97)
	{
		*pix_x = -sin(data->player->angle_v * (M_PI / 180)) * HIPO;
		*pix_y = cos(data->player->angle_v * (M_PI / 180)) * HIPO;
	}
	else if (keycode == 100)
	{
		*pix_x = sin(data->player->angle_v * (M_PI / 180)) * HIPO;
		*pix_y = -cos(data->player->angle_v * (M_PI / 180)) * HIPO;
	}
	data->player->pixel_x = data->player->pixel_x + *pix_x;
	data->player->pixel_y = data->player->pixel_y - *pix_y;
}

void	aux_pixel_y(t_data *data, float pix_y)
{
	if (data->player->pixel_y < 0)
	{
		if (data->player->pos_y - 1 >= 0)
		{
			data->player->pixel_y = data->player->pixel_y - pix_y + 64;
			data->player->pos_y--;
		}
		else
			data->player->pixel_y = 1;
	}
	else if (data->player->pixel_y > 64)
	{
		if (data->player->pos_y + 1 < data->rows)
		{
			data->player->pixel_y = data->player->pixel_y - pix_y - 64;
			data->player->pos_y++;
		}
		else
			data->player->pixel_y = 63;
	}
	draw_img(data);
}

void	try_move(t_data *data, int keycode)
{
	float	pix_x;
	float	pix_y;

	pixel_distances(&pix_x, &pix_y, data, keycode);
	if (data->player->pixel_x > 64)
	{
		if (data->player->pos_x + 1 < data->cols)
		{
			data->player->pixel_x = data->player->pixel_x + pix_x - 64;
			data->player->pos_x++;
		}
		else
			data->player->pixel_x = 63;
	}
	else if (data->player->pixel_x < 0)
	{
		if (data->player->pos_x - 1 >= 0)
		{
			data->player->pixel_x = data->player->pixel_x + pix_x + 64;
			data->player->pos_x--;
		}
		else
			data->player->pixel_x = 1;
	}
	aux_pixel_y(data, pix_y);
}

int	ft_move(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window((*data).mlx_init, (*data).win);
		exit (0);
	}
	else if (keycode == 65361)
		change_vision(data, keycode);
	else if (keycode == 65363)
		change_vision(data, keycode);
	else if (keycode == 119)
		try_move(data, 119);
	else if (keycode == 115)
		try_move(data, 115);
	else if (keycode == 97)
		try_move(data, 97);
	else if (keycode == 100)
		try_move(data, 100);
	return (0);
}
