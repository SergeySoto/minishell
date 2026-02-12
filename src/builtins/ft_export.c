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
	int	i;
	if (!str || !*str)
		return (1);
	
		i = 0;
		while (str[i])
		{
			if (ft_isdigit(str[0]) || str[0] == '=')
			{
				write(1, "not a valid identifier", 23);
				write(1, '\n', 1);
				return (1);
			}
			
		}
}

/*
int	ft_export(char **env, char **av)
{

} */