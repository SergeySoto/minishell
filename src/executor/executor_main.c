
#include "../../includes/minishell.h"

void	executor_dispatch(t_mini *mini)
{
	t_cmd	*cmd;

	cmd = mini->cmds;
	if (!cmd)
		return ;
	if (cmd->next == NULL)
		handle_single_cmd(mini, cmd);
	else
		handle_pipeline_loop(mini);
	return ;
}

void	handle_single_cmd(t_mini *mini, t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args[0] && is_builtin(cmd->args[0])
		&& is_parent_builtin(cmd->args[0]))
	{
		execute_builtin_in_parent(mini, cmd);
		return ;
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		return ;
	}
	if (cmd->pid == 0)
		single_cmd_child_process(mini, cmd);
	else
		single_cmd_parent_wait(mini, cmd);
	return ;
}

void	handle_pipeline_loop(t_mini *mini)
{
	t_cmd	*current_cmd;
	int		prev_pipe;
	int		pipe_fd[2];

	prev_pipe = -1;
	current_cmd = mini->cmds;
	while (current_cmd != NULL)
	{

		if (init_pipe(mini, current_cmd, prev_pipe, pipe_fd) == -1)
			return ;
		if (spawn_process(current_cmd, prev_pipe, pipe_fd) == -1)
			return ;
		if (current_cmd->pid == 0)
			pipe_child_process(mini, current_cmd, prev_pipe, pipe_fd);
		else
		{
			pipe_parent_process(current_cmd, &prev_pipe, pipe_fd);
			current_cmd = current_cmd->next;
		}
	}
	wait_all_children(mini);
}
