#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>

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
	else
		return (ft_strdup(&str[++i]));
}

void	create_new_env(t_mini *mini, char *k, char *v)
{
	t_env	*current;

	current = mini->env;
	while (current)
	{
		if (ft_strcmp(k, current->key) == 0)
		{
			free(current->value);
			current->value = v;
			break ;
		}
		else if (current->next == NULL)
		{
			printf("Este es mi ultimo nodo %s\n", current->key);
			printf("Esta es el value de mi ultimo nodo %s\n", current->value);
			add_env_back(&(mini->env), k, v);
			current = current->next;
			printf("Este es mi ultimo nuevo nodo %s\n", current->key);
			printf("Esta es el value de mi nuevo ultimo nodo %s\n", current->value);
			break ;
		}
		current = current->next;
	}
}

int	update_or_add_env(t_mini *mini, char **av)
{
	char	*k;
	char	*v;
	int		i;

	if (!av || !*av)
		return (1);
	i = 1;
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

void	swap_nodes(t_mini *mini)
{
	char	*swap;
	t_env	*aux;

	aux = mini->env;
	while (aux)
	{
		if (aux->next != NULL && (ft_strcmp(aux->key, aux->next->key) > 0))
		{
			swap = aux->key;
			aux->key = aux->next->key;
			aux->next->key = swap;
		}
		aux = aux->next;
	}
}

void	print_order_env(t_mini *mini)
{
	t_env	*aux;

	aux = mini->env;
	while (aux)
	{
		ft_printf("declare -x ");
		ft_printf("%s=\"%s\"\n", aux->key, aux->value);
		aux = aux->next;
	}
}

int	order_env(t_mini *mini)
{
	t_env	*aux;
	int		i;
	int		len;

	aux = mini->env;
	if (!aux)
		return (0);
	len = ft_lstsize(aux);
	i = 0;
	while (i < len)
	{
		aux = mini->env;
		swap_nodes(mini);
		i++;
	}
	print_order_env(mini);
	return (0);
}

int	ft_export(t_mini *mini, char **av)
{
	int	i;
	if (!av || !*av)
		return (0);
	i = 0;
	if (av[0] && !av[i + 1])
	{
		order_env(mini);
	}
	else
	{
		update_or_add_env(mini, av);
	}
	return (0);
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
	//int i = 1;
	//printf("%s\n", av[1]);
	ft_export(&mini, &av[1]);
	//print_env(mini.env);
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
