
#include "../../includes/minishell.h"

char	*get_env_val(char *name, t_mini *mini)
{
	t_env	*env;

	env = mini->env;
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*find_full_path(t_mini *mini)
{
	char	*path_found;
	char	**path_splited;

	path_splited = NULL;
	path_found = 0;
	path_found = get_env_val("PATH", mini);
	path_splited = ft_split(path_found, ':');
	if (!path_splited)
	{
		free_token(NULL, path_splited);
		printf("Environment path not found\n");
	}
	assign_full_path(path_splited, &(*mini).cmds);
	free_token(NULL, path_splited);
	return ;
}

void	assign_full_path(char **path_env, t_cmd **cmd)
{
	char	*aux;
	char	*full_path;
	int		i;

	full_path = NULL;
	aux = NULL;
	if (ft_strchr((*cmd)->args[0], '/') && access((*cmd)->args[0], X_OK) == 0)
	{
		(*cmd)->cmd_path = ft_strdup((*cmd)->args[0]);
		return ;
	}
	i = 0;
	while (path_env && path_env[i])
	{
		aux = ft_strjoin(path_env[i], "/");
		full_path = ft_strjoin(aux, (*cmd)->args[0]);
		free(aux);
		if (access(full_path, X_OK) == 0)
		{
			(*cmd)->cmd_path = full_path;
			break ;
		}
		free(full_path);
		i++;
	}
}
