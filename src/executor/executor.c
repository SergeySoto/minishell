
#include "../../includes/minishell.h"

void	get_cmd_path(t_mini *mini)
{
	char	*path_found;
	char	**path_splited;
	t_env	*env;

	path_splited = NULL;
	path_found = 0;
	env = (*mini).env;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
		{
			path_splited = ft_split(env->value, ':');
			if (!path_splited)
				printf("Environment path not found\n");
			break ;
		}
		env = env->next;
	}
	find_command2(path_splited, &(*mini).cmds);
	free_token(NULL, path_splited);
	return ;
}

/*
void	find_command(char **path_env, t_cmd **cmd)
{
	char	*aux;
	char	*full_path;
	int		i;
	
	i = 0;
	full_path = NULL;
	while (path_env[i])
	{
		while (cmd)
		{
			aux = ft_strjoin(path_env[i], "/");
			full_path = ft_strjoin(aux, (*cmd)->args[0]);
			free(aux);
			if (access(full_path, X_OK) == 0)
			{
				(*cmd)->cmd_path = full_path;
				return ;
			}
			free(full_path);
		}
		i++;
	}
	return ;
}
*/

void	find_command2(char **path_env, t_cmd **cmd)
{
	t_cmd	*current;
	char	*aux;
	char	*full_path;
	int		i;

	full_path = NULL;
	aux = NULL;
	current = (*cmd);
	while (current)
	{
		i = 0;
		while (path_env[i])
		{
			aux = ft_strjoin(path_env[i], "/");
			full_path = ft_strjoin(aux, current->args[0]);
			free(aux);
			if (access(full_path, X_OK) == 0)
			{
				current->cmd_path = full_path;
				break ;
			}
			free(full_path);
		}
		i++;
		current = current->next;
	}
}
