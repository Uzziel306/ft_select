#include "libft.h"

void	ft_clrscreen(int rows)
{
	while (--rows >= 0)
	{
		ft_cursor_goto(0, rows);
		ft_termcmd("dl");
	}
}