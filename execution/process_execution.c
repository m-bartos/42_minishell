/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:35:56 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/18 21:48:44 by aldokezer        ###   ########.fr       */
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
	dup2(data->fd_in, STDIN_FILENO);
	if (data->fd_in != STDIN_FILENO)
		close(data->fd_in);
	if (cmd->next != NULL && (ft_has_out_redir(cmd) == 0))
	{
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[1]);
	}
	else
	{
		dup2(data->fd_out, STDOUT_FILENO);
		if (data->fd_out != STDOUT_FILENO)
			close(data->fd_out);
		if (cmd->next != NULL)
			close(data->pipe_fd[1]);
	}
	if (cmd->next != NULL)
		close(data->pipe_fd[0]);
	close(data->ori_fd_in);
	close(data->ori_fd_out);
}
// OLD Version was closing to much!
/*
{
	dup2(data->fd_in, STDIN);
	if (cmd->next != NULL && (ft_has_out_redir(cmd) == 0))
		dup2(data->pipe_fd[1], STDOUT);
	else
		dup2(data->fd_out, STDOUT);
	if(data->fd_in != STDIN)
		close(data->fd_in);
	if (data->fd_out != STDOUT)
		close(data->fd_out);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(data->ori_fd_in);
	close(data->ori_fd_out);
}
*/

void	ft_child_process(t_exec_data *data, t_mini_data *minidata)
{
	ft_redirect_io(data->cmd, &data->fd_in, &data->fd_out);
	ft_redir_process_io(data, data->cmd);
	ft_exec_commands(data->cmd, minidata);
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
	t_exec_data	data;

	ft_init_exec_data(&data, tab);
	while (data.cmd)
	{
		if (data.cmd->next != NULL)
			pipe(data.pipe_fd);
		data.pid = fork();
		if (data.pid == 0)
			ft_child_process(&data, minidata);
		else
		{
			data.child_pids[data.num_children++] = data.pid;
			if (data.fd_in != STDIN_FILENO)
				close(data.fd_in);
			if (data.cmd->next != NULL)
			{
				close(data.pipe_fd[1]);
				data.fd_in = data.pipe_fd[0];
			}
		}
		data.cmd = data.cmd->next;
	}
	ft_parent_process(&data, minidata, data.pid);
}
