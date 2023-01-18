/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doykim <doykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:32:29 by doykim            #+#    #+#             */
/*   Updated: 2023/01/18 14:35:47 by doykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libs/libft/libft.h"

typedef struct s_player
{
	int		x;
	int		y;
	void	*front;
	void	*back;
	void	*left;
	void	*right;
}	t_player;

typedef struct s_game
{
	int			width;
	int			height;
	int			p_cnt;
	char		p_dir;
	char		**map;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	void		*mlx;
	void		*win;
	void		*floor;
	void		*wall;
	t_player	player;
}	t_game;

//map
void	check_file(int ac, char **av, t_game *game);
void	check_argument(int ac, char **av);
void	check_element(char *buff, t_game *game);

void	read_map(char **temp, t_game *game);

//game
void	init_game(t_game *game);

//utils
void	error_exit(int n);
void	free_2d_array(char **str);
void	print_2d(char **arr);

#endif
