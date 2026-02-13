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
	printf("Len de mi str: %d\n", len);
	while (str[i] && is_valid(str) == 0)
	{
		char	*aux;
		if (str[i] == '=')
		{
			aux = ft_strchr(str, '=');
			len_aux = ft_strlen(aux);
			printf("Len de mi aux: %d\n", len_aux);
			len = (len - len_aux) + 2;
			printf("Len que quiero para mi k_word: %d\n", len);
			break ;
		}
		i++;
	}
	k_word = (char *)ft_calloc(len + 1, sizeof(char));
	//k_word = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	if (str[i] && is_valid(str) == 0)
		ft_strlcpy(k_word, str, len);
	else
		return (NULL);
	k_word[len] = '\0';
	while (i < len)
	{
		printf("Esta es la KEY: %c\n", k_word[i]);
		i++;
	}
	return (k_word);
}

char	*value(char *str)
{
	int		i;
	int		j;
	char	*name;
	
	name = key(str);
	i = 0;
	j = 0;
	while(name[i] && name[i] != '=')
		i++;
	if (!name[i])
	{
		str[j] = name[i];
		return (str);
	}
	if (name[i] && name[i] == '=' && name[i + 1] == '\0')
	{
		i++;
		while (name[i])
		{
			str[j] = name[i];
			return (str);
		}
	}
	if (name[i] && name[i] == '=' && name[i + 1] != '\0')
	{
		i++;
		while (name[i])
		{
			str[j] = name[i];
			write(1, &str[j], 1);
			j++;
			i++;
		}
	}
	return (str);
}

/*
int	ft_export(char **env, char **av)
{

} */

int	main(int ac, char **av)
{
	(void)ac;
	int i = 1;
	while (av[i])
	{
		key(av[i]);
		i++;
	}
	//value(av[i]);
	return (0);
}