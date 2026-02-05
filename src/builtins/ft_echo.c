//#include "../../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

//! -- ESTAS 3 PRIMERAS FUNCIONES VAN FUERA DESPUES AL INCLUIRLAS EN EL PROGRAMA --//
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

// Funcion que me imprime sin el salto de linea.
// Cambiar el parametro por la struct t_cmd **argv
int	whitout_n(char **av)
{
	int	i;
	if (!av || !*av)
		return (0);

	i = 0;
	while (check_flag(av[i]) == 1)
		i++;
	while (av[i])
	{
		if (av[i + 1] == NULL)
			ft_putstr_fd(av[i], 1);
		else
		{
			ft_putstr_fd(av[i], 1);
			write(1, " ", 1);
		}
		i++;
	}
	return (1);
}

// Cambiar el parametro por la struct t_cmd **argv
int	whit_n(char **av)
{
	int	i;

	if (!av || !*av)
		return (0);
	
	i = 1;
	while (av[i])
	{
		if (av[i + 1] == NULL)
		{
			ft_putstr_fd(av[i], 1);
			write(1, "\n", 1);
		}
		else
		{
			ft_putstr_fd(av[i], 1);
			write(1, " ", 1);
		}
			i++;
	}
	return (1);
}

// Cambiar el parametro por la struct t_cmd **argv
//! CUIDADO: Tengo la i = 2 para eliminar la impresion del programa y del comando 'echo'
int	ft_echo(char **av)
{
	if (!av || !*av)
		return (0);
	
	if (check_flag(av[1]) == 1)
		whitout_n(&av[1]);
	else
		whit_n(av);
	return (1);
}

/* 	while (av[i])
	{
		if (check_flag(av[i]) == 0 && av[i + 1] == NULL)
		{
			ft_putstr_fd(av[i], 1);
			write(1, "\n", 1);
		}
		else if (check_flag(av[i]) == 0)
		{
			ft_putstr_fd(av[i], 1);
			write(1, " ", 1);
		}
		i++;
	} */

int main(int ac, char **av)
{
	(void)ac;

	//whitout_n(&*av);
	ft_echo(&av[1]);
	return (0);
}