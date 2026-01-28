
#include "../../includes/minishell.h"

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env) * 1);
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

static void	add_env_back(t_env **env, char *key, char *value)
{
	t_env	*temp;
	t_env	*new_node;

	new_node = create_env_node(key, value);
	if (!new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;
	char	*key;
	char	*value;
	char	*pos;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		pos = ft_strchr(envp[i], '=');
		if (pos)
		{
			key = ft_substr(envp[i], 0, pos - envp[i]);
			value = ft_strdup(pos + 1);
			add_env_back(&env, key, value);
		}
		i++;
	}
	return (env);
}
