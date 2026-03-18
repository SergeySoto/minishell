
#include "../../includes/minishell.h"

static int	hd_signal_cleanup(int fd, t_mini *mini)
{
	close(fd);
	unlink(".minishell_heredoc");
	dup2(mini->stdin_backup, STDIN_FILENO);
	close(mini->stdin_backup);
	set_signals_interactive();
	return (-1);
}

static int	hd_read_loop(int fd,char *delimiter, t_mini *mini)
{
	char *line;
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
	int		fd;

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

