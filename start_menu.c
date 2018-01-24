/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrusu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:43:54 by alrusu            #+#    #+#             */
/*   Updated: 2017/05/16 17:16:08 by alrusu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			start_menu(t_fractol *f)
{
	static int	boolean;

	boolean = 0;
	if (!boolean)
	{
		mlx_string_put(f->mlx, f->win, WIN_WID / 2 - 50, WIN_HGT / 2 - 100,
				0xFFFFFFFF, "WELCOME!");
		mlx_string_put(f->mlx, f->win, WIN_WID / 2 - 150, WIN_HGT / 2 - 75,
				0xFFFFFFFF, "fract'ol implemented by alrusu");
		mlx_string_put(f->mlx, f->win, WIN_WID / 2 - 200, WIN_HGT / 2 - 50,
				0xFFFFFFFF, "Arrow keys - move, F - pause julia's set");
		mlx_string_put(f->mlx, f->win, WIN_WID / 2 - 200, WIN_HGT / 2 - 25,
				0xFFFFFFFF, "E - random palette, 1-4 - selecet palette");
		mlx_string_put(f->mlx, f->win, WIN_WID / 2 - 125, WIN_HGT / 2,
				0xFFFFFFFF, "Mouse wheel - zoom in/out");
		mlx_string_put(f->mlx, f->win, WIN_WID / 2 - 70, WIN_HGT / 2 + 25,
				0xFFFFFFFF, "ESC - Quit");
		mlx_string_put(f->mlx, f->win, WIN_WID / 2 - 130, WIN_HGT / 2 + 50,
				0xFFFFFFFF, "Press any key to continue");
		boolean = 1;
	}
}
