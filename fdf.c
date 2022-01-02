#include "fdf.h"
#include "mlx/mlx.h"
/*int map_parse()
{

}*/

int main(void)
{
    void    *mlx_ptr;
    void    *win_ptr;

    ft_putchar_fd('c', 1);
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 500, 500, "FdF");
    mlx_loop(mlx_ptr);
}