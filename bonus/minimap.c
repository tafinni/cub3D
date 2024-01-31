/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:44:02 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/04 20:34:24 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_start(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->x_len - 1)
	{
		y = 0;
		while (y < map->y_len && map->map[y][x] == 'X')
			y++;
		if (y == map->y_len)
			x++;
		else if (x > 0)
			return (x);
		else if (x == 0)
			break ;
	}
	return (0);
}

void	init_minimap(t_data *data)
{
	data->minimap = malloc(sizeof(t_minimap));
	if (!data->minimap)
	{
		error_msg("Malloc fail");
		exit_game(data, FAIL, 1);
	}
	data->minimap->image = NULL;
	data->minimap->block_size = 10;
}

void	minimap_area(t_data *data)
{
	static int	start;

	if (start == 0)
	{
		start = 1;
		init_minimap(data);
	}
	if (data->minimap->image != NULL)
		mlx_destroy_image(data->mlx_ptr, data->minimap->image);
	data->minimap->image = mlx_xpm_file_to_image(data->mlx_ptr, \
	"./bonus/bonus_textures/minimap_base.xpm", \
	&data->minimap->size, &data->minimap->size);
	if (data->minimap->image == NULL)
	{
		error_msg("Texture not found");
		exit_game(data, FAIL, 1);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->minimap->image, 0, 0);
}

int	minimap(t_data *data)
{
	float	y;
	int		y_rounds;

	minimap_area(data);
	y_rounds = 0;
	y = (data->player->y / GRID_SIZE) - 6;
	while (y < 0)
	{
		y_rounds++;
		y++;
	}
	while ((y < (data->player->y / GRID_SIZE) + 6) && \
	(y < data->map->y_len))
	{
		place_correct_image(data, y, y_rounds);
		y_rounds++;
		y++;
	}
	img_to_place('P', 8, 6, data);
	return (SUCCESS);
}
