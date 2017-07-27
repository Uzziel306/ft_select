#include "ft_select.h"

void		starting_env(t_sct *f)
{
	char	*env;
	int		ret;

	if (!(env = getenv("TERM")))
		ft_error("didn't find TERM enviroment");
	if (!(ret = tgetent(NULL, env)))
		ft_error("getting the TERM enviroment");
	if (tcgetattr(0, &f->term) != 0)
		ft_error("didn't store the attributes of termios structure");
	f->term.c_lflag &= ~(ICANON | ECHO);
	f->term.c_cc[VMIN] = 1;
	f->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &f->term);
	ft_termcmd("ti");
	ft_termcmd("vi");
}

void		starting_f(int	argc, char	**argv, t_sct *f)
{
	f->len = 0;
	f->full = 0;
	f->cursor = 0;
	f->tmp = 0;
	f->total_selected = 0;
	f->arg_height = argc - 1;
	f->objects = argv + 1;
	f->del = 0;
	f->arg_width = max_width(f->objects);
	f->select = (int *)ft_memalloc(sizeof(int) * f->arg_height);
}

void		return_values(t_sct *f)
{
	int		i;
	int		cont;

	cont = 0;
	i = -1;
	ft_clrscreen(f->win_x);
	ft_termcmd("te");
	ft_termcmd("ve");
	while (f->objects[++i])
	{
		if (f->select[i] == 1)
		{
			ft_printfbasic("%s", f->objects[i]);
			cont += 1;
			if (cont != f->total_selected)
				ft_putchar(' ');
		}
	}
	ft_memdel((void**)&f->select);
	exit (EXIT_SUCCESS);
}

int			main(int argc, char **argv)
{
	t_sct	f;
	int		i;
	char	*s;

	i = -1;
	if (argc < 2)
		ft_error("No arguments");
	set_signals();
	starting_env(&f);
	starting_f(argc, argv, &f);
	get_t_sect(&f);
	window_validation(0);
	read_key(&f);
	return (0);
}
// gcc *.c -ltermcap libft/libft.a -o ft_select && ./ft_select *
	// mtx = ft_strsplit("huevos pendejo de mierda", ' ');
	// tmp = mtx + 1;
	// ft_putmatrix(tmp);
