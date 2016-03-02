/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:10:12 by avella            #+#    #+#             */
/*   Updated: 2016/02/03 16:10:47 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_line	*give_line(float xi, float yi, float xf, float yf)
{
	t_line *line;

	line = (t_line *)malloc(sizeof(t_line) * 12);
	line->x = xi;
	line->y = yi;
	line->dx = xf - xi;
	line->dy = yf - yi;
	line->xinc = (line->dx > 0) ? 1 : -1;
	line->yinc = (line->dy > 0) ? 1 : -1;
	line->dx = abs(line->dx);
	line->dy = abs(line->dy);
	return (line);
}

t_line	*first_while(t_line *line)
{
	line->x += line->xinc;
	line->cumul += line->dy;
	if (line->cumul >= line->dx)
	{
		line->cumul -= line->dx;
		line->y += line->yinc;
	}
	return (line);
}

t_line	*second_while(t_line *line)
{
	line->y += line->yinc;
	line->cumul += line->dx;
	if (line->cumul >= line->dy)
	{
		line->cumul -= line->dy;
		line->x += line->xinc;
	}
	return (line);
}

t_line	*norme_line(t_line *line)
{
	line->cumul = line->dy / 2;
	line->i = 1;
	return (line);
}

void	draw_line_on_img(t_img *myimg, t_temp *temp, int color)
{
	t_line *line;

	line = give_line(temp->x1, temp->y1, temp->x2, temp->y2);
	my_pixel_put_to_image(myimg, line->x, line->y, color);
	if (line->dx > line->dy)
	{
		line->cumul = line->dx / 2;
		line->i = 1;
		while (line->i <= line->dx)
		{
			line = first_while(line);
			my_pixel_put_to_image(myimg, line->x, line->y, color);
			line->i++;
		}
	}
	else
	{
		line = norme_line(line);
		while (line->i <= line->dy)
		{
			line = second_while(line);
			my_pixel_put_to_image(myimg, line->x, line->y, color);
			line->i++;
		}
	}
}
