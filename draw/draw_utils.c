/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:20:04 by carlos-m          #+#    #+#             */
/*   Updated: 2024/08/15 17:20:06 by carlos-m         ###   ########.fr       */
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
		img_c->color = data->north.buff[tex_y * data->north.width \
		+ img_c->tex_x];
	}
	if (data->texture == SO)
	{
		tex_y = (int)tex_pos % data->south.height;
		img_c->color = data->south.buff[tex_y * data->south.width \
		+ img_c->tex_x];
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
	int	pixel_index;
	int	color_value;

	pixel_index = (y * img_c->size_line) + (x * (img_c->bpp / 8));
	color_value = (color.r * 65536) + (color.g * 256) + color.b;
	*(int *)(img_c->img_data + pixel_index) = color_value;
}
