/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:55:00 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/28 15:36:20 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dest;

	if (x >= 0 && x < 800 && y >= 0 && y < 600)
	{
		dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}

void clear_image(t_data *data, int color)
{
    for (int y = 0; y < 600; y++)
    {
        for (int x = 0; x < 800; x++)
        {
            my_mlx_pixel_put(data, x, y, color);
        }
    }
}

void draw_rectangle(t_data *data, int x, int y, int width, int height, int color)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            my_mlx_pixel_put(data, x + j, y + i, color);
        }
    }
}

int handle_keypress(int keycode, t_data *data)
{
    static int rect_x = 270; // Initial rectangle position
    static int rect_y = 220;

    if (keycode == 65307) // Escape key (Linux)
	{
        mlx_destroy_window(data->mlx, data->window);
		exit(0);
	}
    if (keycode == 65307) // Escape key (Linux)
    {
        mlx_destroy_window(data->mlx, data->window);
        exit(0);
    }
    else if (keycode == 65361) // Left arrow key
        rect_x -= 10;
    else if (keycode == 65362) // Up arrow key
        rect_y -= 10;
    else if (keycode == 65363) // Right arrow key
        rect_x += 10;
    else if (keycode == 65364) // Down arrow key
        rect_y += 10;

    // Clear the image and redraw the rectangle at the new position
    clear_image(data, 0x00000000); // Black background
    draw_rectangle(data, rect_x, rect_y, 200, 150, 0x0000FF00); // Green rectangle
    mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
    return (0);
}

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->window);
    exit(0);
}

int main()
{
    t_data data;

    data.mlx = mlx_init();
    data.window = mlx_new_window(data.mlx, 800, 600, "Animation");
    data.image = mlx_new_image(data.mlx, 800, 600);
    data.addr = mlx_get_data_addr(data.image, &data.bits_per_pixel,
                                  &data.line_length, &data.endian);

    draw_rectangle(&data, 270, 220, 200, 150, 0x0000FF00);
    mlx_put_image_to_window(data.mlx, data.window, data.image, 0, 0);

	mlx_key_hook(data.window, handle_keypress, &data);
	mlx_hook(data.window, 17, 0, close_window, &data);

    mlx_loop(data.mlx);

	return (0);
}
