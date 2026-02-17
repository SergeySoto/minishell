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

int	is_valid(char *str)
{
	if (!str || !*str)
		return (1);
	else if (ft_isdigit(str[0]) || str[0] == '=')
	{
		write(1, "not a valid identifier", 23);
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

char	*key(char *str)
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
			len = (len - len_aux) + 1;
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
}

char	*value(char *str)
{
	int		i;
	int		len_content;
	char	*content;
	
	i = 0;
	content = NULL;
	while(str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	if (str[i] && str[i] == '=' && str[i + 1] == '\0')
	{
		char	*empty;
		i++;
		empty = ft_calloc(1 ,sizeof(char));
		return (empty);
	}
	if (str[i] && str[i] == '=' && str[i + 1] != '\0')
	{
		i++;
		len_content = ft_strlen(&str[i]);
		content = ft_calloc(len_content + 1, sizeof(char));
		ft_strlcpy(content, &str[i], len_content + 1);
	}
	return (content);
}


int	ft_export(t_mini *mini, int ac, char **av)
{
	char	*k;
	char	*v;
	t_env	*current;
	int		i;

	i = 1;
	k = key(av[i]);
	v = value(av[i]);
	current = mini->env;
	while (current)
	{
		if (strncmp(k, current->key, ft_strlen(k)) == 0)
		{
			free(current->value);
			current->value = v;
		}
		current = current->next;
	}
}

int	main(int ac, char **av)
{
	(void)ac;
	int i = 1;
	char	*k;
	char	*v;
	while (av[i])
	{
		//key(av[i]);
		k = key(av[i]);
		v = value(av[i]);
		printf("Esta es la KEY: %s\n", k);
		printf("Este es el VALUE: %s\n", v);
		i++;
	}
	free(k);
	free(v);
	return (0);
}
