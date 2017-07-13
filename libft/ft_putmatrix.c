#include "libft.h"

void		ft_putmatrix(char **mtx)
{
	int		i;

	i = -1;
	while (mtx[++i])
		ft_printfbasic("%s\n", mtx[i]);
}