/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:45:45 by tfinni            #+#    #+#             */
/*   Updated: 2024/01/15 16:37:08 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx/minilibx_linux/mlx.h"
//# include <mlx.h>
# include <fcntl.h>
# include <math.h>

# define FAIL -1
# define SUCCESS 0

# define PI 3.1415926535
# define WINDOW_WIDTH 720 
# define WINDOW_HEIGHT 540 
# define GRID_SIZE 15
# define FOV 60.0
# define DEG_TO_RAD 0.0174533
# define HUGE_NUMBER 10000000
# define PLAYER_SPEED 3

# define LINUX_UP 119
# define LINUX_RIGHT 100
# define LINUX_LEFT 97
# define LINUX_DOWN 115
# define LINUX_R_LEFT 65361
# define LINUX_R_RIGHT 65363

# define MAC_UP 13
# define MAC_RIGHT 2
# define MAC_LEFT 0
# define MAC_DOWN 1
# define MAC_R_LEFT 123
# define MAC_R_RIGHT 124

# define MAP_MAX_Y 35
# define MAP_MAX_X 35

typedef struct s_list
{
	char			*str;
	int				str_len;
	struct s_list	*next;
	struct s_list	*previous;
}	t_list;

typedef struct s_map
{
	char	**map;
	int		y_len;
	int		x_len;
	int		border_start;
}	t_map;

typedef struct s_textures
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		no_found;
	int		so_found;
	int		we_found;
	int		ea_found;
	int		floor_found;
	int		ceil_found;
	int		found;
}	t_textures;

typedef struct s_colors
{
	int	ceiling;
	int	floor;
}	t_colors;

typedef struct s_player
{
	float	y;
	float	x;
	float	y_start;
	float	x_start;
	char	direction;
	float	p_angle;
	float	pdx;
	float	pdy;
	int		xo;
	int		yo;
	float	ch_x_a;
	float	ch_y_a;
	float	ch_x_d;
	float	ch_y_d;
	float	ch_x_s;
	float	ch_y_s;
	float	ch_x_w;
	float	ch_y_w;
}	t_player;

typedef struct s_rays
{
	int		mp;
	int		mx;
	int		my;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	horizontal_x;
	float	horizontal_y;
	float	vertical_x;
	float	vertical_y;
	float	dis_v;
	float	dis_h;
	float	dis_fin;
	float	a_tan;
	float	n_tan;
}				t_rays;

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			line_length;
	int			bits_per_pixel;
	int			endian;
	int			*data;
}				t_img;

typedef struct s_texture_info
{
	int		tex_height;
	int		tex_width;
	int		**tex_data;
}	t_texture_info;

typedef struct s_textures_data
{
	t_texture_info		*tex;
	float				tex_x;
	float				tex_y;
	int					tex_xi;
	int					tex_yi;
	int					tex_height;
	int					wall_top;
	int					wall_bottom;
	int					draw_end;
	float				offs;
	float				mod_ofs;
	int					x;
}				t_textures_data;

typedef struct s_data
{
	int				error;
	t_map			*map;
	t_textures		*textures;
	t_colors		*colors;
	t_player		*player;
	t_rays			*rays;
	t_textures_data	*textures_data;
	t_img			*img;
	void			*mlx_ptr;
	void			*win_ptr;
	t_texture_info	north;
	t_texture_info	south;
	t_texture_info	east;
	t_texture_info	west;
	char			*buffer;
}	t_data;

// free.c
int				free_list(t_list *list);
int				free_array(char **str, int len);
int				free_textures(t_data *data);
void			free_tex_data(t_texture_info *tex);
int				free_data(t_data *data, int flag);

// key_hook_move.c
int				move_left(t_data *data);
int				move_right(t_data *data);
int				move_forward(t_data *data);
int				move_backward(t_data *data);

// key_hook.c
int				turn_left(t_data *data);
int				turn_right(t_data *data);
int				key_press(int key, t_data *data);

// utils.c
int				error_msg(char *msg);
int				exit_game(t_data *data, int exit_code, int flag);
void			set_null(t_data **data);

// - DRAW
// create_textures.c
void			init_text_data(t_texture_info *texture_info);
t_texture_info	fill_text_data(t_data *data, t_img *img, char *path);
void			init_textures_info(t_data *data);
void			create_textures(t_data *data);

// draw_image.c
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			draw_ceil_floor(t_data *data);
int				init_image(t_data *data);

// draw_player.c
void			get_player_direction(t_data *data);

// draw_walls.c
float			fix_fisheye(t_data *data);
void			set_walls_size(t_data *data);
void			help_init_draw_walls(t_data *data);
void			draw_walls(t_data *data, int number_rays);

// - MAP_VALIDATION
// check.c
int				texture_check(t_data *data, t_list **list);
int				map_errors(t_data *data, char **map);
int				list_lenght(t_list *list);

// color.c
int				color_check(t_data *data, t_list **list);
int				get_floor(t_data *data, t_list **list);
int				get_ceiling(t_data *data, t_list **list);

// create_map.c
int				check_whole_list(t_list **list);
int				list_to_array(t_data *data, t_map *map, t_list *list);

// init.c
int				init_variables(t_data **data);

// list.c
char			*list_help(t_data *data, char *str, int fd, int flag);
int				read_to_list(t_data *data, int fd, t_list **list);
t_list			**list_move(t_list **list, int flag);
t_list			*add_temp_back(t_list *list, t_list *temp);

// map_utils.c
char			**duplicate_arr(char **map, int len);
int				scroll_empty(char *str, int i);
int				path_start(char *str, char *find, int flag);
int				check_texture_type(char *str);
int				max_x_len(t_list *list, int best, int current, int x);

// map.c
int				check_map(t_data *data, int fd);

// surrounds.c
int				map_surrounded(t_data *data, char **map, int y, int x);
int				space_surrounds(t_data *data, char **map, int y, int x);

// textures_utils.c
int				starts_right(char *str, char *find, int flag);
int				find_texture(t_data *data, t_list **list, int flag);
int				map_begin(char *str, int i);
int				check_for_map_line(t_data *data, char *str, int i);

// textures.c
int				get_no(t_data *data, t_list **list);
int				get_so(t_data *data, t_list **list);
int				get_we(t_data *data, t_list **list);
int				get_ea(t_data *data, t_list **list);

// - RAYCASTER
// dda_algorithm.c
void			fix_ray_len_overflow(t_data *data);
float			ray_distance(t_data *data);
void			check_a_wall(t_data *data, char flag_vertical_horizontal);
void			check_hit_with_dda(t_data *data, char flag_v_h);

// ray_caster_utils.c
void			init_rays(t_rays *rays);

// ray_caster.c
void			create_horizontal_ray(t_data *data);
void			create_vertical_ray(t_data *data);
void			choose_wall_texture(t_data *data);
void			run_raycaster(t_data *data);
void			start_raycaster(t_data *data);

#endif
