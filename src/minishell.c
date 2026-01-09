/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:28:58 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/09 15:03:35 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shell_loop()
{
	char *str;
	while(1)
	{
		str = readline("Minishell$>");
		if (str == NULL)
			continue ;
		else if (str)
			return (str);
	}
	return (str);
}

int main(void)
{
	shell_loop();
	return (0);
}