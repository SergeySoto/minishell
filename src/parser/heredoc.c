
#include "../../includes/minishell.h"

int	handle_heredoc(char *delimiter, t_mini *mini)
{
	int		fd;
	char	*line;
	(void)mini;

	fd = open("/tmp/minishell_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (perror("heredoc"), -1);
	mini->stdin_backup = dup(STDIN_FILENO);
	g_signal = 0;
	set_signals_heredoc();
	while (1)
	{
		line = readline("> ");
		if (g_signal != 0)
		{
			free(line);
			close(fd);
			unlink("/tmp/minishell_heredoc");
			dup2(mini->stdin_backup, STDIN_FILENO);
			close(mini->stdin_backup);
			set_signals_interactive();
			return (-1);
		}
		if (!line)
		{
			ft_putstr_fd(ERROR_HD, 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("\n", 2);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(mini->stdin_backup);
	close(fd);
	fd = open("/tmp/minishell_heredoc", O_RDONLY);
	unlink("/tmp/minishell_heredoc");
	set_signals_interactive();
	return (fd);
}

