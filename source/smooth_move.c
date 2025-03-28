/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:44:23 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/26 16:50:57 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Initialise la structure des touches de contrôle avec des valeurs à zéro.
*/
t_keys	*init_keys(void)
{
	t_keys	*keys;

	keys = safe_malloc(sizeof(t_keys));
	keys->backward = 0;
	keys->forward = 0;
	keys->left = 0;
	keys->right = 0;
	keys->rotate_left = 0;
	keys->rotate_right = 0;
	return (keys);
}

/*
** Met à jour l'état des touches lors d'une pression
** clavier pour gérer les mouvements et rotations.
*/
int	key_press(int keycode, t_mlx *data)
{
	if (keycode == 65307)
	{
		//mlx_destroy_window(data->mlx, data->window);
		//mlx_destroy_display(data->mlx);
		//mlx_destroy_image(data->mlx, data->image);
		free_all(data);
		exit(0);
	}
	else if (keycode == 65362 || keycode == 119)
		data->keys->forward = 1;
	else if (keycode == 65364 || keycode == 115)
		data->keys->backward = 1;
	else if (keycode == 65361 || keycode == 97)
		data->keys->rotate_left = 1;
	else if (keycode == 65363 || keycode == 100)
		data->keys->rotate_right = 1;
	return (0);
}

/*
** Réinitialise l'état des touches lorsque les touches
** de mouvement ou rotation sont relâchées.
*/
int	key_release(int keycode, t_mlx *data)
{
	if (keycode == 65362 || keycode == 119)
		data->keys->forward = 0;
	else if (keycode == 65364 || keycode == 115)
		data->keys->backward = 0;
	else if (keycode == 65361 || keycode == 97)
		data->keys->rotate_left = 0;
	else if (keycode == 65363 || keycode == 100)
		data->keys->rotate_right = 0;
	return (0);
}

/*
** Gère la boucle principale du jeu : calcul des mouvements,
** rotations et rendu 3D.
*/
int	game_loop(t_mlx *data)
{
	t_loop	n;

	n.current_time = get_time_in_seconds();
	n.delta_time = n.current_time - data->last_frame;
	data->last_frame = n.current_time;
	n.move_speed = 4.0 * n.delta_time;
	n.rot_speed = 2.0 * n.delta_time;
	move_front_back(data, &n.new_x, &n.new_y, n.move_speed);
	n.save_dir_x = data->player->dir_x;
	n.save_plane_x = data->player->plane_x;
	rot(data, n.save_dir_x, n.save_plane_x, n.rot_speed);
	render_3d(data);
	return (0);
}
