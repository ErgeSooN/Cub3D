/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:11:13 by ayaman            #+#    #+#             */
/*   Updated: 2023/09/11 14:41:32 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx/mlx.h"
# include "../Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>

# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1

# define FLOOR 0
# define CEILING 1

# define MAX_FD 256

# define TEX_W 64
# define TEX_H 64
# define SCREEN_W 1280
# define SCREEN_H 720

# define BUFFER_SIZE 1024

enum e_key {
	KEY_ESC = 53,
	KEY_EVENT_PRESS = 2,
	KEY_EVENT_RELEASE = 3,
	KEY_EVENT_EXIT = 17,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_LEFT = 123,
	KEY_RIGHT = 124
};

enum e_dir {
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3
};

typedef struct s_node	t_node;

typedef struct s_node
{
	char	*map;
	t_node	*next;
}	t_node;

typedef struct s_maplist
{
	int			size;
	t_node		*head;
	t_node		*tail;
}	t_maplist;

typedef struct s_ray
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}	t_ray;

typedef struct s_img
{
	void		*img;
	int			*data;
	int			bpp;
	int			img_width;
	int			img_height;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			**buf;
	int			**texture;
	char		**map;
	int			map_width;
	int			map_height;
	int			key_a;
	int			key_w;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
	int			player;
	int			color_flag;
	int			dir_flag;
	int			pos_flag;
	int			floor;
	int			ceiling;
	double		msws;
	double		msad;
	t_img		img;
	t_ray		ray;
	t_maplist	*list;
}	t_game;

typedef struct s_calc
{
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart; 
	int			drawend;
	int			texnum;
	double		wallx;
	int			texx;
	int			texy;
	double		step;
	double		texpos;
}	t_calc;

/*
**	get_next_line.c
*/
int			get_next_line(int fd, char **line);
/*
**	ft_strjoin_free.c
*/
char		*ft_strjoin_free(char *s1, char *s2);
/*
**	init.c
*/
void		init_game(t_game *game);
void		init_map(t_game *game);
/*
**	key_press.c
*/
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		player_move(t_game *game);
/*
**	list.c
*/
t_maplist	*create_list(void);
t_node		*create_node(char *line);
void		add_node(t_maplist *list, t_node *node);
/*
**	parse.c
*/
void		check_arg(int argc, char **argv, t_game *game);
void		load_texture(t_game *game, int dir, char *path);
/*
**	parse_map.c
*/
void		parse_map(char *line, t_game *game);
void		parse_last(t_game *game, char *line);
/*
**	parse_color.c
*/
void		get_background_color(char *line, t_game *game, int flag);
/*
**	get_texture.c
*/
int			get_textures(char *line, t_game *game);
/*
**	get_map_game.c
*/
void		dup_map(t_game *game);
void		get_map_game(t_game *game);
/*
**	player_position.c
*/
void		player_position(t_game *game, int i, int j);
/*
**	ray.c
*/
void		init_dda(t_game *game, t_calc *calc);
void		perform_dda(t_game *game, t_calc *calc);
void		start_ray(int x, t_game *game, t_calc *calc);
/*
**	texture.c
*/
void		init_wall_texture(t_game *game, t_calc *calc);
void		input_wall_texture(int x, t_game *game, t_calc *calc);
/*
**	error.c
*/
void		exit_err(char *err_msg);
void		system_err(char *err_msg);
void		free_exit_err(char **str, char *err_msg);
int			free_return_err(char **str);
/*
**	utils.c
*/
int			ft_splitlen(char **str);
void		free_double_char(char **str);
void		free_list(t_game *game);
void		deinitialize(t_game *game);

/* utils2.c */
void		key_leftright(t_game *game);

#endif