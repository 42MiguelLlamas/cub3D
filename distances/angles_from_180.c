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

float	aux_360(t_data *data, t_angle_calc *aux, float ang)
{
	aux->y_dist = 0;
	aux->n_iter = 0;
	aux->aux_x = data->player->pos_x;
	aux->aux_y = data->player->pos_y;
	while (found_cub(data, aux->aux_x, aux->aux_y) == -1)
	{
		aux->y_dist = (((64 - data->player->pixel_x) + (64 * aux->n_iter)) / \
		sin(ang * (M_PI / 180)));
		aux->aux_dist = aux->y_dist * cos(ang * (M_PI / 180));
		aux->aux_x++;
		aux->aux_y = data->player->pos_y + ((aux->aux_dist + \
		data->player->pixel_y) / 64);
		if (found_cub(data, aux->aux_x, aux->aux_y) == -2)
			aux->y_dist = 100000000;
		aux->n_iter++;
	}
	if (aux->x_dist > aux->y_dist)
	{
		data->texture = EA;
		return (aux->y_dist);
	}
	if (aux->x_dist == 100000000)
		return (-1);
	data->texture = SO;
	return (aux->x_dist);
}

float	ang_360(t_data *data, float ang)
{
	t_angle_calc	aux;

	ang = ang - 270;
	aux.x_dist = 0.00;
	aux.n_iter = 0;
	aux.aux_x = data->player->pos_x;
	aux.aux_y = data->player->pos_y;
	while (found_cub(data, aux.aux_x, aux.aux_y) == -1)
	{
		aux.x_dist = ((64 - data->player->pixel_y + (64 * aux.n_iter)) / \
		(cos(ang * (M_PI / 180))));
		aux.aux_dist = aux.x_dist * sin(ang * (M_PI / 180));
		aux.aux_y++;
		aux.aux_x = data->player->pos_x + ((aux.aux_dist + \
		data->player->pixel_x) / 64);
		if (found_cub(data, aux.aux_x, aux.aux_y) == -2)
			aux.x_dist = 100000000;
		aux.n_iter++;
	}
	return (aux_360(data, &aux, ang));
}

float	aux_270(t_data *data, t_angle_calc *aux, float ang)
{
	aux->y_dist = 0;
	aux->n_iter = 0;
	aux->aux_x = data->player->pos_x;
	aux->aux_y = data->player->pos_y;
	while (found_cub(data, aux->aux_x, aux->aux_y) == -1)
	{
		aux->y_dist = ((data->player->pixel_x + (64 * aux->n_iter)) / \
		cos(ang * (M_PI / 180)));
		aux->aux_dist = aux->y_dist * sin(ang * (M_PI / 180));
		aux->aux_x--;
		aux->aux_y = data->player->pos_y + ((aux->aux_dist + \
		data->player->pixel_y) / 64);
		if (found_cub(data, aux->aux_x, aux->aux_y) == -2)
			aux->y_dist = 100000000;
		aux->n_iter++;
	}
	if (aux->x_dist > aux->y_dist)
	{
		data->texture = WE;
		return (aux->y_dist);
	}
	if (aux->x_dist == 100000000)
		return (-1);
	data->texture = SO;
	return (aux->x_dist);
}

float	ang_270(t_data *data, float ang)
{
	t_angle_calc	aux;

	ang = ang - 180;
	aux.x_dist = 0;
	aux.n_iter = 0;
	aux.aux_x = data->player->pos_x;
	aux.aux_y = data->player->pos_y;
	while (found_cub(data, aux.aux_x, aux.aux_y) == -1)
	{
		aux.x_dist = (((64 - data->player->pixel_y) + (64 * aux.n_iter)) / \
		(sin(ang * (M_PI / 180))));
		aux.aux_dist = aux.x_dist * cos(ang * (M_PI / 180));
		aux.aux_y++;
		aux.aux_x = data->player->pos_x - ((aux.aux_dist - \
		data->player->pixel_x) / 64);
		if (found_cub(data, aux.aux_x, aux.aux_y) == -2)
			aux.x_dist = 100000000;
		aux.n_iter++;
	}
	return (aux_270(data, &aux, ang));
}
