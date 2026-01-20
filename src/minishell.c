/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:28:58 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/20 18:51:41 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/minishell.h"

/**
 * @brief Removes surrounding quotes from a string while handling nested quotes.
 *
 * This function iterates through the input string and copies characters to a
 * new string, omitting quoting characters (' or ") unless they are preserved
 * by context. It maintains a state to track whether the current character is
 * inside quotes to correctly handle nested or escaped sequences (though logic
 * for escaping is delegated to `update_quote_status`).
 *
 * @param input The input string containing potential quotes to be trimmed.
 * @return A newly allocated string with the quotes removed. The caller is
 *         responsible for freeing this memory.
 */
// static char	*trim_quotes(char *input)
// {
// 	int		i;
// 	int		j;
// 	char	quote;
// 	char	*result;

// 	i = 0;
// 	j = 0;
// 	quote = 0;
// 	result = malloc(ft_strlen(input) + 1);
// 	while (input[i])
// 	{
// 		update_quote_status(input[i], &quote);
// 		if (quote == 0 && (input[i] == '"' || input[i] == '\''))
// 			i++;
// 		else if (input[i] == quote && quote != 0)
// 			i++;
// 		else
// 		{
// 			result[j] = input[i];
// 			j++;
// 			i++;
// 		}
// 	}
// 	result[j] = '\0';
// 	return (result);
// }

char	*shell_loop(void)
{
	char	*input;
	t_token	*tokens;
/*
	Gestionar mas adelante el Enter sin salto de linea
*/
	tokens = NULL;
	while (1)
	{
		input = readline("Minishell$> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] != '\0')
		{
			input_to_token(input, &tokens);
		}
		free(input);
	}
	rl_clear_history();
	return (NULL);
}

int	main(void)
{
	shell_loop();
	return (0);
}
