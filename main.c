/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrusu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:23:38 by alrusu            #+#    #+#             */
/*   Updated: 2017/05/16 18:29:23 by alrusu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int				usage_err(char *av)
{
	ft_putstr("fractol: illegal option ");
	ft_putendl(av);
	ft_putendl(USAGE_ERROR);
	exit(1);
}

void			rand_palette(t_fractol *f)
{
	f->palette[4] = (t_palette){7, {
		{rand() % 255, rand() % 255, rand() % 255},
			{rand() % 255, rand() % 255, rand() % 255},
			{rand() % 255, rand() % 255, rand() % 255},
			{rand() % 255, rand() % 255, rand() % 255},
			{rand() % 255, rand() % 255, rand() % 255},
			{rand() % 255, rand() % 255, rand() % 255},
			{rand() % 255, rand() % 255, rand() % 255}}};
	f->selected_palette = 4;
}

void			init_palettes(t_fractol *f)
{
	f->palette[0] = (t_palette){5, {{149, 0, 216}, {0, 128, 128}, {163, 255, 0},
		{51, 105, 39}, {186, 24, 24}}};
	f->palette[1] = (t_palette){7, {{167, 162, 188}, {197, 165, 141},
		{248, 19, 25}, {206, 75, 24}, {140, 90, 226}, {173, 195, 138},
		{227, 71, 248}}};
	f->palette[2] = (t_palette){7, {{129, 34, 239}, {54, 66, 152},
		{89, 149, 162}, {128, 115, 249}, {170, 153, 136}, {61, 140, 33},
		{134, 41, 138}}};
	f->palette[3] = (t_palette){7, {{4, 4, 70}, {221, 61, 80}, {182, 55, 89},
		{215, 36, 89}, {92, 34, 100}, {36, 227, 101}, {155, 234, 166}}};
}

void			init_struct(t_fractol *f)
{
	f->itterations = 45;
	f->x = 0;
	f->y = 0;
	f->zoom = 1;
	f->selected_palette = 1;
	f->hooking = 0;
	f->jul = 1;
	f->can_draw = 0;
	init_palettes(f);
	f->img.img = mlx_new_image(f->mlx, WIN_WID, WIN_HGT);
	f->img.str = mlx_get_data_addr(f->img.img, &f->img.bpp, &f->img.sline,
			&f->img.endian);
}

int				main(int ac, char **av)
{
	t_fractol	f;

	(ac != 2) ? usage_err("") : (void)'f';
	if (!ft_strcmp(str_to_lower(av[1]), "mandelbrot"))
		f.draw = &mandelbrot;
	else if (!ft_strcmp(str_to_lower(av[1]), "julia"))
		f.draw = &julia;
	else if (!ft_strcmp(str_to_lower(av[1]), "newton"))
		f.draw = &newton;
	else
		usage_err(av[1]);
	f.mlx = mlx_init();
	f.win = mlx_new_window(f.mlx, WIN_WID, WIN_HGT, "fract'ol");
	init_struct(&f);
	start_menu(&f);
	mlx_key_hook(f.win, input, &f);
	if (f.can_draw)
		mlx_expose_hook(f.win, expose_hook, &f);
	mlx_mouse_hook(f.win, mouse_hook, &f);
	mlx_hook(f.win, MOTION_NOTIFY, PTR_MOTION_MASK, julia_mouse, &f);
	mlx_loop(f.mlx);
	return (0);
}
