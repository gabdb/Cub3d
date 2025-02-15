/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:49:04 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/14 14:49:35 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char    *dest;

	if (x >= 0 && x < 1000 && y >= 0 && y < 800)
	{
		dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}

void clear_image(t_mlx *data, int color)
{
    for (int y = 0; y < 1000; y++)
    {
        for (int x = 0; x < 1000; x++)
        {
            my_mlx_pixel_put(data, x, y, color);
        }
    }
}

int handle_keypress(int keycode, t_mlx *data)
{
	float	rot_speed;
	double	save_dir_x;
	double	save_plane_x;
	float	speed = 0.25; //temporaire

	rot_speed = data->player->rot_speed;
	save_dir_x = data->player->dir_x;
	save_plane_x = data->player->plane_x;

	if (keycode == 65307) // Escape key (Linux)
	{
		mlx_destroy_window(data->mlx, data->window);
		exit(0);
	}
	if (keycode == 65363) // RIGHT arrow
	{
		data->player->dir_x = data->player->dir_x * cos(rot_speed) - data->player->dir_y * sin(rot_speed);
		data->player->dir_y = save_dir_x * sin(rot_speed) + data->player->dir_y * cos(rot_speed);

		data->player->plane_x = data->player->plane_x * cos(rot_speed) - data->player->plane_y * sin(rot_speed);
		data->player->plane_y = save_plane_x * sin(rot_speed) + data->player->plane_y * cos(rot_speed);
	}
	else if (keycode == 65361) // LEFT arrow
	{
		data->player->dir_x = data->player->dir_x * cos(-rot_speed) - data->player->dir_y * sin(-rot_speed);
		data->player->dir_y = save_dir_x * sin(-rot_speed) + data->player->dir_y * cos(-rot_speed);

		data->player->plane_x = data->player->plane_x * cos(-rot_speed) - data->player->plane_y * sin(-rot_speed);
		data->player->plane_y = save_plane_x * sin(-rot_speed) + data->player->plane_y * cos(-rot_speed);
	}
	else if (keycode == 65362) // Up arrow
	{
		printf("float_x = %f and float_y = %f\n", data->player->x_pos + data->player->dir_x * speed, data->player->y_pos + data->player->dir_y * speed);
		if (check_wall(data, data->player->x_pos + data->player->dir_x * speed, data->player->y_pos + data->player->dir_y * speed))
		{
			data->player->x_pos += data->player->dir_x * speed;
			data->player->y_pos += data->player->dir_y * speed;
		}
	}
	clear_image(data, 0X000000);
	render_3d(data);

	return (0);
}

int close_window(t_mlx *data)
{
    mlx_destroy_window(data->mlx, data->window);
    exit(0);
}

void	handle_mlx(t_mlx *data)
{
	data->mlx = mlx_init();

	data->window = mlx_new_window(data->mlx, WINDOW_LENGTH, WINDOW_HEIGHT, "Top-Down View");
	data->image = mlx_new_image(data->mlx, WINDOW_LENGTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->line_length, &data->endian);
	
	//mlx_loop_hook(data->mlx, render, data);;
	data->player = init_player(data);
	init_raycast(data->player);
	render_3d(data);

	mlx_key_hook(data->window, handle_keypress, data);
	mlx_hook(data->window, 17, 0, close_window, data);

	mlx_loop(data->mlx);
}
