#include "ft_select.h"

int		ft_strlen_val(char *str, t_sct *f)
{
	int		len;
	int		diff;

	len = (int)ft_strlen(str);
	diff = (f->arg_width + 3) - len;
	return (len + diff);
}

int			ft_putitem_fd(char *str, t_sct *f, int i)
{
	if (i == f->cursor)
		ft_termcmd("us");
	if (f->select[i] == 1)
		ft_termcmd("so");
	ft_putstr_fd(f->objects[i], 2);
	ft_termcmd("ue");
	ft_termcmd("se");
	ft_putcharn_fd(' ',f->arg_width - (int)ft_strlen(f->objects[i]) + 3 ,2);
	return ((int)ft_strlen(f->objects[i]) + 3);

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
}

int			window_sizevalidation(t_sct *f)
{
	int		i;
	int		huevos;
	int		len;

	i = 0;
	huevos = 0;
	len = 0;
	while (huevos <= f->win_y && f->objects[i])
	{
		len += ft_strlen_val(f->objects[huevos], f);
		while (42)
		{
			i += f->win_y;
			if (i > f->arg_height)
				break ;
			else if(f->objects[i])
				len += ft_strlen_val(f->objects[huevos], f);
		}
		if ((len - 3) > f->win_x)
			return (0);
		len = 0;
		huevos++;
		i = huevos;
	}
	return (1);
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