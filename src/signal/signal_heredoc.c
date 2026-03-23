#include "../../includes/minishell.h"

/**
 * @brief Signal handler for SIGINT during heredoc input. Sets g_signal and
 *		closes STDIN_FILENO to force readline() to return NULL and abort
 *		the heredoc read loop.
 * @param signum The signal number received (SIGINT = 2).
 * @return void
 */
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
