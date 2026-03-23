#include "../../includes/minishell.h"

/**
 * @brief Allocates and initialises a new t_env node with the given key/value.
 * @param key Heap-allocated string for the variable name.
 * @param value Heap-allocated string for the variable value.
 * @return Pointer to the new node, or NULL on malloc failure.
 */
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

void	add_env_back(t_env **env, char *key, char *value)
{
	t_env	*temp;
	t_env	*new_env;

	new_env = create_env_node(key, value);
	if (!new_env)
		return ;
	if (!*env)
	{
		*env = new_env;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = new_env;
}

void	in_or_de_shlvl(t_mini *mini)
{
	char	*shlvl;
	int		level;
	char	*new_level;

	shlvl = get_env_val("SHLVL", mini);
	if (shlvl == NULL)
		add_env_back(&mini->env, ft_strdup("SHLVL"), ft_strdup("1"));
	else
	{
		level = ft_atoi(shlvl);
		level += 1;
		new_level = ft_itoa(level);
		create_new_env(mini, ft_strdup("SHLVL"), new_level);
	}
}

t_env	*create_basic_env(char **envp)
{
	char	*pwd_var;
	t_env	*env;
	(void)envp;

	env = NULL;
	pwd_var = getcwd(NULL, 0);
	add_env_back(&env, ft_strdup("PWD"), ft_strdup(pwd_var));
	free(pwd_var);
	add_env_back(&env, ft_strdup("_"), ft_strdup("/usr/bin/env"));
	return (env);
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
	if (!*envp)
		env = create_basic_env(envp);
	return (env);
}
