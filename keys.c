/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:46:49 by asolis            #+#    #+#             */
/*   Updated: 2017/07/17 18:46:54 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		read_key(t_sct *f)
{
	long	key;
	int		refresh;

	key = 0;
	while ((read(0, &key, 8)) != 0)
	{
		refresh = 1;
		if (key == KEY_BSP || key == KEY_DEL)
			printf("del\n");
		else if (key == KEY_UP || key == KEY_DOWN ||
				key == KEY_LEFT || key == KEY_RIGHT)
			key_up_down(f, key);
		else if (key == KEY_SPC)
			key_space(f, key);
		else if (key == KEY_ENTER)
			return_values(f);
		else if (key == KEY_STAR || key == KEY_MINUS)
			printf("minus\n");
		else if (key == KEY_ESC)
			exit_esc();
		else
			refresh = 0;
		(refresh) ? print_scren(f, 0, 1, -1) : 0;
		key = 0;
	}
}

void		key_up_down(t_sct *f, long key)
{
	if (key == KEY_DOWN)
	{
		if (f->cursor == (f->arg_height - 1))
			f->cursor = 0;
		else if (f->cursor < f->arg_height)
			f->cursor += 1;
	}
	else if (key == KEY_UP)
	{
		if (f->cursor == 0)
			f->cursor = (f->arg_height - 1);
		else
			f->cursor -= 1;
	}
}

static void		key_space(t_sct *f, long key)
{
	if (f->select[f->cursor] == 0)
		{
			f->select[f->cursor] = 1;
			f->total_selected += 1;
		}
	else
	{
		f->select[f->cursor] = 0;
		f->total_selected -= 1;
	}
	key_up_down(f, KEY_DOWN);
}
