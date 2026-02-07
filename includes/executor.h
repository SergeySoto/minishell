/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 19:20:37 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/02/07 20:20:08 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

char	*get_env_val(char *name, t_mini *mini);
void	find_full_path(t_mini *mini);
void	get_cmd_path(char **path_env, t_cmd *cmd);
void	assign_full_path(char **path_env, t_cmd **cmd);


#endif