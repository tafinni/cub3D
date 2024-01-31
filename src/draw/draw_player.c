/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:13:19 by akuzmenk          #+#    #+#             */
/*   Updated: 2024/01/02 12:49:31 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_player_direction(t_data *data)
{
	if (data->player->direction == 'W')
	{
		data->player->p_angle = 0;
	}
	if (data->player->direction == 'N')
	{
		data->player->p_angle = PI / 2;
	}
	if (data->player->direction == 'E')
	{
		data->player->p_angle = PI;
	}
	if (data->player->direction == 'S')
	{
		data->player->p_angle = 3 * PI / 2;
	}
	data->player->pdx = cos(data->player->p_angle) * 5;
	data->player->pdy = sin(data->player->p_angle) * 5;
}
