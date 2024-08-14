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


void	calculate_points(t_data *data, t_img_calc	*img_c)
{
	if (data->texture == NO)
	{
		img_c->line_height = (int)(HEIGHT / img_c->perp_dist);
		img_c->tex_step = 1.0 * data->north.height / img_c->line_height;
		
	}
	if (data->texture == SO)
	{
		img_c->line_height = (int)(HEIGHT / img_c->perp_dist);
		img_c->tex_step = 1.0 * data->south.height / img_c->line_height;
	}
	if (data->texture == EA)
	{
		img_c->line_height = (int)(HEIGHT / img_c->perp_dist);
		img_c->tex_step = 1.0 * data->east.height / img_c->line_height;
	}
	if (data->texture == WE)
	{
		img_c->line_height = (int)(HEIGHT / img_c->perp_dist);
		img_c->tex_step = 1.0 * data->west.height / img_c->line_height;
	}
}

void	calculate_color(t_data *data, float tex_pos, t_img_calc	*img_c)
{
	int	tex_y;
	if (data->texture == NO)
	{
		tex_y = (int)tex_pos % data->north.height;
		img_c->color = data->north.buff[tex_y * data->north.width + img_c->tex_x];
	}
	if (data->texture == SO)
	{
		tex_y = (int)tex_pos % data->south.height;
		img_c->color = data->south.buff[tex_y * data->south.width + img_c->tex_x];
		//printf("Tex_y: %i, Tex_x: %d, Text width:%d, Tex Pos: \n", tex_y ,img_c->tex_x,data->south.width );
	}
	if (data->texture == EA)
	{
		tex_y = (int)tex_pos % data->east.height;
		img_c->color = data->east.buff[tex_y * data->east.width + img_c->tex_x];
	}
	if (data->texture == WE)
	{
		tex_y = (int)tex_pos % data->west.height;
		img_c->color = data->west.buff[tex_y * data->west.width + img_c->tex_x];
	}
}

void	paint_color(t_img_calc	*img_c, t_color color, int x, int y)
{
	int pixel_index;
	int color_value;

	pixel_index = (y * img_c->size_line) + (x * (img_c->bpp / 8));
	color_value = (color.r * 65536) + (color.g * 256) + color.b;
	*(int*)(img_c->img_data + pixel_index) = color_value;
}

void	draw_vertical_line(t_data *data, int x, t_img_calc	*img_c)
{
	int	y;
	int	a;
	float	tex_pos;

	tex_pos = 0;
	a = 0;
	calculate_points(data, img_c);
	//printf("Col: %i, Line height:%i, Tex:%d, Step:%f, Texture: %i\n", x, img_c->line_height, img_c->tex_x, img_c->tex_step, data->texture);
	y = (HEIGHT - img_c->line_height) / 2;
	if (y < 0)
		y = 0;
	while (++a < y)
		paint_color(img_c, data->ceiling, x, a);
	while (y < (HEIGHT + img_c->line_height) / 2 && y < HEIGHT)
	{
		calculate_color(data, tex_pos, img_c);
		tex_pos += img_c->tex_step;
		*(int*)(img_c->img_data + (y * img_c->size_line + x * (img_c->bpp / 8))) = img_c->color;
		y++;
	}
	while (y < HEIGHT && y > (HEIGHT / 2))
		paint_color(img_c, data->floor, x, y++);
}

void	draw_img(t_data *data)
{
	t_img_calc	img_calc;
	int		x;

	img_calc.img = mlx_new_image(data->mlx_init, WIDTH, HEIGHT);
	if (!img_calc.img)
	{
		fprintf(stderr, "Error creating image\n");
		return ;
	}
	img_calc.img_data = mlx_get_data_addr(img_calc.img, &img_calc.bpp, \
	&img_calc.size_line, &img_calc.endian);
	x = 0;
	while (x < WIDTH)
	{
		img_calc.ang_cum = angulo_rayo(data->player, x);
		img_calc.dist_bloque = distancia_a_bloque(data, &img_calc) / 64;
		img_calc.correction_angle = data->player->angle_v - img_calc.ang_cum;
		img_calc.perp_dist = img_calc.dist_bloque * (float)cos(img_calc.correction_angle * (M_PI / 180.0));
		//printf("Column x=%d: ang_cum=%f, dist_bloque=%f, correction_angle=%f, perp_dist=%f, Tex_x: %f\n",
		//		x, img_calc.ang_cum, img_calc.dist_bloque, img_calc.correction_angle, img_calc.perp_dist);
		draw_vertical_line(data, x, &img_calc);
		x++;
	}
	mlx_put_image_to_window(data->mlx_init, data->win, img_calc.img, 0, 0);
}
