/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrusu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:13:10 by alrusu            #+#    #+#             */
/*   Updated: 2017/05/16 18:13:19 by alrusu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define SEL_PAL f->palette[f->selected_palette]
#define PAL_CNT f->palette[f->selected_palette].count

int			get_color(double mu, t_fractol *f)
{
	t_color	clr;
	double	index;
	double	adjust;

	if (mu < 0)
		mu = 0;
	index = mu / f->itterations;
	adjust = fmod(index, 1.0f / (double)(PAL_CNT)) * (double)(PAL_CNT - 1);
	clr = clerp(SEL_PAL.colors[(int)(index * (PAL_CNT - 1)) + 1],
		SEL_PAL.colors[(int)(index * (PAL_CNT))],
		(int)(adjust + 1) - adjust);
	return ((clr.r << 16) + (clr.g << 8) + clr.b);
}

t_color		clerp(t_color c1, t_color c2, double p)
{
	t_color	c;

	c.r = ft_lerpi((int)c1.r, (int)c2.r, p);
	c.g = ft_lerpi((int)c1.g, (int)c2.g, p);
	c.b = ft_lerpi((int)c1.b, (int)c2.b, p);
	return (c);
}

double		cmagn(t_complex c)
{
	return ((c.a * c.a) + (c.b * c.b));
}

void		cadd(t_complex *c1, t_complex c2)
{
	c1->a += c2.a;
	c1->b += c2.b;
}

void		csqr(t_complex *c)
{
	double	tmp;

	tmp = (c->a * c->a) - (c->b * c->b);
	c->b = 2.0 * c->a * c->b;
	c->a = tmp;
}
