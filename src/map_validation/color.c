/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:25:37 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/02 14:28:53 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	color_check(t_data *data, t_list **list)
{
	if (starts_right((*list)->str, "F", 2) == 1)
	{
		if (find_texture(data, list, 5) == FAIL)
			return (FAIL);
	}
	else if (starts_right((*list)->str, "C", 2) == 1)
	{
		if (find_texture(data, list, 6) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

static int	get_rgb_int(char *str, int start, int len)
{
	char	*temp;
	int		res;

	temp = ft_substr(str, start, len);
	if (!temp)
		return (error_msg("Malloc fail"));
	res = ft_atoi(temp);
	free(temp);
	if (res > 255 || res < 0)
		return (error_msg("Not a valid RGB value"));
	return (res);
}

static int	find_rgb(char *str, int *i, int flag, int y)
{
	int		start;
	int		len;

	len = 0;
	if (flag == 1)
		*i = scroll_empty(str, *i);
	start = *i;
	if (!ft_isalnum(str[*i]) && str[*i] != ',' && str[*i] != '	' \
	&& str[*i] != ' ')
		return (error_msg("Error in finding rgb values"));
	while ((str[*i] && str[*i] >= '0' && str[*i] <= '9' && len++ < 4) \
	|| str[*i] == ' ' || str[*i] == '	')
		(*i)++;
	if (flag == 3)
	{
		y = *i;
		while ((str[y] && str[y] == '	') || (str[y] && str[y] == ' ') || \
		(str[y] && str[y] == '\n'))
			y++;
		if (str[y] != '\0')
			return (error_msg("Error in finding rgb values"));
	}
	(*i)++;
	return (get_rgb_int(str, start, len));
}

int	get_floor(t_data *data, t_list **list)
{
	int	i;
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	if (data->textures->floor_found == 1)
		return (error_msg("Duplicate F texture"));
	i = path_start((*list)->str, "F", 2);
	if (i == FAIL)
		return (error_msg("Error in finding rgb values"));
	r = find_rgb((*list)->str, &i, 1, 0);
	if (r == FAIL)
		return (FAIL);
	g = find_rgb((*list)->str, &i, 2, 0);
	if (g == FAIL)
		return (FAIL);
	b = find_rgb((*list)->str, &i, 3, 0);
	if (b == FAIL)
		return (FAIL);
	data->colors->floor = (r << 16) | (g << 8) | b;
	return (SUCCESS);
}

int	get_ceiling(t_data *data, t_list **list)
{
	int	i;
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	if (data->textures->ceil_found == 1)
		return (error_msg("Duplicate C texture"));
	i = path_start((*list)->str, "C", 2);
	if (i == FAIL)
		return (error_msg("Error in finding rgb values"));
	r = find_rgb((*list)->str, &i, 1, 0);
	if (r == FAIL)
		return (FAIL);
	g = find_rgb((*list)->str, &i, 2, 0);
	if (g == FAIL)
		return (FAIL);
	b = find_rgb((*list)->str, &i, 3, 0);
	if (b == FAIL)
		return (FAIL);
	data->colors->ceiling = (r << 16) | (g << 8) | b;
	return (SUCCESS);
}
