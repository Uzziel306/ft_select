#include "libft.h"

void	ft_termcmd(char *str)
{
	if (str == NULL)
		return ;
	ft_putstr_fd(tgetstr(str, NULL), 2);
}