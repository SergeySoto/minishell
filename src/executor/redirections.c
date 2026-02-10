
#include "../../includes/minishell.h"

int	apply_redirections(t_cmd *cmd)
{
	if (cmd->infile)
	{
		cmd->fd_in = open(cmd->infile, O_RDONLY);
		if (cmd->fd_in == -1)
			return (perror("Failed opening file"), -1);
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return (close(cmd->fd_in), 1);
		close(cmd->fd_in);
	}
	if (cmd->outfile)
	{
		if (cmd->append == 1)
			cmd->fd_out = open(cmd->fd_out, O_WRONLY | O_CREAT | O_APPEND);
		else
			cmd->fd_out = open(cmd->fd_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd_out == -1)
			return (perror("Failed opening file"), -1);
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return (close(cmd->fd_in), 1);
		close(cmd->fd_out);
	}
	return (0);
}
