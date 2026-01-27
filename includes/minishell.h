/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 20:03:15 by carmegon          #+#    #+#             */
/*   Updated: 2026/01/27 17:44:47 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# include "structs.h"
# include "lexer.h"
# include "parser.h"
# include "utils.h"

// FUNCIONES BUILTINS AQUI POR AHORA
int	ft_pwd(void);
int	ft_env(t_mini *mini, char **av);

#endif
