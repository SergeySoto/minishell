/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:12:44 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/03/10 19:12:16 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**c_mem(int n_words)
{
	char	**words;

	words = malloc((n_words + 1) * sizeof(char *));
	if (!words)
	{
		free(words);
		return (NULL);
	}
	return (words);
}

char	**smart_split(char *input)
{
	char	**words;

	if (!input)
		return (NULL);
	words = c_mem(word_count(input));
	if (!words)
		return (NULL);
	fill_mem(words, input);
	return (words);
}
