/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:48:32 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/03/24 15:54:08 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700
# define _POSIX_C_SOURCE 200809L
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# include "structs.h"
# include "lexer.h"
# include "parser.h"
# include "utils.h"
# include "executor.h"
# include "signals.h"
# include "error.h"
# include "builtins.h"

extern int	g_signal;

#endif
