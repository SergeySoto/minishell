
#include "../../includes/minishell.h"

int	backup_std_fds(t_mini *mini)
{
	mini->stdin_backup = dup(STDIN_FILENO);
	if (mini->stdin_backup < 0)
		return (perror("Dup failed"), -1);
	mini->stdout_backup = dup(STDOUT_FILENO);
	if (mini->stdout_backup < 0)
	{
		close(mini->stdin_backup);
		return (perror("Dup failed"), -1);
	}
	return (0);
}

int	restore_std_fds(t_mini *mini)
{
	if (dup2(mini->stdin_backup, STDIN_FILENO) < 0)
		return (perror("Dup failed"), -1);
	if (dup2(mini->stdout_backup, STDOUT_FILENO) < 0)
	{
		close(mini->stdin_backup);
		close(mini->stdout_backup);
		return (perror("Dup failed"), -1);
	}
	close(mini->stdin_backup);
	close(mini->stdout_backup);
	return (0);
}

int	setup_redirections(t_cmd *cmd)
{
	if (cmd->infile)
	{
		cmd->fd_in = open(cmd->infile, O_RDONLY);
		if (cmd->fd_in == -1)
			return (perror(cmd->infile), 0);
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return (close(cmd->fd_in), 0);
		close(cmd->fd_in);
	}
	if (cmd->outfile)
	{
		if (cmd->append == 1)
			cmd->fd_out = open(cmd->outfile, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else
			cmd->fd_out = open(cmd->outfile, O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		if (cmd->fd_out == -1)
			return (perror(cmd->outfile), 0);
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return (close(cmd->fd_out), 0);
		close(cmd->fd_out);
	}
	return (1);
}
