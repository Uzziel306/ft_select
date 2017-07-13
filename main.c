#include "ft_select.h"

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
	if (!str || !*str)
		return ;
	ft_putstr_fd(tgetstr(str, NULL), STDERR_FILENO);
}

void	ft_cursor_goto(int x, int y)
{
	char *str1;
	char *str2;

	if ((str1 = tgetstr("cm", NULL)) != NULL)
	{
		if ((str2 = tgoto(str1, x, y)) != NULL)
			ft_putstr_fd(str2, STDERR_FILENO);
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
	f->win_x = tgetnum("co");
	f->win_y = tgetnum("li");
	ft_termcmd("ti");
	ft_termcmd("ve");
	ft_clrscreen(f->win_y);
}

void		starting_f(int	argc, char	**argv, t_sct *f)
{
	f->cursor = 0;
	f->arg_height = argc - 1;
	f->objects = argv + 1;
	f->arg_width = max_width(f->objects);
	f->select = (int *)ft_memalloc(sizeof(int) * f->arg_height);
}

void		print_scren(t_sct *f)
{
	int		i;

	ft_termcmd("ti");
	ft_termcmd("ve");
	i = -1;
	while (f->objects[++i])
	{
		if (i == f->cursor)
			ft_termcmd("us");
		if (f->select[i] == 1)
			ft_termcmd("so");
		ft_putstr_fd(f->objects[i], 2);
		 printf("\n");
		ft_termcmd("ue");
		ft_termcmd("se");
	}
	printf("%d\n", f->cursor);
	printf("%d\n", f->arg_height);
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

		f->select[f->cursor] = 1;
	else
		f->select[f->cursor] = 0;
	key_up_down(f, KEY_DOWN);
}

void		read_key(t_sct *f)
{
	long	key;
	int		refresh;

	print_scren(f);
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
			printf("enter\n");
		else if (key == KEY_STAR || key == KEY_MINUS)
			printf("minus\n");
		else if (key == KEY_ESC)
			exit(0);
		else
			refresh = 0;
		(refresh) ? print_scren(f) : 0;
		key = 0;
	}
}

int			main(int argc, char **argv)
{
	t_sct	f;
	int		i;
	char	*s;

	i = -1;
	if (argc < 2)
		ft_error("No arguments");
	starting_env(&f);
	starting_f(argc, argv, &f);
	ft_cursor_goto(0, 0);
	read_key(&f);
	return (0);
}
// gcc main.c -ltermcap -o ft_select && ./ft_select
	// mtx = ft_strsplit("huevos pendejo de mierda", ' ');
	// tmp = mtx + 1;
	// ft_putmatrix(tmp);