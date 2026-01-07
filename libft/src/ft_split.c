/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:40:46 by carmegon          #+#    #+#             */
/*   Updated: 2025/12/01 21:36:36 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_free_all(char **list, int end_list)
{
	int	i;

	i = 0;
	while (i < end_list)
	{
		free(list[i]);
		i++;
	}
	free(list);
}

static int	ft_word_counter(char const *str, char c)
{
	int	i;
	int	words;
	int	flag;

	i = 0;
	flag = 1;
	words = 0;
	while (str[i])
	{
		if (str[i] == c)
			flag = 1;
		if (str[i] != c && flag)
		{
			flag = 0;
			words++;
		}
		i++;
	}
	return (words);
}

static char	**ft_fill_array(char **list, char const *str, int w_count, char c)
{
	int	i;
	int	word_len;

	i = 0;
	word_len = 0;
	while (i < w_count && *str)
	{
		while (*str == c)
			str++;
		word_len = 0;
		while (str[word_len] != c && str[word_len])
			word_len++;
		list[i] = ft_substr(str, 0, word_len);
		if (!list[i])
		{
			ft_free_all(list, i);
			return (NULL);
		}
		str = str + word_len + 1;
		i++;
	}
	list[i] = NULL;
	return (list);
}

char	**ft_split(char const *s, char c)
{
	int		w_count;
	char	**list;

	w_count = ft_word_counter(s, c);
	list = malloc((w_count + 1) * sizeof(char *));
	if (!list)
	{
		return (NULL);
	}
	list = ft_fill_array(list, s, w_count, c);
	return (list);
}

/* int	main(void)
{
	char	s1[] = "Hola buenos dias";
	char	**list = ft_split(s1, 32);
	int	i = 0;
	while (*list[i])
	{
		printf("%s\n", &*list[i]);
		i++;
	}
	return (0);
} */
