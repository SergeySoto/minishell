
#include "../../includes/minishell.h"

int	init_pipe(t_mini *mini, t_cmd *cmd, int prev_pipe, int *pipe_fd)
{
	if (cmd->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("Error pipe fd");
			if (prev_pipe != -1)
				close(prev_pipe);
			free_struct_mini(mini);
			return (-1);
		}
	}
	return (0);
}

int	spawn_process(t_cmd *cmd, int prev_pipe, int *pipe_fd)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		perror("fork");
		if (cmd->next)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		if (prev_pipe != -1)
			close(prev_pipe);
		return (-1);
	}
	return (0);
}

void	pipe_child_process(t_mini *mini, t_cmd *cmd, int prev_pipe, int *pipe_fd)
{
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	execute_command_node(mini, cmd);
}

void	pipe_parent_process(t_cmd *cmd, int *prev_pipe, int *pipe_fd)
{
	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_pipe = pipe_fd[0];
	}
}

void	wait_all_children(t_mini *mini)
{
	t_cmd *current_cmd;

	set_signals_ignore();
	current_cmd = mini->cmds;
	while (current_cmd)
	{
		waitpid(current_cmd->pid, &mini->exit_status, 0);
		current_cmd = current_cmd->next;
	}
	if (WIFEXITED(mini->exit_status))
		mini->exit_status = WEXITSTATUS(mini->exit_status);
	else if (WIFSIGNALED(mini->exit_status))
		mini->exit_status = 128 + WTERMSIG(mini->exit_status);
	set_signals_interactive();
}
