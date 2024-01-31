/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:13:29 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/15 16:14:53 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	starts_right(char *str, char *find, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
	{
		while (str[i])
		{
			if (str[i + 1] && str[i + 2] && str[i] == \
			find[0] && str[i + 1] == find[1])
				return (1);
			i++;
		}
	}
	else if (flag == 2)
	{
		while (str[i])
		{
			if (str[i] == find[0])
				return (1);
			i++;
		}
	}
	return (-1);
}

static int	find_tex_color(t_data *data, t_list **list, int flag)
{
	if (flag == 4)
	{
		if (get_ea(data, list) == FAIL)
			return (FAIL);
		data->textures->ea_found = 1;
	}
	else if (flag == 5)
	{
		if (get_floor(data, list) == FAIL)
			return (FAIL);
		data->textures->floor_found = 1;
	}
	else if (flag == 6)
	{
		if (get_ceiling(data, list) == FAIL)
			return (FAIL);
		data->textures->ceil_found = 1;
	}
	return (SUCCESS);
}

int	find_texture(t_data *data, t_list **list, int flag)
{
	if (flag == 1)
	{
		if (get_no(data, list) == FAIL)
			return (FAIL);
		data->textures->no_found = 1;
	}
	else if (flag == 2)
	{
		if (get_so(data, list) == FAIL)
			return (FAIL);
		data->textures->so_found = 1;
	}
	else if (flag == 3)
	{
		if (get_we(data, list) == FAIL)
			return (FAIL);
		data->textures->we_found = 1;
	}
	else if (flag > 3)
	{
		if (find_tex_color(data, list, flag) == FAIL)
			return (FAIL);
	}
	data->textures->found++;
	return (SUCCESS);
}

int	map_begin(char *str, int i)
{
	while (str[i] && (str[i] == '	' || str[i] == ' '))
		i++;
	if (str[i] != '\n')
	{
		if (starts_right(str, "NO", 1) == 1)
			return (1);
		else if (starts_right(str, "SO", 1) == 1)
			return (1);
		else if (starts_right(str, "WE", 1) == 1)
			return (1);
		else if (starts_right(str, "EA", 1) == 1)
			return (1);
		else if (starts_right(str, "F", 2) == 1)
			return (1);
		else if (starts_right(str, "C", 2) == 1)
			return (1);
	}
	return (-1);
}

int	check_for_map_line(t_data *data, char *str, int i)
{
	while (str[i] && (str[i] == '	' || str[i] == ' '))
		i++;
	if (str[i] != '\n')
	{
		if (starts_right(str, "NO", 1) == 1)
			return (1);
		else if (starts_right(str, "SO", 1) == 1)
			return (1);
		else if (starts_right(str, "WE", 1) == 1)
			return (1);
		else if (starts_right(str, "EA", 1) == 1)
			return (1);
		else if (starts_right(str, "F", 2) == 1)
			return (1);
		else if (starts_right(str, "C", 2) == 1)
			return (1);
		if (data->textures->no_found == 0 || data->textures->so_found == 0 || \
		data->textures->we_found == 0 || data->textures->ea_found == 0 || \
		data->textures->floor_found == 0 || data->textures->ceil_found == 0)
			return (error_msg("Texture(s) or color(s) not found"));
		return (error_msg("Not valid texture/rgb line"));
	}
	return (0);
}
