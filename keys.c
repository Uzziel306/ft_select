/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:46:49 by asolis            #+#    #+#             */
/*   Updated: 2017/07/27 19:57:25 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			read_key(t_sct *f)
{
	long		key;
	int			refresh;

	key = 0;
	while ((read(0, &key, 8)) != 0)
	{
		refresh = 1;
		if (key == KEY_BSP || key == KEY_DEL || key == KEY_RESET)
			key_del_res(f, key);
		else if (key == KEY_UP || key == KEY_DOWN ||
				key == KEY_LEFT || key == KEY_RIGHT)
			key_up_down(f, key);
		else if (key == KEY_SPC || key == K_S || key == K_D || key == K_R)
			key_space(f, key);
		else if (key == KEY_ENTER)
			return_values(f);
		else if (key == KEY_STAR || key == KEY_MINUS)
			f->menu = (f->menu) ? 0 : 1;
		else if (key == KEY_ESC)
			exit_esc();
		else
			refresh = 0;
		(refresh) ? window_validation(0) : 0;
		key = 0;
	}
}

void			key_left_right(t_sct *f, long key)
{
	int			tmp;

	tmp = f->cursor;
	if (key == KEY_RIGHT)
	{
		if ((tmp + f->win_y) < f->tata)
			f->cursor = (tmp + f->win_y);
	}
	else if (key == KEY_LEFT)
	{
		if ((tmp - f->win_y) < f->arg_height && (tmp - f->win_y) >= 0)
			f->cursor = (tmp - f->win_y);
	}
}

void			key_up_down(t_sct *f, long key)
{
	if (key == KEY_DOWN)
	{
		if (f->cursor == (f->tata - 1))
			f->cursor = 0;
		else if (f->cursor < f->arg_height)
			f->cursor += 1;
	}
	else if (key == KEY_UP)
	{
		if (f->cursor == 0)
			f->cursor = (f->tata - 1);
		else
			f->cursor -= 1;
	}
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		key_left_right(f, key);
}

void			key_space(t_sct *f, long key)
{
	if (key != KEY_SPC)
		key_s_d_r(f, key);
	else
	{
		key++;
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
}

void			key_del_res(t_sct *f, long key)
{
	int			i;

	i = -1;
	if (key == KEY_DEL || key == KEY_BSP)
	{
		ft_arr_remove_nth(f->cursor, f->objects, sizeof(char *), f->arg_height);
		ft_arr_remove_nth(f->cursor, f->select, sizeof(int), f->arg_height);
		key_up_down(f, KEY_DOWN);
		f->del += 1;
		f->tata -= 1;
		if (f->tata == 0)
			exit_esc();
	}
	else if (key == KEY_RESET)
	{
		while (++i <= f->arg_height)
			f->select[i] = 0;
		f->cursor = 0;
	}
}
