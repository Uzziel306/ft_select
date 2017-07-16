#include "ft_select.h"

int			window_sizevalidation(t_sct *f)
{
	int		j;

	j = -1;
	f->len = 0;
	f->full = f->win_x * f->win_y;

	while (f->objects[++j])
	{
		f->len += (int)ft_strlen(f->objects[j]) + 3;
	}
	printf("len: %d\n", f->len);
	printf("full: %d\n", f->full);
	return (f->len < f->full) ? 1 : 0;
}

t_sct		*get_t_sect(t_sct *f)
{
	static t_sct *h = NULL;

	if (f)
		h = f;
	return (h);
}
void get_windows_size(int *i, int *y)
{
	struct winsize win;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &win);
	*i = win.ws_col;
	*y = win.ws_row;
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
		print_scren(f);
	else
		ft_printfcolor("%s", "No space :C\n", 31);
		f->len = 0;
}

void		safe_exit(int signum)
{
	exit (3);
}
void		suspend_term(int signum)
{
	exit (3);
}

void		continue_term(int signum)
{
	exit (3);
}

void	set_signals(void)
{
	signal(SIGHUP, safe_exit);
	signal(SIGINT, safe_exit);
	signal(SIGQUIT, safe_exit);
	signal(SIGILL, safe_exit);
	signal(SIGTRAP, safe_exit);
	signal(SIGABRT, safe_exit);
	signal(SIGEMT, safe_exit);
	signal(SIGFPE, safe_exit);
	signal(SIGBUS, safe_exit);
	signal(SIGSEGV, safe_exit);
	signal(SIGSYS, safe_exit);
	signal(SIGPIPE, safe_exit);
	signal(SIGALRM, safe_exit);
	signal(SIGTERM, safe_exit);
	signal(SIGTTIN, safe_exit);
	signal(SIGTTOU, safe_exit);
	signal(SIGXCPU, safe_exit);
	signal(SIGXFSZ, safe_exit);
	signal(SIGVTALRM, safe_exit);
	signal(SIGPROF, safe_exit);
	signal(SIGUSR1, safe_exit);
	signal(SIGUSR2, safe_exit);
	signal(SIGTSTP, suspend_term);
	signal(SIGCONT, continue_term);
	signal(SIGWINCH, window_validation);
}

void		ft_error(char *error)
{
	ft_printfcolor("%s %s\n", "Error:", 31, error, 31);
	exit (EXIT_FAILURE);
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

void	ft_termcmd(char *str)
{
	if (str == NULL)
		return ;
	ft_putstr_fd(tgetstr(str, NULL), 2);
}

void	ft_cursor_goto(int x, int y)
{
	char *str1;
	char *str2;

	if ((str1 = tgetstr("cm", NULL)) != NULL)
	{
		if ((str2 = tgoto(str1, x, y)) != NULL)
			ft_putstr_fd(str2, 2);
	}
}

void	ft_clrscreen(int rows)
{
	while (--rows >= 0)
	{
		ft_cursor_goto(0, rows);
		ft_termcmd("dl");
	}
}

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
	f->total_selected = 0;
	f->arg_height = argc - 1;
	f->objects = argv + 1;
	f->arg_width = max_width(f->objects);
	f->select = (int *)ft_memalloc(sizeof(int) * f->arg_height);
}

void		ft_putcharn_fd(int c, int n, int fd)
{
	while (n)
	{
		ft_putchar_fd(c, fd);
		n--;
	}
}

void		print_scren(t_sct *f)
{
	int		i;
	int		col;
	int		row;
	// ft_termcmd("ti");
	int		huevos;
	row = -1;
	col = 0;
	i = -1;
	// ft_clrscreen(f->win_y);
	// ft_printfcolor("%s%d\n", "ITEMS SELECTED: ", 44, f->total_selected, 44);
	ft_cursor_goto(0, 0);
	while (f->objects[++i])
	{
			if (i == f->cursor)
				ft_termcmd("us");
			if (f->select[i] == 1)
				ft_termcmd("so");
			ft_putstr_fd(f->objects[i], 2);
			ft_termcmd("ue");
			ft_termcmd("se");
			ft_putcharn_fd(' ',f->arg_width - (int)ft_strlen(f->objects[i]) + 3 ,2);
			printf("\n");
	}
			// printf("%d\n", f->arg_width - (int)ft_strlen(f->objects[i]) + 1);
	// ft_printfbasic("%d\n", f->cursor);
	// ft_printfbasic("%d\n", f->win_y);
}

void		return_values(t_sct *f)
{
	int		i;
	int		cont;

	cont = 0;
	i = -1;
	ft_clrscreen(f->win_x);
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
	ft_cursor_goto(0, 0);
	window_validation(0);
	// print_scren(&f);
	read_key(&f);
	return (0);
}
// gcc main.c -ltermcap -o ft_select && ./ft_select
	// mtx = ft_strsplit("huevos pendejo de mierda", ' ');
	// tmp = mtx + 1;
	// ft_putmatrix(tmp);
