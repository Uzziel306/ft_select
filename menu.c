/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/28 20:26:56 by asolis            #+#    #+#             */
/*   Updated: 2017/07/28 20:26:58 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void				print_just_values(t_sct *f, int color)
{
	int		i;
	int		cont;

	cont = 0;
	i = -1;
	ft_putchar('\n');
	while (f->objects[++i])
	{
		if (f->select[i] == 1)
		{
			ft_printfcolor("%s", f->objects[i], color);
			cont += 1;
			if (cont != f->total_selected)
				ft_putchar(' ');
		}
	}
	ft_putchar('\n');
	ft_putchar('\n');
}

void				tetas2(t_sct *f)
{
	ft_printfcolor("%s", "- Perss 'return' to return t\
		he values selected\n", 92);
	ft_printfcolor("%s", "- Press 'delete' to delete a item of the list\n", 92);
	ft_printfcolor("%s", "- Press 'S' to select all items \n", 92);
	ft_printfcolor("%s", "- Press 'D' to unselect all items\n", 92);
	ft_printfcolor("%s", "- Press 'R' to move the cursor to 0\n", 92);
	ft_printfcolor("%s", "- Press 'ESC' to close the program\n", 92);
	ft_printfcolor("%s", "- Press any key to exit of here...\n\n", 92);
	ft_printfcolor("%s%d%s%d", "WINDOWS SIZE: X: ", 92, f->win_x, 92
		, "  Y: ", 92, f->win_y, 92);
}

void				tetas(t_sct *f)
{
	ft_clrscreen(f->win_y);
	ft_printfcolor("%s"
, " ______ ______   ______  ______  __      ______  ______  ______  \n"
, 92);
	ft_printfcolor("%s"
, "/\\  ___/\\__  _/  \\  ___\\/\\  ___\\/\\ \\    /\\  ___\\/\\  ___\\/\\\
__  _\\ \n", 92);
	ft_printfcolor("%s"
, "\\ \\  __\\/_/\\ \\    \\___  \\ \\  __\\  \\ \\___ \\ \\  __\
\\ \\ \\___\\/_/\\ \\/ \n", 92);
	ft_printfcolor("%s"
, " \\ \\_\\    \\ \\_\\ /  \\_____\\ \\_____\\ \\_____ \\ \\_____\
\\\\_____\\ \\ \\_\\ \n", 92);
	ft_printfcolor("%s\n\n", "  \\/_/     \\/_/  \
\\/_____/\\/_____/\\/_____/\\/_____/\\/_____/   \\/_/\n", 92);
	ft_printfcolor("%s%d\n", "ITEMS SELECTED: ", 44, f->total_selected, 44);
	print_just_values(f, 44);
	ft_printfcolor("%s%d\n\n\n", "ITEMS DELETED: ", 44, f->del, 44);
	ft_printfcolor("%s", "INSTRUCTIONS: \n", 92);
	ft_printfcolor("%s", "- Use the arrows to move the cursor \n", 92);
	ft_printfcolor("%s", "- Press 'space' to selecet/unselect a item \n", 92);
	tetas2(f);
}

void				key_s_d_r(t_sct *f, long key)
{
	int		i;

	i = -1;
	if (key == K_S)
	{
		while (f->objects[++i] != NULL)
			f->select[i] = 1;
	}
	else if (key == K_D)
	{
		while (f->objects[++i] != NULL)
			f->select[i] = 0;
	}
	else if (key == K_R)
		f->cursor = 0;
}
