#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h> //TO DEL
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# define MAP_SIZE 10
# define LINE_LEN 30
typedef struct s_point
{
    double	x;
    double	y;
}               t_point;
typedef struct s_angles
{
    double	x;
    double	y;
    double	z;
}               angl;
typedef struct s_variables
{
    int	angle_x;
	int	angle_y;
	int	angle_z;
    double x;
    double y;
}               var;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data_img;

typedef struct	s_img {
    void    *mlx_ptr;
    void    *win_ptr;
    t_data_img *img;
    angl    ***map;
}				t_img;

int	create_trgb(int t, int r, int g, int b);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);
void    ft_print_map(angl ***map, t_data_img *img);
void	ft_print_line(angl *start, angl *end, t_data_img *img, int color);
void	ft_print_simple_line(angl *start_point, angl *end_point, t_data_img *img, int color);
void	put_pixel_img(t_data_img *data, int x, int y, int color);
void	ft_swap(double *x, double *y);
double	f_part(double x);
int	i_part(double x);
void    ft_set_size(angl ***map, double line_len);
void    ft_rotate_map(angl ***map, int angle, int ax);
void    ft_set_to_point(angl ***map, float x, float y, int sign);
void	ft_print_simple_line(angl *start_point, angl *end_point, t_data_img *img, int color);
void    to_isometric(angl ***map);
void    to_decart(angl ***map);
t_point	*ft_get_center(angl ***map);

#endif