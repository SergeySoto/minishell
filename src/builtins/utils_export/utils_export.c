#include "../../../includes/minishell.h"

int	is_valid(char *av)
{
	int	i;

	if (!av || av[0] == '\0')
		return (1);
	if (!(ft_isalpha(av[0])) && av[0] != '_')
		return (1);
	i = 1;
	while (av[i] && av[i] != '=')
	{
		if (!(ft_isalnum(av[i])) && av[i] != '_')
			return (1);
		i++;
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
		return (ft_strdup(""));
	else if (str[i] && str[i] == '=' && str[i + 1] == '\0')
		return (ft_calloc(1, sizeof(char)));
	else
		return (ft_strdup(&str[++i]));
}
