#include "libft.h"

void		ft_error(char *error)
{
	ft_printfcolor("%s %s\n", "Error:", 31, error, 31);
	exit (EXIT_FAILURE);
}