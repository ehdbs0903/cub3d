/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghan <sanghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:40:49 by doykim            #+#    #+#             */
/*   Updated: 2023/02/08 20:43:33 by doykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_leak(void)
{
	system("leaks cub3d");
}

int	main(int ac, char *av[])
{
	t_game	game;
	t_img	img;

	atexit(check_leak);
	init_game(ac, av, &game, &img);
	game.image->img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (game.image->img == NULL)
		exit(1);
	mlx_hook(game.win, 2, 0, key_press, &game);
	main_loop(&game);
	mlx_loop(game.mlx);
	free_2d_array(game.map);
	free(game.no_path);
	free(game.so_path);
	free(game.we_path);
	free(game.ea_path);
	mlx_destroy_window(game.mlx, game.win);
	return (0);
}
