#include "../../includes/minishell.h"

/**
 * @brief Applies the input redirection for a command: dup2s fd_in to stdin
 *		if it is a heredoc FD, or opens infile and dup2s it.
 * @param cmd Pointer to the t_cmd node with fd_in and/or infile set.
 * @return 1 on success, 0 on dup2 or open failure.
 */
static int	setup_input(t_cmd *cmd)
{
	if (cmd->fd_in > 0)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return (close(cmd->fd_in), 0);
		close(cmd->fd_in);
	}
	if (cmd->infile)
	{
		cmd->fd_in = open(cmd->infile, O_RDONLY);
		if (cmd->fd_in == -1)
			return (ft_fprintf(2, ERR_ENV_NOT_FILORDIR, cmd->infile), 0);
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return (close(cmd->fd_in), 0);
		close(cmd->fd_in);
	}
	return (1);
}

/**
 * @brief Opens the output file specified in cmd->outfile with the correct
 *		flags (truncate or append) and stores the FD in cmd->fd_out.
 * @param cmd Pointer to the t_cmd node with outfile and append fields set.
 * @return 1 on success, 0 on open failure.
 */
static int	open_outfile(t_cmd *cmd)
{
	if (cmd->append == 1)
		cmd->fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		cmd->fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out == -1)
		return (ft_fprintf(2, ERR_ENV_NOT_FILORDIR, cmd->outfile), 0);
	return (1);
}

/**
 * @brief Applies the output redirection for a command: dup2s fd_out to stdout
 *		if it is already open, or opens outfile and dup2s it.
 * @param cmd Pointer to the t_cmd node with fd_out and/or outfile set.
 * @return 1 on success, 0 on dup2 or open failure.
 */
static int	setup_output(t_cmd *cmd)
{
	if (cmd->fd_out > 1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return (close(cmd->fd_out), 0);
		close(cmd->fd_out);
	}
	else if (cmd->outfile)
	{
		if (!open_outfile(cmd))
			return (0);
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return (close(cmd->fd_out), 0);
		close(cmd->fd_out);
	}
	return (1);
}

int	setup_redirections(t_cmd *cmd)
{
	if (!setup_input(cmd))
		return (0);
	if (!setup_output(cmd))
		return (0);
	return (1);
}
