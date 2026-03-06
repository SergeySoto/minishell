#include "../../includes/minishell.h"

static void	handler_sigint_heredoc(int signum)
{
	g_signal = signum;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	set_signals_heredoc(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handler_sigint_heredoc;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
