/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:25:20 by carlos-m          #+#    #+#             */
/*   Updated: 2024/08/10 12:25:22 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	calc_text_180_to_360(t_data *data, t_angle_calc *aux, \
t_img_calc *img_c, t_ident id)
{
	data->texture = id;
	if (img_c->ang_cum >= 180 && img_c->ang_cum < 270 && id == WE)
		img_c->tex_x = fmodf(-1.0f * (sin(img_c->ang_cum * (M_PI / 180.0f)) * \
		aux->y_dist) + (float)data->player->pixel_y + \
		(float)(data->player->pos_y * 64), 64.0f) * data->west.width / 64;
	if (img_c->ang_cum >= 180 && img_c->ang_cum < 270 && id == SO)
		img_c->tex_x = fmodf((sin((img_c->ang_cum - 270) * (M_PI / 180.0f)) * \
		aux->x_dist) + (float)data->player->pixel_x + \
		(float)(data->player->pos_x * 64), 64.0f) * data->south.width / 64;
	if (img_c->ang_cum >= 270 && img_c->ang_cum < 360 && id == EA)
		img_c->tex_x = fmodf(-1.0f * (sin(img_c->ang_cum * (M_PI / 180.0f)) * \
		aux->y_dist) + (float)data->player->pixel_y + \
		(float)(data->player->pos_y * 64), 64.0f) * data->east.width / 64;
	if (img_c->ang_cum >= 270 && img_c->ang_cum < 360 && id == SO)
		img_c->tex_x = fmodf((sin((img_c->ang_cum - 270) * (M_PI / 180.0f)) * \
		aux->x_dist) + (float)data->player->pixel_x + \
		(float)(data->player->pos_x * 64), 64.0f) * data->south.width / 64;
}

float	aux_360(t_data *data, t_angle_calc *aux, t_img_calc *img_c)
{
	aux->n_iter = 0;
	aux->aux_x = data->player->pos_x;
	aux->aux_y = data->player->pos_y;
	while (found_cub(data, aux->aux_x, aux->aux_y) == -1)
	{
		aux->y_dist = (((64 - data->player->pixel_x) + (64 * aux->n_iter)) / \
		sin(img_c->ang_cum * (M_PI / 180)));
		aux->aux_dist = aux->y_dist * cos(img_c->ang_cum * (M_PI / 180));
		aux->aux_x++;
		aux->aux_y = data->player->pos_y + ((aux->aux_dist + \
		data->player->pixel_y) / 64);
		if (found_cub(data, aux->aux_x, aux->aux_y) == -2)
			aux->y_dist = 100000000;
		aux->n_iter++;
	}
	img_c->ang_cum += 270;
	if (aux->x_dist > aux->y_dist)
	{
		calc_text_180_to_360(data, aux, img_c, EA);
		return (aux->y_dist);
	}
	if (aux->x_dist == 100000000)
		return (-1);
	calc_text_180_to_360(data, aux, img_c, SO);
	return (aux->x_dist);
}

float	ang_360(t_data *data, t_img_calc *img_c)
{
	t_angle_calc	aux;

	img_c->ang_cum = img_c->ang_cum - 270;
	aux.x_dist = 0.00;
	aux.n_iter = 0;
	aux.aux_x = data->player->pos_x;
	aux.aux_y = data->player->pos_y;
	while (found_cub(data, aux.aux_x, aux.aux_y) == -1)
	{
		aux.x_dist = ((64 - data->player->pixel_y + (64 * aux.n_iter)) / \
		(cos(img_c->ang_cum * (M_PI / 180))));
		aux.aux_dist = aux.x_dist * sin(img_c->ang_cum * (M_PI / 180));
		aux.aux_y++;
		aux.aux_x = data->player->pos_x + ((aux.aux_dist + \
		data->player->pixel_x) / 64);
		if (found_cub(data, aux.aux_x, aux.aux_y) == -2)
			aux.x_dist = 100000000;
		aux.n_iter++;
	}
	aux.y_dist = 0;
	return (aux_360(data, &aux, img_c));
}

float	aux_270(t_data *data, t_angle_calc *aux, t_img_calc *img_c)
{
	aux->n_iter = 0;
	aux->aux_x = data->player->pos_x;
	aux->aux_y = data->player->pos_y;
	while (found_cub(data, aux->aux_x, aux->aux_y) == -1)
	{
		aux->y_dist = ((data->player->pixel_x + (64 * aux->n_iter)) / \
		cos(img_c->ang_cum * (M_PI / 180)));
		aux->aux_dist = aux->y_dist * sin(img_c->ang_cum * (M_PI / 180));
		aux->aux_x--;
		aux->aux_y = data->player->pos_y + ((aux->aux_dist + \
		data->player->pixel_y) / 64);
		if (found_cub(data, aux->aux_x, aux->aux_y) == -2)
			aux->y_dist = 100000000;
		aux->n_iter++;
	}
	img_c->ang_cum += 180;
	if (aux->x_dist > aux->y_dist)
	{
		calc_text_180_to_360(data, aux, img_c, WE);
		return (aux->y_dist);
	}
	if (aux->x_dist == 100000000)
		return (-1);
	calc_text_180_to_360(data, aux, img_c, SO);
	return (aux->x_dist);
}

float	ang_270(t_data *data, t_img_calc *img_c)
{
	t_angle_calc	aux;

	img_c->ang_cum = img_c->ang_cum - 180;
	aux.x_dist = 0;
	aux.n_iter = 0;
	aux.aux_x = data->player->pos_x;
	aux.aux_y = data->player->pos_y;
	while (found_cub(data, aux.aux_x, aux.aux_y) == -1)
	{
		aux.x_dist = (((64 - data->player->pixel_y) + (64 * aux.n_iter)) / \
		(sin(img_c->ang_cum * (M_PI / 180))));
		aux.aux_dist = aux.x_dist * cos(img_c->ang_cum * (M_PI / 180));
		aux.aux_y++;
		aux.aux_x = data->player->pos_x - ((aux.aux_dist - \
		data->player->pixel_x) / 64);
		if (found_cub(data, aux.aux_x, aux.aux_y) == -2)
			aux.x_dist = 100000000;
		aux.n_iter++;
	}
	aux.y_dist = 0;
	return (aux_270(data, &aux, img_c));
}
