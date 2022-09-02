#include <signal.h>

void	ft_error(char *msg);

void	set_sigaction(struct sigaction *sa_ptr,
						void (*handler)(int, siginfo_t *, void *))
{
	(*sa_ptr).sa_flags = SA_SIGINFO;
	(*sa_ptr).sa_sigaction = handler;
	sigemptyset(&(*sa_ptr).sa_mask);
	if (sigaction(SIGINT, sa_ptr, 0) == -1)
		ft_error("signal(SIGINT) error");
	if (sigaction(SIGQUIT, sa_ptr, 0) == -1)
		ft_error("signal(SIGQUIT) error");
}
