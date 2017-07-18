#include "ft_select.h"

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
	ft_termcmd("ve");
	exit (3);
}