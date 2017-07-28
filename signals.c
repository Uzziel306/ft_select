/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 21:08:05 by asolis            #+#    #+#             */
/*   Updated: 2017/07/27 20:00:39 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		safe_exit(int signum)
{
	t_sct	*f;

	signum++;
	f = get_t_sect(0);
	ft_memdel((void**)&f->select);
	ft_termcmd("te");
	ft_termcmd("ve");
	exit(3);
}

void		suspend_term(int signum)
{
	t_sct	*f;
	char	tmp[3];

	signum++;
	f = get_t_sect(0);
	ft_clrscreen(f->win_y);
	f->term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &f->term);
	ft_termcmd("te");
	ft_termcmd("ve");
	signal(SIGTSTP, SIG_DFL);
	tmp[0] = f->term.c_cc[VSUSP];
	tmp[1] = '\n';
	tmp[2] = '\0';
	ioctl(0, TIOCSTI, &tmp);
}

void		continue_term(int signum)
{
	t_sct	*f;

	signum++;
	f = get_t_sect(0);
	starting_env(f);
	set_signals();
	window_validation(0);
}

void		set_signals(void)
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
