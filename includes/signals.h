#ifndef SIGNAL_H
# define SIGNAL_H

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                               signal.c                                     */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Configures signal handling for the interactive prompt state.
 *		SIGINT → handler_sigint_interactive (reprint prompt).
 *		SIGQUIT → SIG_IGN (ignored).
 * @return void
 */
void	set_signals_interactive(void);

/**
 * @brief Configures signal handling for the parent process while waiting
 *		for a single child command.
 *		SIGINT → handler_signals_child (write newline).
 *		SIGQUIT → SIG_IGN.
 * @return void
 */
void	set_signals_child(void);

/**
 * @brief Ignores both SIGINT and SIGQUIT. Used in the parent while waiting
 *		for all pipeline children to finish.
 * @return void
 */
void	set_signals_ignore(void);

/**
 * @brief Restores default OS behaviour for both SIGINT and SIGQUIT.
 *		Always called inside child processes right after fork(), so that
 *		external programs receive signals normally.
 * @return void
 */
void	set_signals_default(void);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                           signal_heredoc.c                                 */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Configures signal handling for the heredoc input state.
 *		SIGINT → handler_sigint_heredoc (abort heredoc).
 *		SIGQUIT → SIG_IGN.
 * @return void
 */
void	set_signals_heredoc(void);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                            signal_utils.c                                  */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Signal handler for SIGINT in interactive mode. Sets g_signal,
 *		writes a newline and uses readline helpers to display a fresh
 *		empty prompt without executing anything.
 * @param signum The signal number received (SIGINT = 2).
 * @return void
 */
void	handler_sigint_interactive(int signum);

/**
 * @brief Signal handler for SIGINT while the parent waits for a single child.
 *		Sets g_signal and writes a newline. The child handles its own death
 *		via SIG_DFL.
 * @param signum The signal number received (SIGINT = 2).
 * @return void
 */
void	handler_signals_child(int signum);

#endif
