/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrusu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:29:22 by alrusu            #+#    #+#             */
/*   Updated: 2017/05/15 18:49:25 by alrusu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int		expose_hook(t_fractol *f)
{
	mlx_clear_window(f->mlx, f->win);
	f->draw(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img.img, 0, 0);
	return (1);
}

void	translate(t_fractol *f, int key)
{
	mlx_clear_window(f->mlx, f->win);
	if (key == UP)
		f->y -= TRANSLATE_DIST / f->zoom;
	else if (key == DOWN)
		f->y += TRANSLATE_DIST / f->zoom;
	else if (key == LEFT)
		f->x -= TRANSLATE_DIST / f->zoom;
	else if (key == RIGHT)
		f->x += TRANSLATE_DIST / f->zoom;
}

int		mouse_hook(int key, int x, int y, t_fractol *f)
{
	if (key == SCROLL_UP)
	{
		f->scroll_count++;
		f->itterations += (f->scroll_count >= SCROLL_LIMIT) ? 1 : 0;
		if (f->scroll_count % 5 || f->scroll_count)
		{
			f->x += ((x - WIN_WID / 2) / (ZOOM)) / (f->zoom * 2000);
			f->y += ((y - WIN_HGT / 2) / (ZOOM)) / (f->zoom * 2000);
			f->zoom *= 1.05;
		}
	}
	else if (key == SCROLL_DOWN)
	{
		f->scroll_count++;
		f->zoom /= 1.05;
		f->itterations -= (f->scroll_count >= SCROLL_LIMIT) ? 1 : 0;
	}
	(f->scroll_count % 5) ? expose_hook(f) : 0;
	f->scroll_count *= (f->scroll_count >= SCROLL_LIMIT) ? 0 : 1;
	return (0);
}

int		input(int key, t_fractol *f)
{
	if (key == UP || key == LEFT || key == RIGHT || key == DOWN)
		translate(f, key);
	else if (key == F)
		f->jul = !f->jul;
	else if (key == ESC)
		exit(1);
	else if (key == E)
		rand_palette(f);
	else if (key >= 18 && key <= 21)
		f->selected_palette = key - 18;
	f->can_draw = (f->can_draw == 0) ? 1 : f->can_draw;
	init_palettes(f);
	expose_hook(f);
	return (0);
}
