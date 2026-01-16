
#include "../minishell.h"

int	word_count(char *str)
{
	int		i;
	char	in_quotes;
	int		count;
	
	count = 0;
	in_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (is_space(str[i]) && in_quotes == 0)
			i++;
		update_quote_status(str[i], &in_quotes);
		/*if ((str[i] == '"' || str[i] == '\'') && in_quotes == 0)
			in_quotes = str[i];
		else if (str[i] == in_quotes)
			in_quotes = 0;*/
		if ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && in_quotes != 0)
			i++;
		else if (in_quotes == 0)
			count++;
		i++;
	}
	return (count);
}
