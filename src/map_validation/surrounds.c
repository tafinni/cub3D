/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surrounds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:26:01 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/04 19:47:28 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	map_surrounded(t_data *data, char **map, int y, int x)
{
	if (y < 0 || x < 0 || y >= data->map->y_len || x >= data->map->x_len)
		return (0);
	else if (map[y][x] && (map[y][x] != 'V' && map[y][x] != '1' && \
	map[y][x] != '0' && map[y][x] != 'X' && map[y][x] != 'N' && \
	map[y][x] != 'E' && map[y][x] != 'S' && map[y][x] != 'W'))
	{
		data->error = 1;
		return (0);
	}
	else if (map[y][x] == 'V' || map[y][x] == '1')
		return (0);
	else if (map[y][x] == 'X')
	{
		data->error = 1;
		return (0);
	}
	map[y][x] = 'V';
	map_surrounded(data, map, y + 1, x);
	map_surrounded(data, map, y - 1, x);
	map_surrounded(data, map, y, x + 1);
	map_surrounded(data, map, y, x - 1);
	return (1);
}

static int	row_above(t_data *data, char **map, int y, int x)
{
	if (y > 0 && x > 0 && (map[y - 1][x - 1] != '1' && \
	map[y - 1][x - 1] != 'V' && map[y - 1][x - 1] != '-' && \
	map[y - 1][x - 1] != 'N' && map[y - 1][x - 1] != 'E' && \
	map[y - 1][x - 1] != 'S' && map[y - 1][x - 1] != 'W'))
		return (FAIL);
	if (y > 0 && (map[y - 1][x] != '1' && map[y - 1][x] != 'V' && \
	map[y - 1][x] != '-' && map[y - 1][x] != 'N' && map[y - 1][x] != 'E' && \
	map[y - 1][x] != 'S' && map[y - 1][x] != 'W'))
		return (FAIL);
	if (y > 0 && x < data->map->x_len - 1 && \
	(map[y - 1][x + 1] != '1' && map[y - 1][x + 1] != 'V' && \
	map[y - 1][x + 1] != '-' && map[y - 1][x + 1] != 'N' && \
	map[y - 1][x + 1] != 'E' && map[y - 1][x + 1] != 'S' && \
	map[y - 1][x + 1] != 'W'))
		return (FAIL);
	return (SUCCESS);
}

static int	row_current(t_data *data, char **map, int y, int x)
{
	if (x > 0 && (map[y][x - 1] != '1' && map[y][x - 1] != 'V' && \
	map[y][x - 1] != '-' && map[y][x - 1] != 'N' && \
	map[y][x - 1] != 'E' && map[y][x - 1] != 'S' && map[y][x - 1] != 'W'))
		return (FAIL);
	if (x < data->map->x_len - 1 && (map[y][x + 1] != '1' && \
	map[y][x + 1] != 'V' && map[y][x + 1] != '-' && \
	map[y][x + 1] != 'N' && map[y][x + 1] != 'E' && map[y][x + 1] != 'S' && \
	map[y][x + 1] != 'W'))
		return (FAIL);
	return (SUCCESS);
}

static int	row_below(t_data *data, char **map, int y, int x)
{
	if (y < data->map->y_len - 1 && x > 0 && \
	(map[y + 1][x - 1] != '1' && map[y + 1][x - 1] != 'V' && \
	map[y + 1][x - 1] != '-' && map[y + 1][x - 1] != 'N' && \
	map[y + 1][x - 1] != 'E' && map[y + 1][x - 1] != 'S' && \
	map[y + 1][x - 1] != 'W'))
		return (FAIL);
	if (y < data->map->y_len - 1 && (map[y + 1][x] != '1' && \
	map[y + 1][x] != 'V' && map[y + 1][x] != '-' && map[y + 1][x] != 'N' && \
	map[y + 1][x] != 'E' && map[y + 1][x] != 'S' && map[y + 1][x] != 'W'))
		return (FAIL);
	if (y < data->map->y_len - 1 && x < data->map->x_len && \
	(map[y + 1][x + 1] != '1' && map[y + 1][x + 1] != 'V' && \
	map[y + 1][x + 1] != '-' && map[y + 1][x + 1] != 'N' && \
	map[y + 1][x + 1] != 'E' && map[y + 1][x + 1] != 'S' && \
	map[y + 1][x + 1] != 'W'))
		return (FAIL);
	return (SUCCESS);
}

int	space_surrounds(t_data *data, char **map, int y, int x)
{
	if (y == 0 || x == 0 || y == data->map->y_len - 1 || \
	x == data->map->x_len - 1)
		return (FAIL);
	if (row_above(data, map, y, x) == FAIL)
		return (FAIL);
	if (row_current(data, map, y, x) == FAIL)
		return (FAIL);
	if (row_below(data, map, y, x) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
