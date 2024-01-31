/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:25:57 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/15 19:03:34 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_textures(t_data *data, t_list **list)
{
	int	i;

	i = 0;
	while ((*list) != NULL)
	{
		list = list_move(list, i);
		if (map_begin((*list)->str, 0) == -1)
			break ;
		if (check_for_map_line(data, (*list)->str, 0) == -1)
			return (FAIL);
		i = 1;
		if (list == NULL)
			return (FAIL);
		if (texture_check(data, list) == FAIL)
			return (FAIL);
		if (color_check(data, list) == FAIL)
			return (FAIL);
	}
	if (data->textures->found != 6)
		return (error_msg("Problem in finding textures"));
	return (SUCCESS);
}

static void	save_player_pos(t_data *data, char c, int y, int *found)
{
	int	x;

	x = 0;
	while (x < data->map->x_len)
	{
		while (data->map->map[y][x] && data->map->map[y][x] != c)
			x++;
		if (data->map->map[y][x] && data->map->map[y][x] == c)
		{
			data->player->x = x;
			data->player->y = y;
			data->player->direction = c;
			(*found)++;
		}
		x++;
	}
}

static int	find_player(t_data *data, char **map)
{
	int	found;
	int	y;

	found = 0;
	y = 0;
	while (y < data->map->y_len)
	{
		if (ft_strchr(map[y], 'N'))
			save_player_pos(data, 'N', y, &found);
		if (ft_strchr(map[y], 'S'))
			save_player_pos(data, 'S', y, &found);
		if (ft_strchr(map[y], 'E'))
			save_player_pos(data, 'E', y, &found);
		if (ft_strchr(map[y], 'W'))
			save_player_pos(data, 'W', y, &found);
		y++;
	}
	if (found != 1)
		return (error_msg("Wrong amount of players in map"));
	get_player_direction(data);
	return (SUCCESS);
}

static int	get_map_info(t_data *data, t_list *list)
{
	if (get_textures(data, &list) == FAIL)
	{
		free_data(data, 0);
		exit (FAIL);
	}
	if (list_to_array(data, data->map, list) == FAIL)
	{
		free_list(list);
		return (free_data(data, 0));
	}
	free_list(list);
	if (find_player(data, data->map->map) == FAIL)
		return (free_data(data, 0));
	return (SUCCESS);
}

int	check_map(t_data *data, int fd)
{
	t_list	*list;

	list = NULL;
	if (init_variables(&data) == FAIL)
	{
		close(fd);
		return (error_msg("Malloc fail"));
	}
	if (read_to_list(data, fd, &list) == FAIL)
		return (error_msg("Failed to create list"));
	if (get_map_info(data, list) == FAIL)
		return (FAIL);
	if (map_errors(data, data->map->map) == FAIL)
		return (free_data(data, 0));
	if (data->map->x_len > MAP_MAX_X || data->map->y_len > MAP_MAX_Y)
		return (error_msg("Map too large"));
	data->player->x = data->player->x * GRID_SIZE;
	data->player->y = data->player->y * GRID_SIZE;
	data->player->x = data->player->x + GRID_SIZE / 2;
	data->player->y = data->player->y + GRID_SIZE / 2;
	return (SUCCESS);
}
