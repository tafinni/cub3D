/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:25:40 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/04 20:21:00 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	map_start_point(t_list *list, t_map *map)
{
	while (list != NULL && !ft_strchr(list->str, '1'))
		list = list->next;
	if (list == NULL)
		return (FAIL);
	while (list != NULL && ft_strchr(list->str, '1'))
	{
		map->y_len++;
		list = list->next;
	}
	return (SUCCESS);
}

static int	copy_to_array(t_list *list, char **res, int y, int *x)
{
	if (*x < list->str_len)
	{
		if (list->str[*x] == '1' || list->str[*x] == '0' || \
		list->str[*x] == 'X' || list->str[*x] == 'N' || \
		list->str[*x] == 'E' || list->str[*x] == 'S' || \
		list->str[*x] == 'W')
			res[y][*x] = list->str[*x];
		else
		{
			free_array(res, y + 1);
			return (FAIL);
		}
	}
	else
		res[y][*x] = 'X';
	(*x)++;
	return (SUCCESS);
}

int	check_whole_list(t_list **list)
{
	int		i;
	t_list	*temp;

	temp = *list;
	while (temp != NULL)
	{
		i = 0;
		if (temp->str != NULL)
		{
			while (temp->str[i] != '\0')
			{
				if (temp->str[i] != '	' && temp->str[i] != ' ')
					return (error_msg("Character(s) outside map"));
				i++;
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

static int	copy_list_strs(t_data *data, t_list **list, char **res)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map->y_len)
	{
		x = 0;
		(*list)->str_len = ft_strlen((*list)->str);
		res[y] = malloc(sizeof(char *) * (data->map->x_len + 1));
		if (!res[y])
			return (error_msg("Malloc fail"));
		while (x < data->map->x_len)
		{
			if (copy_to_array((*list), res, y, &x) == FAIL)
				return (error_msg("Forbidden character in map"));
		}
		res[y][x] = '\0';
		y++;
		(*list) = (*list)->next;
	}
	data->map->y_len = y;
	if (check_whole_list(list) == FAIL)
		return (free_array(res, y));
	return (SUCCESS);
}

int	list_to_array(t_data *data, t_map *map, t_list *list)
{
	char	**res;

	list = *list_move(&list, 0);
	if (map_start_point(list, map) == FAIL)
		return (error_msg("Invalid map line"));
	res = (char **)malloc(sizeof(char **) * map->y_len);
	if (!res)
		return (error_msg("Malloc fail"));
	map->x_len = max_x_len(list, 0, 0, 0);
	if (map->x_len == FAIL)
		return (error_msg("Forbidden character in map"));
	if (copy_list_strs(data, &list, res) == FAIL)
		return (FAIL);
	data->map->map = res;
	free_list(list);
	return (SUCCESS);
}
