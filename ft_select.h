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
}					t_sct;
/*
**Windows functions		windows.c
*/
int					ft_putitem_fd(char *str, t_sct *f, int i);
void				print_scren(t_sct *f, int i, int tmp, int huevos);
int					window_sizevalidation(t_sct *f);
void				window_validation(int signum);
/*
**Keyboard's functions	keys.c
*/
void				read_key(t_sct *f);
void				key_up_down(t_sct *f, long key);
static void			key_space(t_sct *f, long key);
/*
**Signal's functions	signals.c
*/
void				set_signals(void);
void				continue_term(int signum);
void				suspend_term(int signum);
void				safe_exit(int signum);
/*
**Helper's functions	helper.c
*/
int					max_width(char **mtx);
void				exit_esc(void);
t_sct				*get_t_sect(t_sct *f);
void				ft_putcharn_fd(int c, int n, int fd);
int					max_width(char **mtx);
/*
**Main's functions		main.c
*/
void				return_values(t_sct *f);
void				starting_f(int	argc, char	**argv, t_sct *f);
void				starting_env(t_sct *f);
#endif
