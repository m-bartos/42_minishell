/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:35:56 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/21 09:17:13 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Redirects I/O for a child process after forking.
 *
 * Adjusts standard input and output for the child process based on execution
 * data. If the command is part of a pipeline and has no output redirection,
 * stdout is redirected to a pipe. Otherwise, stdout is redirected to the
 * specified file descriptor.
 *
 * @param data Pointer to the execution data containing file descriptors.
 * @param cmd Pointer to the current command being executed.
 */

void	ft_redir_process_io(t_exec_data *data, t_cmd *cmd)
{
	dup2(data->fd_in, STDIN);
	if (cmd->next != NULL && (ft_has_out_redir(cmd) == 0))
		dup2(data->pipe_fd[1], STDOUT);
	else
		dup2(data->fd_out, STDOUT);
	close(data->pipe_fd[0]);
}

/**
 * @brief Executes commands from a command table.
 *
 * Iterates through commands in a command table, creating a pipe and forking
 * for each command. In the child process, performs I/O redirection and
 * executes the command. The parent process waits for the child to finish.
 *
 * @param tab Pointer to the command table containing commands to execute.
 */

void	ft_exec_input(t_cmd_tab *tab, t_mini_data *minidata)
{
	t_exec_data data;
	t_cmd	*cmd;

	ft_init_exec_data(&data);
	cmd = tab->first_cmd;
	while (cmd)
	{
		pipe(data.pipe_fd);
		if (fork() == 0)
		{
			ft_redirect_io(cmd, &data.fd_in, &data.fd_out);
			ft_redir_process_io(&data, cmd);
			ft_exec_commands(cmd, minidata);
		}
		else
			ft_parent_process(&data, minidata);
		cmd = cmd->next;
	}
}
