/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrusu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:30:19 by alrusu            #+#    #+#             */
/*   Updated: 2017/05/16 18:30:20 by alrusu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		pixel_put(t_fractol *f, int x, int y, int color)
{
	int		offset;

	offset = x * 4;
	offset += y * f->img.sline;
	*(int*)(f->img.str + offset) = color;
}
