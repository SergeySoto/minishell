
#include "../../includes/minishell.h"

char	*get_cmd_path(t_mini *mini)
{
	char	*path_found;
	char	**path_splited;
	t_env	*env;

	path_found = 0;
	env = (*mini).env;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
		{
			path_splited = ft_split(env->value, ':');
			break ;
		}
		env = env->next;
	}
	if (!path_splited)
		printf("Environment path not found\n");
	else
		path_splited = ft_split(path_found, ':');
	return ;
}

char	*find_command(t_mini *mini)
{
	char	*aux;
	char	*full_path;
	t_env	*env;

	env = (*mini).env
	full_path = NULL;

	while (env)
	{
		aux = ft_strjoin(env_path[i], "/");
		full_path = ft_strjoin(aux, cmd);
		free(aux);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free_all(NULL, full_path);
		i++;
	}
	return (NULL);
}
