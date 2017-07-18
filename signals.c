#include "ft_select.h"

void		safe_exit(int signum)
{
	exit (3);
}
void		suspend_term(int signum)
{
	exit (3);
}

void		continue_term(int signum)
{
	exit (3);
}

void	set_signals(void)
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