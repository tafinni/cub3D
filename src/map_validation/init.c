/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:25:43 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/11 16:09:21 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	init_map(t_data **data)
{
	(*data)->map = NULL;
	(*data)->map = malloc(sizeof(t_map));
	if (!(*data)->map)
		return (FAIL);
	(*data)->map->map = NULL;
	(*data)->map->y_len = 0;
	(*data)->map->x_len = 0;
	(*data)->map->border_start = 0;
	return (SUCCESS);
}

static int	init_textures(t_data **data)
{
	(*data)->textures = NULL;
	(*data)->textures = malloc(sizeof(t_textures));
	if (!(*data)->textures)
		return (FAIL);
	(*data)->textures->no_path = NULL;
	(*data)->textures->so_path = NULL;
	(*data)->textures->we_path = NULL;
	(*data)->textures->ea_path = NULL;
	(*data)->textures->no_found = 0;
	(*data)->textures->so_found = 0;
	(*data)->textures->we_found = 0;
	(*data)->textures->ea_found = 0;
	(*data)->textures->floor_found = 0;
	(*data)->textures->ceil_found = 0;
	(*data)->textures->found = 0;
	return (SUCCESS);
}

static int	init_colors(t_data **data)
{
	(*data)->colors = NULL;
	(*data)->colors = malloc(sizeof(t_colors));
	if (!(*data)->colors)
		return (FAIL);
	return (SUCCESS);
}

static int	init_player(t_data **data)
{
	(*data)->player = NULL;
	(*data)->player = malloc(sizeof(t_player));
	if (!(*data)->player)
		return (FAIL);
	(*data)->player->y = 0;
	(*data)->player->x = 0;
	(*data)->player->pdy = 0;
	(*data)->player->pdx = 0;
	(*data)->player->p_angle = 0;
	return (SUCCESS);
}

int	init_variables(t_data **data)
{
	if (init_map(data) == FAIL)
		return (free_data((*data), 0));
	if (init_textures(data) == FAIL)
		return (free_data((*data), 0));
	if (init_colors(data) == FAIL)
		return (free_data((*data), 0));
	if (init_player(data) == FAIL)
		return (free_data((*data), 0));
	(*data)->rays = malloc(sizeof(t_rays));
	if (!(*data)->rays)
		return (FAIL);
	(*data)->textures_data = malloc(sizeof(t_textures_data));
	if (!(*data)->textures_data)
		return (FAIL);
	(*data)->img = malloc(sizeof(t_img));
	if (!(*data)->img)
		return (FAIL);
	return (SUCCESS);
}
