#ifndef FT_SELECT
# define FT_SELECT
#include "libft/libft.h"
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>

# define KEY_ENTER		10
# define KEY_ESC		27
# define KEY_SPC		32
# define KEY_STAR		42
# define KEY_MINUS		45
# define KEY_BSP		127
# define KEY_LEFT		4479771
# define KEY_UP			4283163
# define KEY_RIGHT		4414235
# define KEY_DOWN		4348699
# define KEY_DEL		2117294875L

typedef struct		s_sct
{
	struct termios	term;
	char			**objects;
	int				*select;
	int				arg_height;
	int				arg_width;
	int				win_x;
	int				win_y;
	int				cursor;
	int				total_selected;
	int				len;
	int				full;
}						t_sct;

void					print_scren(t_sct *f);
void					read_key(t_sct *f);
void					key_up_down(t_sct *f, long key);
void					return_values(t_sct *f);
static void		key_space(t_sct *f, long key);

#endif
