/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:25:33 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/04 20:19:47 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	texture_check(t_data *data, t_list **list)
{
	if (starts_right((*list)->str, "NO", 1) == 1)
	{
		if (find_texture(data, list, 1) == FAIL)
			return (FAIL);
	}
	else if (starts_right((*list)->str, "SO", 1) == 1)
	{
		if (find_texture(data, list, 2) == FAIL)
			return (FAIL);
	}
	else if (starts_right((*list)->str, "WE", 1) == 1)
	{
		if (find_texture(data, list, 3) == FAIL)
			return (FAIL);
	}
	else if (starts_right((*list)->str, "EA", 1) == 1)
	{
		if (find_texture(data, list, 4) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

static int	check_walls(t_data *data, char **temp_map)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map->y_len && data->error == 0)
	{
		if (ft_strchr(temp_map[y], '0'))
		{
			x = 0;
			while (temp_map[y][x] != '0')
				x++;
			map_surrounded(data, temp_map, y, x);
		}
		else
			y++;
	}
	if (data->error == 1)
		return (error_msg("Map not surrounded by walls"));
	return (SUCCESS);
}

static int	check_corners(t_data *data, char **temp_map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < data->map->y_len && data->error == 0)
	{
		if (temp_map[y] && ft_strchr(temp_map[y], 'V'))
		{
			while (temp_map[y][x] != 'V')
				x++;
			temp_map[y][x] = '-';
			if (space_surrounds(data, temp_map, y, x) == FAIL)
				return (error_msg("Map not surrounded by walls"));
		}
		else
		{
			x = 0;
			y++;
		}
	}
	return (SUCCESS);
}

int	map_errors(t_data *data, char **map)
{
	char	**temp_map;

	temp_map = duplicate_arr(map, data->map->y_len);
	if (!temp_map)
		return (error_msg("Malloc fail"));
	if (check_walls(data, temp_map) == FAIL)
		return (free_array(temp_map, data->map->y_len));
	if (check_corners(data, temp_map) == FAIL)
		return (free_array(temp_map, data->map->y_len));
	if (space_surrounds(data, temp_map, data->player->y, \
	data->player->x) == FAIL)
	{
		free_array(temp_map, data->map->y_len);
		return (error_msg("Player not in map"));
	}
	free_array(temp_map, data->map->y_len);
	return (SUCCESS);
}

int	list_lenght(t_list *list)
{
	int		count;
	t_list	*temp;

	count = 0;
	if (list != NULL)
	{
		temp = list;
		while (temp != NULL)
		{
			temp = temp->next;
			count ++;
		}
	}
	return (count);
}
