
#include "../../includes/minishell.h"

static char	*join_env_node(t_env *envp)
{
	int		len_str;
	char	*str;

	len_str = ft_strlen(envp->key) + ft_strlen(envp->value) + 2;
	str = malloc(sizeof(char) * len_str);
	if (!str)
		return (NULL);
	ft_strlcpy(str, envp->key, len_str);
	ft_strlcat(str, "=", len_str);
	ft_strlcat(str, envp->value, len_str);
	return (str);
}

char	**env_to_array(t_env *envp)
{
	char	**env_array;
	t_env	*current;
	int		i;

	env_array = malloc(sizeof(char *) * (ft_lstsize(envp) + 1));
	if (!env_array)
		return (NULL);
	current = envp;
	i = 0;
	while (current)
	{
		env_array[i] = join_env_node(current);
		if (!env_array[i])
			return (free_token(NULL, env_array));
		i++;
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
