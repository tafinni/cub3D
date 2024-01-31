/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:26:04 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/15 16:13:18 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*save_path(char *str, int i)
{
	int		y;
	int		empty;

	y = 0;
	empty = 0;
	i = scroll_empty(str, i);
	if (!str[i] || str[i] != '.' || str[i + 1] != '/' || \
	!ft_isalpha(str[i + 2]))
		return (NULL);
	y = i;
	while (str[y] && str[y] != '	' && str[y] != ' ')
		y++;
	while ((str[y] && str[y] == '	') || (str[y] && str[y] == ' ') || \
	(str[y] && str[y] == '\n'))
	{
		empty++;
		y++;
	}
	if (str[y - 1] != '\n')
		return (NULL);
	if (str[y - 2] != '	' || str[y - 2] != '	')
		empty++;
	if ((empty && str[y - 2] == '	') || (empty && str[y - 2] == ' '))
		empty--;
	return (ft_substr(str, i, ft_strlen(str) - i - empty));
}

int	get_no(t_data *data, t_list **list)
{
	int	i;

	if (data->textures->no_found == 1)
		return (error_msg("Duplicate NO texture"));
	i = path_start((*list)->str, "NO", 1);
	if (i == FAIL || ((*list)->str[i] != '	' && (*list)->str[i] != ' '))
		return (error_msg("Can't find NO texture from .cub file"));
	data->textures->no_path = save_path((*list)->str, i);
	if (!data->textures->no_path)
		return (error_msg("Can't get NO texture from .cub file"));
	if (check_texture_type(data->textures->no_path) == FAIL)
		return (error_msg("Wrong texture type"));
	return (SUCCESS);
}

int	get_so(t_data *data, t_list **list)
{
	int	i;

	if (data->textures->so_found == 1)
		return (error_msg("Duplicate SO texture"));
	i = path_start((*list)->str, "SO", 1);
	if (i == FAIL || ((*list)->str[i] != '	' && (*list)->str[i] != ' '))
		return (error_msg("Can't find SO texture from .cub file"));
	data->textures->so_path = save_path((*list)->str, i);
	if (!data->textures->so_path)
		return (error_msg("Can't get SO texture from .cub file"));
	if (check_texture_type(data->textures->so_path) == FAIL)
		return (error_msg("Wrong texture type"));
	return (SUCCESS);
}

int	get_we(t_data *data, t_list **list)
{
	int	i;

	if (data->textures->we_found == 1)
		return (error_msg("Duplicate we texture"));
	i = path_start((*list)->str, "WE", 1);
	if (i == FAIL || ((*list)->str[i] != '	' && (*list)->str[i] != ' '))
		return (error_msg("Can't find WE texture from .cub file"));
	data->textures->we_path = save_path((*list)->str, i);
	if (!data->textures->we_path)
		return (error_msg("Can't get WE texture from .cub file"));
	if (check_texture_type(data->textures->we_path) == FAIL)
		return (error_msg("Wrong texture type"));
	return (SUCCESS);
}

int	get_ea(t_data *data, t_list **list)
{
	int	i;

	if (data->textures->ea_found == 1)
		return (error_msg("Duplicate EA texture"));
	i = path_start((*list)->str, "EA", 1);
	if (i == FAIL || ((*list)->str[i] != '	' && (*list)->str[i] != ' '))
		return (error_msg("Can't find WE texture from .cub file"));
	data->textures->ea_path = save_path((*list)->str, i);
	if (!data->textures->ea_path)
		return (error_msg("Can't get EA texture from .cub file"));
	if (check_texture_type(data->textures->ea_path) == FAIL)
		return (error_msg("Wrong texture type"));
	return (SUCCESS);
}
