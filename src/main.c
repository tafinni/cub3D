/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:26:12 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/16 14:13:18 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_windows(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		error_msg("MLX fail");
		exit_game(data, FAIL, 0);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
	WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (!data->win_ptr)
	{
		error_msg("MLX fail");
		exit_game(data, FAIL, 0);
	}
	create_textures(data);
	init_image(data);
	mlx_hook(data->win_ptr, 17, 1L << 2, exit_game, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_press, data);
	mlx_loop(data->mlx_ptr);
}

static int	check_file_format(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		return (error_msg("Not enough / too many arguments"));
	len = ft_strlen(argv[1]) - 1;
	if (argv[1][len] != 'b' || argv[1][len - 1] != 'u' ||
		argv[1][len - 2] != 'c' || argv[1][len - 3] != '.')
		return (error_msg("Invalid file format"));
	return (SUCCESS);
}

static int	try_open_file(t_data *data, char **argv, int *fd)
{
	int		rsize;

	data->buffer = ft_calloc(2, sizeof(char));
	if (!data->buffer)
		return (error_msg("Malloc fail"));
	*fd = open(argv[1], O_RDONLY);
	if (*fd == FAIL)
	{
		free(data->buffer);
		return (error_msg("File doesn't exist"));
	}
	rsize = read(*fd, data->buffer, 1);
	if (rsize < 1)
	{
		free(data->buffer);
		return (error_msg("Empty file"));
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		fd;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (FAIL);
	set_null(&data);
	if (check_file_format(argc, argv) == SUCCESS && \
	try_open_file(data, argv, &fd) == SUCCESS)
	{
		if (check_map(data, fd) == FAIL)
		{
			free(data);
			return (FAIL);
		}
		else
			init_windows(data);
	}
	else
	{
		free(data);
		return (FAIL);
	}
	return (0);
}
