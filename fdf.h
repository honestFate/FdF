/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:21:52 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/23 23:06:24 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "mlx/mlx.h"
# define MAP_SIZE 10

typedef struct s_angles
{
	double	x;
	double	y;
	double	z;
}				t_angl;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_fdf {
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	t_angl	***map;
	t_angl	*shift;
	t_angl	*rotate;
	int		projection;
	float	scale;
}				t_fdf;

typedef struct s_line
{
	t_angl		*start;
	t_angl		*end;
	int			dx;
	int			dy;
	t_img		*img;
	int			color;
}				t_line;

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		i_part(double x);
double	f_part(double x);
void	swap(t_angl *s, t_angl *e);
void	put_pixel_img(t_img *data, int x, int y, int color);
t_angl	*angl_copy(t_angl *p);
void	add_shift(t_angl *p, t_angl *shift);
void	add_rotate(t_angl *p, t_angl *rotate);
void	to_iso(t_angl *p);
t_angl	*point_move(t_angl *point, t_fdf *fdf);
t_angl	*get_center(t_angl ***map);
double	get_map_scale(t_angl *center);
float	get_peak(t_angl ***map);
float	get_lowest(t_angl ***map);
int		ft_any_digit(char **s);
void	map_clear(char ***map);
void	parsedmap_clear(t_angl ***map);
int		get_line_len(char **map);
char	***ft_resize_arr(char ***map, int map_current_size);
char	***ft_putline_map(char ***map, char *line, int i);
char	***ft_get_map(int fd);
void	fill_angl_line(char ***map, t_angl ***map_parsed, int i);
t_angl	***ft_map_parse(char ***map);
void	map_chech(char ***map);
void	set_to_center(t_angl ***map, t_angl *center);
void	set_size(t_angl *point, double line_len);
void	rotate_point(t_angl *point, int angle, int ax);
void	print_simple_linex(t_angl *start_point, t_angl *end_point,
			t_img *img, int color);
void	print_simple_liney(t_angl *start_point, t_angl *end_point,
			t_img *img, int color);
void	print_line_v(t_line *line);
void	print_line_h(t_line *line);
void	print_line(t_line *line);
void	print_two_line(t_fdf *fdf, t_line *line, int i, int j);
void	print_map(t_fdf *fdf);
void	choose_key_action2(int key, t_fdf *info);
void	choose_key_action(int key, t_fdf *info);
int		key_hook(int key, t_fdf *info);
int		mouse_press(int key, int x, int y, t_fdf *info);
int		choose_color(float z);

#endif