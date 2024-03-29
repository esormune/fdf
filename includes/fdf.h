/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:10:44 by esormune          #+#    #+#             */
/*   Updated: 2021/03/22 18:43:24 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx/mlx.h"
# include "../libft/includes/libft.h"
# define WIN_X		800
# define WIN_Y		800
# define WIN_HALF	400
# define SQUARES	16
# define SQ_SIZE	200
# define SQ_PR		4
# define WIN_MAX	640000
# define WHITE		0XFFFFFF
# define GREY		0X757575
# define BLACK		0X000000
# define RED		0XFF0000
# define BLUE		0X0000FF
# define GREEN		0X00FF00
# define YELLOW		0XFFFF00
# define ORANGE		0XFF5500
# define PURPLE		0X8700FF
# define MAGENTA	0XFF00FF
# define PINK		0XFF00E4
# define TURQUOISE	0X00FFEC

typedef struct		s_coord
{
	float			x;
	float			y;
	float			z;
	float			z_orig;
	int				colour;
	int				r;
	int				g;
	int				b;
	int				row_len;
}					t_coord;

typedef struct		s_floor
{
	int				colour;
	int				change;
	int				sleep;
	int				inc;
	int				black;
	t_coord			start;
	t_coord			end;
}					t_floor;

typedef struct		s_map
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*img;
	int				endian;
	int				size_line;
	int				bpp;
	int				scale;
	float			zoom;
	t_coord			**coord;
	int				y_size;
	int				x_start;
	int				x_start_orig;
	int				y_start;
	int				y_start_orig;
	int				z_start;
	int				max_width;
	int				view;
	float			z_scale;
	int				colour_arr;
	int				colour;
	int				bg_arr;
	int				bg;
	int				party;
	int				party_scale;
	int				r;
	int				g;
	int				b;
	int				rot;
	int				depth;
	int				max_z;
	int				min_z;
	int				draw;
	int				i;
	t_floor			tiles[SQUARES];
}					t_map;

int					fdf_init(t_map *map);
int					fdf_exit(t_map *map);
int					valid_map(int fd);
t_map				*map_init(int fd, int size);
t_coord				**parse_map(int fd, int size, t_map *orig);
void				reset_img(t_map *map, int colour);
void				reset_map(t_map *map);
int					draw_map(t_map *map);
float				draw_step(float dx, float dy);
void				draw_create(t_map *map);
int					fdf_keys(int key, t_map *map);
void				morph_view(float *x, float *y, float z, int i);
void				morph_rotate(t_coord *p, t_coord center, float angle);
void				morph_scale(t_map *map, t_coord *start, t_coord *end);
void				party_init(t_map *map);
void				party_mode(t_map *map);
void				party_start(t_map *map);
void				floor_create(t_map *map);
void				floor_stripe(t_map *map);
void				square_draw(t_map *map, t_coord start,
						t_coord end, int colour);
int					colour_get(t_coord *p, t_map *map);
void				colour_map(int key, t_map *map);
void				colour_background(t_map *map);
void				colours_party(t_map *map);
void				depth_draw_line(t_map *map, t_coord start, t_coord end);
void				depth_key(t_map *map);
void				event_projection(t_map *map);
void				event_zoom(int key, t_map *map);
void				event_move(int key, t_map *map);
void				event_z_scale(int key, t_map *map);
void				event_rotate(int key, t_map *map);
void				text_put(t_map *map);
int					die(char *reason);
char				*die_null(char *reason);
t_coord				**die_struct(char *reason);
void				free_tcoord_array(t_coord **arr);

#endif
