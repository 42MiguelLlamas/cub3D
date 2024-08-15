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

void	draw_vertical_line(t_data *data, int x, t_img_calc	*img_c)
{
	float	tex_pos;
	int		y;
	int		a;

	tex_pos = 0;
	a = 0;
	calculate_points(data, img_c);
	y = (HEIGHT - img_c->line_height) / 2;
	if (y < 0)
		y = 0;
	while (++a < y)
		paint_color(img_c, data->ceiling, x, a);
	while (y < (HEIGHT + img_c->line_height) / 2 && y < HEIGHT)
	{
		calculate_color(data, tex_pos, img_c);
		tex_pos += img_c->tex_step;
		*(int*)(img_c->img_data + (y * img_c->size_line + x * \
		(img_c->bpp / 8))) = img_c->color;
		y++;
	}
	while (y < HEIGHT && y > (HEIGHT / 2))
		paint_color(img_c, data->floor, x, y++);
}

void	draw_horizon(int x, t_data *data, t_img_calc *img_c)
{
	int	y;

	y = 0;
	while (y++ < HEIGHT / 2)
		paint_color(img_c, data->ceiling, x, y);
	while (y < HEIGHT && y > HEIGHT / 2)
		paint_color(img_c, data->floor, x, y++);
}

void	draw_img(t_data *data)
{
	t_img_calc	img_c;
	int			x;

	img_c.img = mlx_new_image(data->mlx_init, WIDTH, HEIGHT);
	if (!img_c.img)
	{
		fprintf(stderr, "Error creating image\n");
		return ;
	}
	img_c.img_data = mlx_get_data_addr(img_c.img, &img_c.bpp, \
	&img_c.size_line, &img_c.endian);
	x = 0;
	while (x++ < WIDTH)
	{
		img_c.ang_cum = angulo_rayo(data->player, x);
		img_c.dist_bloque = distancia_a_bloque(data, &img_c) / 64;
		img_c.correction_angle = data->player->angle_v - img_c.ang_cum;
		img_c.perp_dist = img_c.dist_bloque * \
		(float)cos(img_c.correction_angle * (M_PI / 180.0));
		if (img_c.dist_bloque < 0)
			draw_horizon(x, data, &img_c);
		else
			draw_vertical_line(data, x, &img_c);
	}
	mlx_put_image_to_window(data->mlx_init, data->win, img_c.img, 0, 0);
}
