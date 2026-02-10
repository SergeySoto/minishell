
#include "../../includes/minishell.h"

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}



void	execute_cmds(t_mini **mini)
{
	t_cmd	*cmd;

	cmd = (*mini)->cmds;
	if (cmd->next == NULL && is_builtin(cmd->args[0]))
		//cd, export, exit, unset deben modificar el entorno del padre
		execute_builtin(cmd);
	
}
