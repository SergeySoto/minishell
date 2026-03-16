#include "../../../includes/minishell.h"

void	swap_nodes(t_mini *mini)
{
	char	*swap_key;
	char	*swap_value;
	t_env	*aux;

	aux = mini->env;
	while (aux)
	{
		if (aux->next != NULL && (ft_strcmp(aux->key, aux->next->key) > 0))
		{
			swap_key = aux->key;
			aux->key = aux->next->key;
			aux->next->key = swap_key;
			swap_value = aux->value;
			aux->value = aux->next->value;
			aux->next->value = swap_value;
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
		if (aux->value == NULL)
		{
			ft_printf("declare -x ");
			ft_printf("%s\n", aux->key);
		}
		else
		{
			ft_printf("declare -x ");
			ft_printf("%s=\"%s\"\n", aux->key, aux->value);
		}
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
