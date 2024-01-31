/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:57:10 by akuzmenk          #+#    #+#             */
/*   Updated: 2024/01/15 19:15:29 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	move_left(t_data *data)
{
	float	x;
	float	y;
	float	new_x;
	float	new_y;

	new_x = data->player->x - (GRID_SIZE / 7) * sin(data->player->p_angle);
	new_y = data->player->y + (GRID_SIZE / 7) * cos(data->player->p_angle);
	x = new_x - (GRID_SIZE / 4) * sin(data->player->p_angle);
	y = new_y + (GRID_SIZE / 4) * cos(data->player->p_angle);
	if (data->map->map[(int)y / GRID_SIZE][(int)x / GRID_SIZE] == '1')
		return (SUCCESS);
	data->player->x = new_x;
	data->player->y = new_y;
	return (SUCCESS);
}

int	move_right(t_data *data)
{
	float	x;
	float	y;
	float	new_x;
	float	new_y;

	new_x = data->player->x + (GRID_SIZE / 7) * sin(data->player->p_angle);
	new_y = data->player->y - (GRID_SIZE / 7) * cos(data->player->p_angle);
	x = new_x + (GRID_SIZE / 4) * sin(data->player->p_angle);
	y = new_y - (GRID_SIZE / 4) * cos(data->player->p_angle);
	if (data->map->map[(int)y / GRID_SIZE][(int)x / GRID_SIZE] == '1')
		return (SUCCESS);
	data->player->x = new_x;
	data->player->y = new_y;
	return (SUCCESS);
}

int	move_forward(t_data *data)
{
	float	x;
	float	y;

	data->player->x -= data->player->pdx / PLAYER_SPEED;
	data->player->y -= data->player->pdy / PLAYER_SPEED;
	x = data->player->x - data->player->pdx;
	y = data->player->y - data->player->pdy;
	if (data->map->map[(int)y / GRID_SIZE][(int)x / GRID_SIZE] == '1'
	|| data->rays->dis_fin < 1.0)
	{
		data->player->x = data->player->x_start;
		data->player->y = data->player->y_start;
	}
	return (SUCCESS);
}

int	move_backward(t_data *data)
{
	float	x;
	float	y;

	data->player->x += data->player->pdx / PLAYER_SPEED;
	data->player->y += data->player->pdy / PLAYER_SPEED;
	x = data->player->x + data->player->pdx;
	y = data->player->y + data->player->pdy;
	if (data->map->map[(int)y / GRID_SIZE][(int)x / GRID_SIZE] == '1')
	{
		data->player->x = data->player->x_start;
		data->player->y = data->player->y_start;
	}
	return (SUCCESS);
}
