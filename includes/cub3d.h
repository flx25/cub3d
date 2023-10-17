/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:46:57 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/17 11:36:17 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>

# ifdef __APPLE__
#  include "../libmlx_opengl/mlx.h"
#  include "keycodes_macos.h"
# else
#  include "../libmlx_linux/mlx.h"
#  include "keycodes_linux.h"
#  include <X11/Xlib.h>
# endif
# include "../libft/libft.h"

// Settings
# define WIN_NAME		"Cub3D"
# define WIN_WIDTH		1800
# define WIN_HEIGHT		900
# define MOVE_SPEED		600
# define ROTATE_SPEED	500
# define MOUSE_SPEED	200
# define NPC_COUNT		10
# define NPC_SPEED		10
# define HEALTH			100
# define DAMAGE			10
# define HEALTH_BAR_LEN	300
# define BUFFER_SIZE	32

// Types
typedef struct s_img
{
	void			*img;
	char			*data;
	int				line_size;
	int				endian;
	int				width;
	int				height;
	int				bpp;
	int				mask;
}					t_img;
typedef struct s_anim
{
	t_list			*frames;
	t_list			*curr_frame;
}					t_anim;
typedef enum e_pl_type
{
	FIRE,
	NPC
}					t_pl_type;
typedef struct s_pl
{
	t_anim			anim;
	t_pl_type		type;
	bool			dead;
	double			pos[2];
	double			dir[2];
	int				scale;
	int				v_move;
}					t_pl;
typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	t_img			maze;
	t_img			n_tex;
	t_img			s_tex;
	t_img			w_tex;
	t_img			e_tex;
	t_list			*sp;
	t_anim			door_a;
	t_anim			pl_a;
	t_anim			fire_a;
	t_anim			lose_a;
	t_anim			win_a;
	double			z_buf[WIN_WIDTH];
}					t_mlx;
typedef struct s_raycast
{
	double			ray_dir_x;
	double			ray_dir_y;
	double			d_dst_x;
	double			d_dst_y;
	double			s_dst_x;
	double			s_dst_y;
	double			perp_d;
	char			wall;
	int				side;
	int				used;
	int				open;
	t_img			tex;
}					t_raycast;
typedef struct s_sprite
{
	double			tr_x;
	double			tr_y;
	int				st_x;
	int				st_y;
	int				en_x;
	int				en_y;
	int				sp_hei;
	int				sp_wid;
	int				v_move;
	int				sp_s_x;
}					t_sprite;
typedef struct s_mouse
{
	bool			mouse_pressed;
	bool			ch;
	bool			lock;
}					t_mouse;
typedef struct s_kbrd
{
	int				fb;
	int				rl;
	int				rr;
	int				f;
}					t_kbrd;
typedef struct s_cub3d
{
	t_mlx			mlx;
	t_mouse			m;
	t_kbrd			k;
	t_raycast		raycst;
	t_raycast		door_raycast;
	t_sprite		sp;
	char			**map;
	unsigned int	player_pos[2];
	char			player_dir;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	char			*ceiling_color_str;
	char			*floor_color_str;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	double			dir[2];
	double			pos[2];
	double			plane[2];
	int				c;
	int				health;
	int				win_lose;
	int				speed;
}					t_cub3d;

typedef struct s_minimap
{
	int				i;
	int				j;
	int				x;
	int				y;
}					t_minimap;

// Parser utils
int					parser(char *argv1, t_cub3d *cub3d);
char				*readmap(char *map);
char				*get_next_line(int fd);
char				*ft_gnl_strjoin(char *str, char *buff);
char				*ft_gnl_strchr(char *c, int i);
int					ft_strlen_longestline(char *str);
char				**makemapmatrix(char *map, int msize);
void				free_parse_error(t_cub3d *cub3d);
int					ft_strlen_longestline(char *str);
int					checkmapenclosure(char *map, t_cub3d *cub3d);
uint32_t			pack_rgb(uint8_t r, uint8_t g, uint8_t b);
char				*copywithoutspaces(char *str);
int					lengtonl(char *str);
void				free_parse_error(t_cub3d *cub3d);
void				freesplit(char **str);
int					checkmap(char *map, t_cub3d *cub3d);
int					checksingleentrance(char *map);
int					checkmapchars(char *map);
char				*get_cut_map(char *argv1);
int					convertcolors(t_cub3d *cub3d);
void				getstartpoint(t_cub3d *cub3d);
void				freematrix(char **matrix);
int					ft_strlen_space(char *s);
int					check_cf(char *str);
int					checkunknowntokens(char *argv1);
int					multicommas(char *str);
char				*return_pointer(char *file);
int					checkadditionalnl(char *map);

// Init
void				init_mlx(t_cub3d *cub3d);
void				init_hooks(t_cub3d *cub3d);
int					init_pos(t_cub3d *cub3d);
int					load_texture(t_cub3d *cub3d, t_img *img, char *path);
// Draw
unsigned int		get_img_color(t_img img, int x, int y);
void				draw_fullscreen(t_cub3d *cub3d, t_img *img, int fill_clr);
void				drw_pnt(t_img *img, int x, int y, int clr);
void				draw_sprite(t_cub3d *cub3d, t_pl *pl);
void				drawminimap(t_cub3d *cub3d);
void				draw_all(t_cub3d *cub3d);
// Raycaster utils
void				calc_side_helper(t_cub3d *cub3d, int step_x, int step_y);
void				draw_x(t_cub3d *cub3d, int x, int door);
void				draw_floor_ceil(t_cub3d *cub3d);
void				copy_raycast(t_cub3d *cub3d);
void				raycasting(t_cub3d *cub3d);
// Navigate
void				rotate(t_cub3d *cub3d, double angleDelta);
// Hooks
int					ft_close(void *cub3d_ptr);
int					loop_hook(void *cub3d_ptr);
int					key_press(int keycode, void *cub3d_ptr);
int					key_release(int keycode, void *cub3d_ptr);
int					mouse_move(int x, int y, void *cub3d_ptr);
int					mouse_press(int keycode, int x, int y, void *cub3d_ptr);
int					mouse_release(int keycode, int x, int y, void *cub3d_ptr);
void				mouse_move_center(t_cub3d *cub3d);
// Animation
int					add_frame(t_cub3d *cub3d, t_anim *anim, char *path);
int					init_anim(t_cub3d *cub3d);
void				exec_anims(t_cub3d *cub3d);
void				play_anim(t_anim *anim);
// Doors
void				manage_doors(t_cub3d *cub3d);
int					load_door_anim(t_cub3d *cub3d);
// Player
void				check_win_lose(t_cub3d *cub3d);
void				draw_lose(t_cub3d *cub3d);
void				draw_win(t_cub3d *cub3d);
int					load_lose_anim(t_cub3d *cub3d);
int					load_win_anim(t_cub3d *cub3d);
// Non-player character
bool				move_available(t_cub3d *cub3d, t_pl *pl,
						double pl_w, double d);
int					load_npc_anim(t_cub3d *cub3d);
void				manage_npc(t_cub3d *cub3d, t_pl *pl);
void				rand_pos(t_cub3d *cub3d, t_pl *pl);
void				create_npcs(t_cub3d *cub3d);
// Fireball
void				init_fireball(t_cub3d *cub3d);
int					load_fireball_anim(t_cub3d *cub3d);
void				manage_fire(t_cub3d *cub3d, t_pl *pl);
bool				check_dist(double pos1[2], double pos2[2], double dist);
// Terminate
void				free_data(t_cub3d *cub3d);
t_list				*ft_lstcut(t_list **lst, void *cnt);
#endif
