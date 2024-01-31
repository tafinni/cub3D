/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:40:30 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/04 20:34:07 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_img(t_data *data, int x, int y, char *path)
{
	if (data->minimap->image != NULL)
		mlx_destroy_image(data->mlx_ptr, data->minimap->image);
	data->minimap->image = NULL;
	data->minimap->image = mlx_xpm_file_to_image(data->mlx_ptr, path, \
	&data->minimap->block_size, &data->minimap->block_size);
	if (data->minimap->image == NULL)
	{
		error_msg("Can't find texture");
		exit_game(data, FAIL, 1);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->minimap->image, x * data->minimap->block_size, \
	y * data->minimap->block_size);
}

void	img_to_place(char c, int x, int y, t_data *data)
{
	if (x < 0 || y < 0)
		return ;
	if (c == '1')
		set_img(data, x, y, "./bonus/bonus_textures/minimap_grey_wall.xpm");
	else if (c == 'P')
		set_img(data, x, y, "./bonus/bonus_textures/minimap_player.xpm");
}

void	place_correct_image(t_data *data, int y, int y_rounds)
{
	int		x_rounds;
	float	x;

	x_rounds = 0;
	x = (data->player->x / GRID_SIZE) - 8;
	while ((x < (data->player->x / GRID_SIZE) + 8))
	{
		if (x < data->map->x_len)
		{
			if (x >= 0 && y >= 0)
				img_to_place(data->map->map[y][(int)x], \
				x_rounds, y_rounds, data);
			x_rounds++;
		}
		x++;
	}
}
