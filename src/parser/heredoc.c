#include "../../includes/minishell.h"

/**
 * @brief Cleans up after a heredoc is interrupted by a signal (Ctrl+C).
 *		Closes the write FD, unlinks the temp file, restores stdin from
 *		backup and resets signals to interactive mode.
 * @param fd The write file descriptor of the heredoc temp file.
 * @param mini Pointer to the main shell structure, uses mini->stdin_backup.
 * @return Always -1, to signal the caller that the heredoc was aborted.
 */
static int	hd_signal_cleanup(int fd, t_mini *mini)
{
	close(fd);
	unlink(".minishell_heredoc");
	dup2(mini->stdin_backup, STDIN_FILENO);
	close(mini->stdin_backup);
	set_signals_interactive();
	return (-1);
}

/**
 * @brief Inner read loop for heredoc. Reads lines with readline() until the
 *		 delimiter is matched or a signal/EOF interrupts.
 * @param fd Write file descriptor of the heredoc temp file.
 * @param delimiter String that closes the heredoc.
 * @param mini Pointer to the main shell structure.
 * @return 1 on success, -1 if interrupted by a signal.
 */
static int	hd_read_loop(int fd, char *delimiter, t_mini *mini)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal != 0)
		{
			free(line);
			return (hd_signal_cleanup(fd, mini));
		}
		if (!line)
			return (ft_fprintf(2, ERROR_HD, delimiter), 1);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (1);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	handle_heredoc(char *delimiter, t_mini *mini)
{
	int	fd;

	fd = open(".minishell_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (ft_fprintf(2, ERR_HD_PERMISSION), -1);
	mini->stdin_backup = dup(STDIN_FILENO);
	g_signal = 0;
	set_signals_heredoc();
	if (hd_read_loop(fd, delimiter, mini) == -1)
		return (-1);
	close(mini->stdin_backup);
	close(fd);
	fd = open(".minishell_heredoc", O_RDONLY);
	unlink(".minishell_heredoc");
	set_signals_interactive();
	return (fd);
}
