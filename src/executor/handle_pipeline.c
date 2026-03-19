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

void	pipe_child_process(t_mini *mini, t_cmd *cmd, int prv_pipe, int *pipe_fd)
{
	set_signals_default();
	if (prv_pipe != -1)
	{
		dup2(prv_pipe, STDIN_FILENO);
		close(prv_pipe);
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
	t_cmd	*current_cmd;

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
	{
		g_signal = 128 + WTERMSIG(mini->exit_status);
		if (WTERMSIG(mini->exit_status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(mini->exit_status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		mini->exit_status = g_signal;
	}
	set_signals_interactive();
}
