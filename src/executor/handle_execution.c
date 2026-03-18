
#include "../../includes/minishell.h"

int	execute_builtin_func(t_mini *mini, t_cmd *cmd)
{
	(void)mini;
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd->args));
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(mini, cmd->args));
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd(mini));
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(mini, cmd->args));
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(mini, cmd));
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(mini, cmd->args));
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(mini, cmd));
	return (0);
}

static void	execute_system_binary(t_mini *mini, t_cmd *cmd)
{
	char	**env;
	char	*path_value;

	if (!cmd->cmd_path)
	{
		path_value = get_env_val("PATH", mini);
		if (!path_value)
			ft_fprintf(2, ERR_ENV_NOT_FILORDIR, cmd->args[0]);
		else
			ft_fprintf(2, ERR_CMD_NOT_FOUND, cmd->args[0]);
		free_struct_mini(mini);
		exit(127);
	}
	env = env_to_array(mini->env);
	if (execve(cmd->cmd_path, cmd->args, env) == -1)
		free_token(NULL, env);
	perror(cmd->args[0]);
	free_struct_mini(mini);
	exit(126);
}

void	execute_command_node(t_mini *mini, t_cmd *cmd)
{
	int	exit_code;

	if (!setup_redirections(cmd))
	{
		free_struct_mini(mini);
		exit(1);
	}
	if (!cmd->args || !cmd->args[0])
	{
		free_struct_mini(mini);
		exit(0);
	}
	if (is_builtin(cmd->args[0]))
	{
		exit_code = execute_builtin_func(mini, cmd);
		free_struct_mini(mini);
		exit(exit_code);
	}
	execute_system_binary(mini, cmd);
}
