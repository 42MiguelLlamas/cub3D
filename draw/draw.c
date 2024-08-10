/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:55:07 by carlos-m          #+#    #+#             */
/*   Updated: 2024/08/10 13:55:08 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	put_pixel_to_image(t_data *data, int x, int y, int color)
{
	int	pixel;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel = (y * data->size_line) + (x * (data->bpp / 8));
		data->img_data[pixel] = color;
		data->img_data[pixel + 1] = color >> 8;
		data->img_data[pixel + 2] = color >> 16;
	}
}

void	draw_vertical_line(t_data *data, int x, int color, float perp_dist)
{
	int	y;
	int	start;
	int	wall_height;
	int	end;

	wall_height = (int)(HEIGHT / perp_dist);
	start = (HEIGHT / 2) - (wall_height / 2);
	end = start + wall_height;
	y = start;
	while (y <= end)
	{
		put_pixel_to_image(data, x, y, color);
		y++;
	}
}

void	draw_img(t_data *data)
{
	float	ang_pocilga;
	float	dist_bloque;
	int		x;
	float	perp_dist;
	float	correction_angle;

	data->img = mlx_new_image(data->mlx_init, WIDTH, HEIGHT);
	if (!data->img)
	{
		fprintf(stderr, "Error creating image\n");
		return ;
	}
	data->img_data = mlx_get_data_addr(data->img, &data->bpp, \
	&data->size_line, &data->endian);
	x = 0;
	while (x < WIDTH)
	{
		ang_pocilga = angulo_rayo(data->player, x);
		dist_bloque = distancia_a_bloque(data, ang_pocilga) / 64;
		correction_angle = data->player->angle_v - ang_pocilga;
		perp_dist = dist_bloque * cos(correction_angle * (M_PI / 180));
		draw_vertical_line(data, x, 0xABFCFA, perp_dist);
		x++;
	}
	mlx_put_image_to_window(data->mlx_init, data->win, data->img, 0, 0);
}
