#include "libft.h"

void		ft_free_mtx(char **mtx)
{
	int		i;

	i = -1;
	while (mtx[++i])
		ft_memdel((void**)&mtx[i]);
}