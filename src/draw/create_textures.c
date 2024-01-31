/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:13:02 by akuzmenk          #+#    #+#             */
/*   Updated: 2024/01/10 16:57:18 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_text_data(t_texture_info *texture_info)
{
	int	i;

	i = 0;
	texture_info->tex_data = ft_calloc(texture_info->tex_height, sizeof(int *));
	while (i < texture_info->tex_height)
	{
		texture_info->tex_data[i] = ft_calloc(texture_info->tex_width, \
		sizeof(int));
		i++;
	}
}

t_texture_info	fill_text_data(t_data *data, t_img *img, char *path)
{
	t_texture_info	new_tex;
	int				i;
	int				j;

	img->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, path, \
	&new_tex.tex_width, &new_tex.tex_height);
	if (img->img_ptr == NULL)
	{
		error_msg("Texture not found");
		exit_game(data, FAIL, 1);
	}
	img->data = (int *)mlx_get_data_addr(img->img_ptr, \
	&img->bits_per_pixel, &img->line_length, &img->endian);
	init_text_data(&new_tex);
	i = -1;
	while (++i < new_tex.tex_height)
	{
		j = -1;
		while (++j < new_tex.tex_width)
			new_tex.tex_data[i][j] = img->data[new_tex.tex_width * i + j];
	}
	mlx_destroy_image(data->mlx_ptr, img->img_ptr);
	return (new_tex);
}

void	init_textures_info(t_data *data)
{
	data->north.tex_height = 0;
	data->north.tex_width = 0;
	data->north.tex_data = NULL;
	data->south.tex_height = 0;
	data->south.tex_width = 0;
	data->south.tex_data = NULL;
	data->east.tex_height = 0;
	data->east.tex_width = 0;
	data->east.tex_data = NULL;
	data->west.tex_height = 0;
	data->west.tex_width = 0;
	data->west.tex_data = NULL;
}

void	create_textures(t_data *data)
{
	t_img	img;

	init_textures_info(data);
	data->north = fill_text_data(data, &img, data->textures->no_path);
	data->south = fill_text_data(data, &img, data->textures->so_path);
	data->east = fill_text_data(data, &img, data->textures->ea_path);
	data->west = fill_text_data(data, &img, data->textures->we_path);
	if (data->north.tex_data == NULL || data->north.tex_data == NULL \
	|| data->north.tex_data == NULL || data->north.tex_data == NULL)
	{
		error_msg("Texture not found");
		exit_game(data, FAIL, 1);
	}
}
