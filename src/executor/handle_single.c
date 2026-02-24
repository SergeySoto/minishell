
#include "../../includes/minishell.h"

void	execute_builtin_in_parent(t_mini *mini, t_cmd *cmd)
{
	backup_std_fds(mini);
	if (!setup_redirections(cmd))
	{
		restore_std_fds(mini);
		return ;
	}
	execute_builtin_func(mini, cmd);
	restore_std_fds(mini);
}

void	single_cmd_child_process(t_mini *mini, t_cmd *cmd)
{
	if (cmd->pid == 0)
	{
		if (cmd->args[0])
			execute_command_node(mini, cmd);
		else
		{
			if(!setup_redirections(cmd))
				exit(1);
			exit(0);
		}
	}
}

void	single_cmd_parent_wait(t_mini *mini, t_cmd *cmd)
{
	waitpid(cmd->pid, &mini->exit_status, 0);
	if (WIFEXITED(mini->exit_status))
		mini->exit_status = WEXITSTATUS(mini->exit_status);
	else if (WIFSIGNALED(mini->exit_status))
		mini->exit_status = 128 + WTERMSIG(mini->exit_status);
	//close(cmd->fd_in);
	//close(cmd->fd_out);
}
