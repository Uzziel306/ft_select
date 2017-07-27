#include "ft_select.h"

int		ft_strlen_val(char *str, t_sct *f)
{
	int		len;
	int		diff;

	len = (int)ft_strlen(str);
	diff = (f->arg_width + 3) - len;
	return (len + diff);
}

void			ft_putitem_fd(char *str, t_sct *f, int i)
{
		if (i == f->cursor)
			ft_termcmd("us");
		if (f->select[i] == 1)
			ft_termcmd("so");
		// ft_putchar_fd('[', 2);
		// ft_putnbr_fd(i, 2);
		// ft_putchar_fd(']', 2);
		ft_putstr_fd(f->objects[i], 2);
		ft_termcmd("ue");
		ft_termcmd("se");
		ft_putcharn_fd(' ',f->arg_width - (int)ft_strlen(f->objects[i]) + 3 ,2);
		f->tmp += 1;
}

void		print_scren(t_sct *f, int i, int columna, int huevos)
{
	ft_clrscreen(f->win_y);
	// ft_printfcolor("%s%d\n", "ITEMS SELECTED: ", 44, f->total_selected, 44);
	while (huevos < f->tata && huevos < f->win_y)
	{
		ft_cursor_goto(0, huevos);
		if (((0 * f->win_y) + huevos) < f->tata)
		ft_putitem_fd(f->objects[huevos], f, huevos);
		while (42)
		{
			columna++;
			if ((i = (columna * f->win_y) + huevos) < f->tata)
				ft_putitem_fd(f->objects[i], f, i);
			else
				break ;
		}
		columna = 0;
		huevos++;
	}
}

int			window_sizevalidation(t_sct *f, int i, int huevos, int columna)
{
	int		len;

	len = 0;
	while (huevos < f->tata && huevos < f->win_y)
	{
		if (((0 * f->win_y) + huevos) < f->tata)
		len += ft_strlen_val(f->objects[huevos], f);;
		while (42)
		{
			columna++;
			if ((i = (columna * f->win_y) + huevos) < f->tata)
				len += ft_strlen_val(f->objects[i], f);
			else
				break ;
		}
		if (len > f->win_x)
			return (0);
		len = 0;
		columna = 0;
		huevos++;
	}
	if (huevos > f->win_y)
		return (0);
	return (1);
}

void		window_validation(int signum)
{
	t_sct	*f;
	struct winsize win;
	int		len;

	signum++;
	f = get_t_sect(NULL);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &win);
	f->win_x = win.ws_col;
	f->win_y = win.ws_row;
	if (f->del == 0)
		f->tata = f->arg_height;
	if ((len = window_sizevalidation(f, 0, 0 , 0)))
		print_scren(f, 0, 0, 0);
	else
	{
		ft_clrscreen(f->win_y);
		ft_printfcolor("%s", "No space :C\n", 31);
	}
}