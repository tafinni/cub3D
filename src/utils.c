/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:26:15 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/02 18:19:58 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	error_msg(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (FAIL);
}

int	exit_game(t_data *data, int exit_code, int flag)
{
	free_data(data, flag);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (exit_code != FAIL)
		exit_code = SUCCESS;
	exit(exit_code);
	return (0);
}

void	set_null(t_data **data)
{
	(*data)->buffer = NULL;
	(*data)->error = SUCCESS;
	(*data)->map = NULL;
	(*data)->textures = NULL;
	(*data)->colors = NULL;
	(*data)->player = NULL;
	(*data)->mlx_ptr = NULL;
	(*data)->win_ptr = NULL;
	(*data)->rays = NULL;
	(*data)->textures_data = NULL;
	(*data)->img = NULL;
}
