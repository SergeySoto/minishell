//#include "../../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	len_s;

	len_s = ft_strlen(s);
	write(fd, s, len_s);
}

// Funcion para checkear el comando -n valido
int	check_flag(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	
	i = 0;
	if (str[0] != '-' || str[i + 1] == '\0')
		return (0);
	else
		i++;

	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **av)
{
	int	i;
	int	j;

	if (!av || !*av)
		return (0);
	
	i = 1;
	j = 0;
	while (av[i])
	{
		if (check_flag(av[i]) == 0)
		{
			ft_putstr_fd(av[i], 1);
		}
		i++;
	}
	return (1);
}

int main(int ac, char **av)
{
	(void)ac;

	ft_echo(&*av);
	return (0);
}