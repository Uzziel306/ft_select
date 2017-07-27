/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 21:16:19 by asolis            #+#    #+#             */
/*   Updated: 2017/07/26 21:16:20 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_arr_remove_nth(int nth, void *array, size_t size, int len)
{
	unsigned char	*elem;

	elem = (((unsigned char *)array) + (nth * size));
	ft_memmove((void *)elem, (void *)(elem + size), (len - nth - 1) * size);
}

void		ft_putcharn_fd(int c, int n, int fd)
{
	while (n)
	{
		ft_putchar_fd(c, fd);
		n--;
	}
}

t_sct		*get_t_sect(t_sct *f)
{
	static t_sct *h = NULL;

	if (f)
		h = f;
	return (h);
}

int			max_width(char **mtx)
{
	int		max;
	int		i;
	int		tmp;

	max = 0;
	i = -1;
	while (mtx[++i])
	{
		if (max < (tmp = (int)ft_strlen(mtx[i])))
			max = tmp;
	}
	return (max);
}

void		exit_esc(void)
{
	t_sct	*f;

	f = get_t_sect(NULL);
	ft_memdel((void**)&f->select);
	ft_termcmd("te");
	ft_termcmd("ve");
	exit (3);
}
