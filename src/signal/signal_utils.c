
#include "../../includes/minishell.h"

void	handler_sigint_interactive(int signum)
{
	g_signal = signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handler_signals_child(int signum)
{
	g_signal = signum;
	write(1, "\n", 1);
}
