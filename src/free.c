/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:26:08 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/02 18:18:26 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	free_list(t_list *list)
{
	t_list	*temp;

	if (list == NULL)
		return (FAIL);
	while (list->previous != NULL)
		list = list->previous;
	while (list != NULL)
	{
		temp = list->next;
		if (list->str)
		{
			free(list->str);
			list->str = NULL;
		}
		free(list);
		list = NULL;
		list = temp;
	}
	return (FAIL);
}

int	free_array(char **str, int len)
{
	int	y;

	y = 0;
	while (y < len)
	{
		free(str[y]);
		y++;
	}
	free(str);
	return (FAIL);
}

int	free_textures(t_data *data)
{
	if (data->textures != NULL)
	{
		if (data->textures->no_path)
			free(data->textures->no_path);
		data->textures->no_path = NULL;
		if (data->textures->so_path)
			free(data->textures->so_path);
		data->textures->so_path = NULL;
		if (data->textures->we_path)
			free(data->textures->we_path);
		data->textures->we_path = NULL;
		if (data->textures->ea_path)
			free(data->textures->ea_path);
		data->textures->ea_path = NULL;
		free(data->textures);
		data->textures = NULL;
	}
	return (FAIL);
}

void	free_tex_data(t_texture_info *tex)
{
	int	i;

	i = 0;
	if (!tex->tex_data)
	{
		return ;
	}
	while (i < tex->tex_height)
	{
		if (tex->tex_data[i])
		{
			free(tex->tex_data[i]);
			tex->tex_data[i] = NULL;
		}
		i++;
	}
	free(tex->tex_data);
	tex->tex_data = NULL;
}

int	free_data(t_data *data, int flag)
{
	if (data->map != NULL)
	{
		if (data->map->map)
			free_array(data->map->map, data->map->y_len);
		free(data->map);
	}
	if (data->colors != NULL)
		free(data->colors);
	if (data->player != NULL)
		free(data->player);
	if (data->img != NULL)
		free(data->img);
	free_textures(data);
	if (data->rays != NULL)
		free(data->rays);
	free(data->textures_data);
	if (flag != 0)
	{
		free_tex_data(&data->north);
		free_tex_data(&data->east);
		free_tex_data(&data->south);
		free_tex_data(&data->west);
	}
	return (FAIL);
}
