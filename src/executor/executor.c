
#include "../../includes/minishell.h"

void	execute_cmd(t_mini *mini)
{
	t_cmd	*cmd;

	cmd = mini->cmds;
	if (!cmd)
		return ;
	if (cmd->next == NULL)
		exec_simple_cmd(mini, cmd);
	else
		exec_pipelines(mini, cmd);
	return ;
}

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
		close(cmd->fd_in);
		close(cmd->fd_out);
		perror("fork");
		return ;
	}
	if (cmd->pid == 0)
	{
		if (cmd->args[0])
			exec_built_child(mini, cmd);
		else
		{
			if(!apply_redirections(cmd))
				exit(1);
			exit(0);
		}
	}
	else
	{
		waitpid(cmd->pid, &mini->exit_status, 0);
		if (WIFEXITED(mini->exit_status))
			mini->exit_status = WEXITSTATUS(mini->exit_status);
		close(cmd->fd_in);
		close(cmd->fd_out);
	}
	return ;
}

void	exec_pipeline(t_mini *mini)
{
	t_cmd	*current_cmd;
	int		prev_pipe;
	int		pipe_fd[2];
	char	**env;

	prev_pipe = -1;
	current_cmd = mini->cmds;
	while (current_cmd != NULL)
	{
		if (current_cmd->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("Error pipe fd");
				if (prev_pipe != -1)
					close(prev_pipe);
				free_struct_mini(mini);
				return ;
			}
		}
		current_cmd->pid = fork();
		if (current_cmd->pid < 0)
		{
			perror("fork");
			if (current_cmd->next)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			if (prev_pipe != -1)
				close(prev_pipe);
			return ;
		}
		if (current_cmd->pid == 0)
		{
			if (prev_pipe != -1)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if (current_cmd->next)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			exec_built_child(mini, current_cmd);
		}
		else
		{
			if (prev_pipe != -1)
				close(prev_pipe);
			if (current_cmd->next)
			{
				close(pipe_fd[1]);
				prev_pipe = pipe_fd[0];
			}
			current_cmd = current_cmd->next;
		}
	}
	current_cmd = mini->cmds;
	while (current_cmd)
	{
		waitpid(current_cmd->pid, &mini->exit_status, 0);
		current_cmd = current_cmd->next;
	}
	if (WIFEXITED(mini->exit_status))
		mini->exit_status = WEXITSTATUS(mini->exit_status);
}
