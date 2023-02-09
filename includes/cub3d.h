/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghan <sanghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:32:29 by doykim            #+#    #+#             */
/*   Updated: 2023/02/08 20:50:49 by sanghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define KEY_ESC	53
# define KEY_W		13
# define KEY_S		1
# define KEY_A		0
# define KEY_D		2
# define KEY_LEFT	123
# define KEY_RIGHT	124

# define WIDTH		1920
# define HEIGHT		1080
# define TWIDTH		64
# define THEIGHT	64
# define MAX_SIZE	1000000

typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	wall_x;
	int		drawstart;
	int		drawend;
	int		texture_x;
	int		texture_y;
	double	step;
	double	texture_pos;
}	t_ray;

typedef struct s_game
{
	t_img		*image;
	void		*mlx;
	void		*win;
	int			p_flag;
	double		plane_x;
	double		plane_y;
	char		**map;
	int			map_width;
	int			map_height;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor;
	int			ceil;
	double		movespeed;
	double		rotspeed;
	t_player	player;
	t_ray		*ray;
	t_img		img_no;
	t_img		img_so;
	t_img		img_we;
	t_img		img_ea;
}	t_game;

//init
void	init_game(int ac, char *av[], t_game *game, t_img *img);

void	check_file(int ac, char **av, t_game *game);
void	check_argument(int ac, char **av);

void	init_element(char **temp, t_game *game);
void	init_texture(t_game *game, char *line);
int		check_texture(char *line, char **tmp);

void	init_rgb(t_game *game, char *line);
void	check_rgb_num(char **temp);
void	*make_rgb_img(t_game *game, int rgb);

void	read_map(char **temp, t_game *game);
void	check_map(char **temp, t_game *game);
void	init_player(char c, int x, int y, t_game *game);
void	init_dir(char dir, t_game *game);

//key
int		key_press(int key, t_game *game);
int		x_exit(int n);

//utils
void	error_exit(int n);
void	free_2d_array(char **str);

//raycast
int		raycasting(t_game *game);
void	calculate_perp_wall_dist(t_game *game, t_ray *ray);
void	dda(t_game *game, t_ray *ray);
void	set_ray_values2(t_game *game, t_ray *ray);
void	set_ray_values(t_game *game, t_ray *ray, int x);

void	draw_img(t_game *game, t_ray *ray, t_img *texture_img, int x);
void	calculate_line(t_game *game, t_ray *ray, t_img *texture_img);
void	set_wall(t_game *game, t_ray *ray, int x);

#endif
