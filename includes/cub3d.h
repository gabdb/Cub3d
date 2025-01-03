/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:55:51 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/23 18:26:42 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// LIBRARIES

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <X11/keysym.h> //pas sur a 100%
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>



// STRUCTURES

typedef struct s_data {
    void    *mlx;
    void    *window;
    void    *image;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_data;



// FONCTIONS



#endif