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

void	calculate_points(t_data *data, float perp_dist)
{
	if (data->texture == NO)
	{
		data->line_height = (int)(HEIGHT / perp_dist);
		data->tex_x = (int)(perp_dist * data->north.height) % data->north.height;
		data->tex_step = 1.0 * data->north.height / data->line_height;
	}
	if (data->texture == SO)
	{
		data->line_height = (int)(HEIGHT / perp_dist);
		data->tex_x = (int)(perp_dist * data->south.height) % data->south.height;
		data->tex_step = 1.0 * data->south.height / data->line_height;
	}
	if (data->texture == EA)
	{
		data->line_height = (int)(HEIGHT / perp_dist);
		data->tex_x = (int)(perp_dist * data->east.height) % data->east.height;
		data->tex_step = 1.0 * data->east.height / data->line_height;
	}
	if (data->texture == WE)
	{
		data->line_height = (int)(HEIGHT / perp_dist);
		data->tex_x = (int)(perp_dist * data->west.height) % data->west.height;
		data->tex_step = 1.0 * data->west.height / data->line_height;
	}
}

int		calculate_color(t_data *data, float tex_pos)
{
	int	tex_y;
	if (data->texture == NO)
	{
		tex_y = (int)tex_pos & (data->north.height - 1);
		return(data->north.buff[tex_y * data->north.width + data->tex_x]);
	}
	if (data->texture == SO)
	{
		tex_y = (int)tex_pos & (data->south.height - 1);
		return(data->south.buff[tex_y * data->south.width + data->tex_x]);
	}
	if (data->texture == EA)
	{
		tex_y = (int)tex_pos & (data->east.height - 1);
		return(data->east.buff[tex_y * data->east.width + data->tex_x]);
	}
	if (data->texture == WE)
	{
		tex_y = (int)tex_pos & (data->west.height - 1);
		return(data->west.buff[tex_y * data->west.width + data->tex_x]);
	}
	return (0);
}

void	draw_vertical_line(t_data *data, int x, float perp_dist)
{
	int	y;
	int	color;
	float	tex_pos;

	tex_pos = 0;
	calculate_points(data, perp_dist);
	y = (HEIGHT - data->line_height) / 2;
	if (y < 0)
		y = 0;
	while (y < (HEIGHT + data->line_height) / 2 && y < HEIGHT)
	{
		color = calculate_color(data, tex_pos);
		tex_pos += data->tex_step;
		// Escribir el píxel en la imagen
		*(int*)(data->img_data + (y * data->size_line + x * (data->bpp / 8))) = color;
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
		draw_vertical_line(data, x, perp_dist);
		x++;
	}
	mlx_put_image_to_window(data->mlx_init, data->win, data->img, 0, 0);
}
