#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>

/*
	*Cosas a tener en cuenta para export:
	export 1VAR=value	# ❌ Error
	export 9_test=hello	# ❌ Error
	export =value		# ❌ Error
	export VAR			# ✅ OK (declara sin valor)
	export VAR=			# ✅ OK (valor vacío)
	export VAR=value	# ✅ OK (con valor)
	export _VAR=value	# ✅ OK (con valor)
	export "VAR"=value	# ✅ OK (las comillas se quitan)
*/

int	is_valid(char c)
{
	if (!(ft_isalpha(c))&& c != '_')
	{
		write(1, "not a valid identifier", 23);
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

/*char	*key(char *str)
{
	int		i;
	char	*k_word;
	int		len;
	int		len_aux;

	i = 0;
	len_aux = 0;
	len = ft_strlen(str);
	while (str[i] && is_valid(str) == 0)
	{
		char	*aux;
		if (str[i] == '=')
		{
			aux = ft_strchr(str, '=');
			len_aux = ft_strlen(aux);
			len = (len - len_aux);
			break ;
		}
		i++;
	}
	k_word = (char *)ft_calloc(len + 1, sizeof(char));
	i = 0;
	if (str[i] && is_valid(str) == 0)
		ft_strlcpy(k_word, str, len + 1);
	else
		return (NULL);
	return (k_word);
}*/

char	*key(char *str)
{
	char	*aux;
	int		len;
	int		len_aux;

	if (!str || !*str)
		return (NULL);
	aux = ft_strchr(str, '=');
	if (aux == NULL)
		return (ft_strdup(str));
	len_aux = ft_strlen(aux);
	len = ft_strlen(str);
	len = len - len_aux;
	return (ft_substr(str, 0, len));
}

char	*value(char *str)
{
	int		i;
	
	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	else if (str[i] && str[i] == '=' && str[i + 1] == '\0')
		return (ft_calloc(1, sizeof(char)));
	else //if (str[i] && str[i] == '=' && str[i + 1] != '\0')
		return (ft_strdup(&str[++i]));
}

void	create_new_env(t_mini *mini, char *k, char *v)
{
	t_env	*current;
	t_env	*last_node;

	current = mini->env;
	while (current)
	{
		if (strcmp(k, current->key) == 0)
		{
			free(current->value);
			current->value = v;
			printf("Nuevo VALUE actualizado: %s\n",current->value);
			break ;
		}
		else if (current->next == NULL)
		{
			last_node = current;
			last_node->key = k;
			last_node->value = v;
			add_env_back(&last_node, last_node->key, last_node->value);
			break ;
		}
		current = current->next;
	}
}

int	ft_export(t_mini *mini, char **av)
{
	char	*k;
	char	*v;
	int		i;

	if (!av || !*av)
		return (1);
	i = 0;
	while (av[i])
	{
		if (is_valid(av[i][0]))
			return (1);
		k = key(av[i]);
		v = value(av[i]);
		create_new_env(mini, k, v);
		i++;
	}
	return (0);
}

void	order_env(t_mini *mini)
{
	t_env	*aux;
	char	*swap;
	int		i;
	int		len;

	aux = mini->env;
	i = 0;
	printf("llego\n");
	len = ft_lstsize(aux);
	printf("%d\n", len);
	while (i < len)
	{
		while (aux)
		{
			if (ft_strcmp(aux->key, aux->next->key) < 0)
			{
				swap = aux->key;
				aux->key = aux->next->key;
				aux->next->key = swap;
			}
			aux = aux->next;
		}
		i++;
	}

	aux = mini->env;
	while (aux)
	{
		ft_printf("declare -x ");
		ft_printf("%s=\"%s\"\n", aux->key, aux->value);
		aux = aux->next;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
/* 	char	*k;
	char	*v; */
	t_mini	mini;
	ft_bzero(&mini, sizeof(t_mini));
	mini.env = init_env(env);
	//ft_export(&mini, &av[i]);
	order_env(&mini);
/* 	while (av[i])
	{
		k = key(av[i]);
		v = value(av[i]);
		printf("Esta es la KEY: %s\n", k);
		printf("Este es el VALUE: %s\n", v);
		i++;
	} */
/* 	while (mini.env)
	{
		printf("%s=", mini.env->key);
		printf("%s\n", mini.env->value);
		mini.env = mini.env->next;
	} */
/* 	free(k);
	free(v); */
	free_env(&mini.env);
	return (0);
}
