/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:55:51 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/21 18:49:57 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// LIBRARIES

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <X11/keysym.h> //pas sur a 100%
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <sys/types.h>

# define WINDOW_HEIGHT 1000
# define WINDOW_LENGTH 1500
# define GRAY 0x808080
# define RED 0xFF0000
# define DARK_RED 0x880000
# define BLUE 0X444FF
# define DARK_BLUE 0X0000B9
# define GREEN 0X00FF00
# define DARK_GREEN 0X00CA00
# define PI 3.14159265


// STRUCTURES

typedef struct s_keys {
	int	forward;
	int	backward;
	int	left;
	int	right;
	int	rotate_left;
	int	rotate_right;
}				t_keys;

typedef struct s_raycast {
	double	pl_x_pos;
	double	pl_y_pos;
	double	dir_x;     // Player's direction vector X
	double	dir_y;     // Player's direction vector Y
	double	plane_x;   // Camera plane X (for FOV projection)
	double	plane_y;   // Camera plane Y
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
}				t_raycast;

typedef struct  s_player {
	double		x_pos;         // Player's X position (continuous, not limited to grid cells)
	double		y_pos;         // Player's Y position
	double		dir_x;     // Player's direction vector X
	double		dir_y;     // Player's direction vector Y
	double		plane_x;   // Camera plane X (for FOV projection)
	double		plane_y;   // Camera plane Y
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	float		rot_speed;
	t_raycast	*ray;
}               t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;


typedef struct s_mlx {
    void    	*mlx;
    void    	*window;
    void    	*image;
    char    	*addr;
    int     	bits_per_pixel;
    int     	line_length;
    int     	endian;
	char		**map;
	int			num_rows; //temporaire, map sera pas forcément carrée
	double		last_frame;
	t_player	*player;
	t_keys		*keys;
	t_img		textures[4]; //pr linstant juste 1, pr tester brick
    //...
} t_mlx;

/* ********* */
/* FONCTIONS */
/* ********* */

// MLX
void    my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void	handle_mlx(t_mlx *data);
void 	clear_image(t_mlx *data, int color);

// PARSING
int		parsing(int fd, char *line, int num_rows);

// MAP
char	**make_map(int num_rows);

// UTILS
int		num_rows(void);
int		round_float(float nb);
double	get_time_in_seconds(void);

// SAFE_UTILS
void	*safe_malloc(size_t size);
char	*safe_strdup(char *str);

// TOP-DOWN
void 	draw_grid(t_mlx *data, int num_rows);
int		render(t_mlx *data);

// PLAYER
t_player	*init_player(t_mlx *data);
int			check_wall(t_mlx *data, float x, float y);

// RAYS
void	draw_rays(t_mlx *data, t_player *player);

// RAYCASTING
void init_raycast(t_player *player);
void render_3d(t_mlx *data); //CHATGPT, attention juste checker

// SMOOTH MOVE
t_keys	*init_keys(void);
int		key_press(int keycode, t_mlx *data);
int		key_release(int keycode, t_mlx *data);
int		game_loop(t_mlx *data);

// TEXTURES
t_img	*init_textures(void);
void	load_textures(t_mlx *data);
int 	get_texture_pixel(t_img *texture, int x, int y);

#endif