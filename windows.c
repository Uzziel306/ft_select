#include "ft_select.h"

void				ft_putitem_fd(char *str, t_sct *f, int i)
{
	if (i == f->cursor)
		ft_termcmd("us");
	if (f->select[i] == 1)
		ft_termcmd("so");
	ft_putstr_fd(f->objects[i], 2);
	ft_termcmd("ue");
	ft_termcmd("se");
	ft_putcharn_fd(' ',f->arg_width - (int)ft_strlen(f->objects[i]) + 3 ,2);
}

void		print_scren(t_sct *f, int i, int tmp, int huevos)
{
	ft_clrscreen(f->win_y);
	// ft_printfcolor("%s%d\n", "ITEMS SELECTED: ", 44, f->total_selected, 44);
	while (huevos <= f->win_y && f->objects[i])
	{
		ft_cursor_goto(0, huevos);
		ft_putitem_fd(f->objects[huevos], f, huevos);
		while (42)
		{
			i += f->win_y;
			if (i > f->arg_height)
				break ;
			else if(f->objects[i])
				ft_putitem_fd(f->objects[i], f, i);
		}
		huevos++;
		i = huevos;
	}
	// if ()
			// if (i == f->cursor)
			// 	ft_termcmd("us");
			// if (f->select[i] == 1)
			// 	ft_termcmd("so");
			// ft_putstr_fd(f->objects[i], 2);
			// ft_termcmd("ue");
			// ft_termcmd("se");
			// ft_putcharn_fd(' ',f->arg_width - (int)ft_strlen(f->objects[i]) + 3 ,2);
			// printf("\n");
			// printf("%d\n", f->arg_width - (int)ft_strlen(f->objects[i]) + 1);
	// ft_printfbasic("%d\n", f->cursor);
	// ft_printfbasic("%d\n", f->win_y);
}

int			window_sizevalidation(t_sct *f)
{
	int		j;
	int		len;
	j = -1;
	len = 0;
	f->full = f->win_x * f->win_y;

	while (f->objects[++j])
		len += (int)ft_strlen(f->objects[j]) + 3;
	return (len < f->full) ? 1 : 0;
}

void		window_validation(int signum)
{
	t_sct	*f;
	struct winsize win;
	signum++;
	f = get_t_sect(NULL);

	ioctl(STDIN_FILENO, TIOCGWINSZ, &win);
	f->win_x = win.ws_col;
	f->win_y = win.ws_row;
	if (window_sizevalidation(f))
		print_scren(f, 0, 1, 0);
	else
	{
		ft_clrscreen(f->win_y);
		ft_printfcolor("%s", "No space :C\n", 31);
	}
}