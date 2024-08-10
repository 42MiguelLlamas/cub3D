/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_imgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:13:14 by carlos-m          #+#    #+#             */
/*   Updated: 2024/08/10 17:13:15 by carlos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	create_imgaes(t_data *data)
{
	data->north.img_ptr = mlx_xpm_file_to_image(data->mlx_init, \
	data->north.path, &data->north.width, &data->north.height);
	data->south.img_ptr = mlx_xpm_file_to_image(data->mlx_init, \
	data->south.path, &data->south.width, &data->south.height);
	data->east.img_ptr = mlx_xpm_file_to_image(data->mlx_init, \
	data->east.path, &data->east.width, &data->east.height);
	data->west.img_ptr = mlx_xpm_file_to_image(data->mlx_init, \
	data->west.path, &data->west.width, &data->west.height);
	data->north.data = (int *)mlx_get_data_addr(data->north.img_ptr, \
	&data->north.bpp, &data->north.size_line, &data->north.endian);
	data->south.data = (int *)mlx_get_data_addr(data->south.img_ptr, \
	&data->south.bpp, &data->south.size_line, &data->south.endian);
	data->east.data = (int *)mlx_get_data_addr(data->east.img_ptr, \
	&data->east.bpp, &data->east.size_line, &data->east.endian);
	data->west.data = (int *)mlx_get_data_addr(data->west.img_ptr, \
	&data->west.bpp, &data->west.size_line, &data->west.endian);
}

void	check_imgs(t_data *data)
{
	int	i;

	i = open(data->north.path, O_RDONLY);
	if (i < 0 || ft_strncmp(".xpm", data->north.path + \
		ft_strlen(data->north.path) - 4, 4) != 0)
		ft_exit(0, data);
	close(i);
	i = open(data->south.path, O_RDONLY);
	if (i < 0 || ft_strncmp(".xpm", data->south.path + \
		ft_strlen(data->south.path) - 4, 4) != 0)
		ft_exit(0, data);
	close(i);
	i = open(data->east.path, O_RDONLY);
	if (i < 0 || ft_strncmp(".xpm", data->east.path + \
		ft_strlen(data->east.path) - 4, 4) != 0)
		ft_exit(0, data);
	close(i);
	i = open(data->west.path, O_RDONLY);
	if (i < 0 || ft_strncmp(".xpm", data->west.path + \
		ft_strlen(data->west.path) - 4, 4) != 0)
		ft_exit(0, data);
	close(i);
	create_imgaes(data);
}
