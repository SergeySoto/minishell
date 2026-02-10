
#include "../../includes/minishell.h"

void	execute_cmds(t_mini **mini)
{
	t_cmd	*cmd;

	cmd = (*mini);
	if (cmd->next == NULL && is_builtin)
		//cd, export, exit, unset deben modificar el entorno del padre
		execute_builtin(cmd);
		
}