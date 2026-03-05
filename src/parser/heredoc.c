
#include "../../includes/minishell.h"


int	handle_heredoc(char *demiliter, t_mini *mini)
{
	int		*fd;
	char	*line;

	fd = open("/tmp/minishell_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (perror(fd), 0);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			perror("warning: here-document delimited by end-of-file");
			break ;
		}
		if (strcmp(line, demiliter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	fd[0] = open("/tmp/minishell_heredoc", O_RDONLY);
	unlink("/tmp/minishell_heredoc");
	return (fd[0]);
}

