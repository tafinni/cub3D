/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:13:26 by akuzmenk          #+#    #+#             */
/*   Updated: 2024/01/15 19:00:29 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < WINDOW_WIDTH && y < WINDOW_HEIGHT && x >= 0 && y >= 0)
	{
		pixel = img->addr + (y * img->line_length + x \
		* (img->bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

void	draw_ceil_floor(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			if (i <= WINDOW_HEIGHT / 2)
			{
				my_mlx_pixel_put(data->img, j, i, data->colors->ceiling);
			}
			else
			{
				my_mlx_pixel_put(data->img, j, i, data->colors->floor);
			}
			j++;
		}
		i++;
	}
}

static void	init_ch(t_data *data)
{
	data->player->ch_x_a = data->player->x - (GRID_SIZE / 4) \
		* sin(data->player->p_angle);
	data->player->ch_y_a = data->player->y + (GRID_SIZE / 4) \
		* cos(data->player->p_angle);
	data->player->ch_x_d = data->player->x + (GRID_SIZE / 4) \
		* sin(data->player->p_angle);
	data->player->ch_y_d = data->player->y - (GRID_SIZE / 4) \
		* cos(data->player->p_angle);
	data->player->ch_x_w = data->player->x - data->player->pdx;
	data->player->ch_y_w = data->player->y - data->player->pdy;
	data->player->ch_x_s = data->player->x + data->player->pdx;
	data->player->ch_y_s = data->player->y + data->player->pdy;
}

static int	check_position_player(t_data *data)
{
	init_ch(data);
	if (data->map->map[(int)data->player->ch_y_s / GRID_SIZE] \
		[(int)data->player->ch_x_s / GRID_SIZE] == '1'
		|| data->map->map[(int)data->player->ch_y_w / GRID_SIZE] \
		[(int)data->player->ch_x_w / GRID_SIZE] == '1'
		|| data->map->map[(int)data->player->ch_y_a / GRID_SIZE] \
		[(int)data->player->ch_x_a / GRID_SIZE] == '1'
		|| data->map->map[(int)data->player->ch_y_d / GRID_SIZE] \
		[(int)data->player->ch_x_d / GRID_SIZE] == '1'
		|| data->map->map[(int)data->player->ch_y_w / GRID_SIZE] \
		[(int)data->player->ch_x_s / GRID_SIZE] == '1'
		|| data->map->map[(int)data->player->ch_y_s / GRID_SIZE] \
		[(int)data->player->ch_x_w / GRID_SIZE] == '1')
	{
		data->player->x = data->player->x_start;
		data->player->y = data->player->y_start;
	}
	return (0);
}

int	init_image(t_data *data)
{
	data->img->img_ptr = mlx_new_image(data->mlx_ptr, \
	WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->img->img_ptr == 0)
	{
		error_msg("Image not found");
		return (FAIL);
	}
	data->img->addr = mlx_get_data_addr(data->img->img_ptr, \
			&data->img->bits_per_pixel, \
			&data->img->line_length, &data->img->endian);
	draw_ceil_floor(data);
	check_position_player(data);
	start_raycaster(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->img->img_ptr, 0, 0);
	return (SUCCESS);
}
