
#include "../../includes/minishell.h"

void	exec_simple_cmd(t_mini *mini, t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args[0] && is_builtin(cmd->args[0])
		&& is_built_father(cmd->args[0]))
	{
		exec_built_father(mini, cmd);
		return ;
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		return ;
	}
	if (cmd->pid == 0)
		exec_child_smp(mini, cmd);
	else
		wait_father_smp(mini, cmd);
	return ;
}

void	exec_pipeline(t_mini *mini)
{
	t_cmd	*current_cmd;
	int		prev_pipe;
	int		pipe_fd[2];

	prev_pipe = -1;
	current_cmd = mini->cmds;
	while (current_cmd != NULL)
	{

		if (create_pipe(mini, current_cmd, prev_pipe, pipe_fd) == -1)
			return ;
		if (fork_process(current_cmd, prev_pipe, pipe_fd) == -1)
			return ;
		if (current_cmd->pid == 0)
			child_process_mlt(mini, current_cmd, prev_pipe, pipe_fd);
		else
		{
			father_process_mlt(current_cmd, &prev_pipe, pipe_fd);
			current_cmd = current_cmd->next;
		}
	}
	wait_children_mlt(mini);
}

void	execute_cmd(t_mini *mini)
{
	t_cmd	*cmd;

	cmd = mini->cmds;
	if (!cmd)
		return ;
	if (cmd->next == NULL)
		exec_simple_cmd(mini, cmd);
	else
		exec_pipeline(mini);
	return ;
}
