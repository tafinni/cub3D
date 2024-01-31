/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:23:02 by akuzmenk          #+#    #+#             */
/*   Updated: 2024/01/15 16:57:34 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	turn_left(t_data *data)
{
	data->player->p_angle -= 0.1;
	if (data->player->p_angle < 0)
		data->player->p_angle += 2 * PI;
	data->player->pdx = cos(data->player->p_angle) * 5;
	data->player->pdy = sin(data->player->p_angle) * 5;
	return (SUCCESS);
}

int	turn_right(t_data *data)
{
	data->player->p_angle += 0.1;
	if (data->player->p_angle > 2 * PI)
		data->player->p_angle -= 2 * PI;
	data->player->pdx = cos(data->player->p_angle) * 5;
	data->player->pdy = sin(data->player->p_angle) * 5;
	return (SUCCESS);
}

int	key_press(int key, t_data *data)
{
	data->player->x_start = data->player->x;
	data->player->y_start = data->player->y;
	if (key == 53 || key == 65307)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	if (key == MAC_LEFT || key == LINUX_LEFT)
		move_left(data);
	if (key == MAC_DOWN || key == LINUX_DOWN)
		move_backward(data);
	if (key == MAC_RIGHT || key == LINUX_RIGHT)
		move_right(data);
	if (key == MAC_UP || key == LINUX_UP)
		move_forward(data);
	if (key == MAC_R_LEFT || key == LINUX_R_LEFT)
		turn_left(data);
	if (key == MAC_R_RIGHT || key == LINUX_R_RIGHT)
		turn_right(data);
	mlx_destroy_image(data->mlx_ptr, data->img->img_ptr);
	init_image(data);
	return (SUCCESS);
}
