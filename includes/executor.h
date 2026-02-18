/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 19:20:37 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/02/18 16:50:54 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

char	*get_env_val(char *name, t_mini *mini);
void	find_full_path(t_mini *mini);
void	get_cmd_path(char **path_env, t_cmd *cmd);
void	assign_full_path(char **path_env, t_cmd **cmd);
int		is_builtin(char *cmd_name);
int		is_parent_builtin(char *cmd_name);
int		execute_builtin_func(t_mini *mini, t_cmd *cmd);
void	executor_dispatch(t_mini *mini);
void	handle_single_cmd(t_mini *mini, t_cmd *cmd);
void	handle_pipeline_loop(t_mini *mini);
int		setup_redirections(t_cmd *cmd);
int		backup_std_fds(t_mini *mini);
int		restore_std_fds(t_mini *mini);
void	execute_builtin_in_parent(t_mini *mini, t_cmd *cmd);
void	execute_command_node(t_mini *mini, t_cmd *cmd);
void	single_cmd_child_process(t_mini *mini, t_cmd *cmd);
void	single_cmd_parent_wait(t_mini *mini, t_cmd *cmd);
void	pipe_child_process(t_mini *mini, t_cmd *cmd, int prev_pipe, int *pipe_fd);
void	pipe_parent_process(t_cmd *cmd, int *prev_pipe, int *pipe_fd);
void	wait_all_children(t_mini *mini);
int		init_pipe(t_mini *mini, t_cmd *cmd, int prev_pipe, int *pipe_fd);
int		spawn_process(t_cmd *cmd, int prev_pipe, int *pipe_fd);

#endif