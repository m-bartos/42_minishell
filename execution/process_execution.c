/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:35:56 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/18 11:44:09 by aldokezer        ###   ########.fr       */
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
	if(data->fd_in != STDIN_FILENO)
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
	if(cmd->next != NULL)
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
	pid_t	pid;
// By now we have opened 5 file descriptors that are connected to 3 files
	ft_init_exec_data(&data);
	cmd = tab->first_cmd;

	pid_t *child_pids;       // Array to store child PIDs
    int num_children;
	int num_commands = tab->size;
	child_pids = malloc(sizeof(pid_t) * num_commands);
	num_children = 0;
	while (cmd)
	{
		if(cmd->next != NULL)
			pipe(data.pipe_fd);
// By now we have opened 7 file descriptors that are connected to 3 files and 1 pipe buffer
		pid = fork();
		if (pid == 0)
		{
			ft_redirect_io(cmd, &data.fd_in, &data.fd_out);
			ft_redir_process_io(&data, cmd);
			ft_exec_commands(cmd, minidata);
		}
		else
		{
			child_pids[num_children++] = pid;
			if (data.fd_in != STDIN_FILENO)
				close(data.fd_in);
			if (cmd->next != NULL)
			{
				close(data.pipe_fd[1]);
				data.fd_in = data.pipe_fd[0];
			}
		}
		cmd = cmd->next;
	}
	int	status;

	status = 0;
	// waitpid(pid, &status, 0);
	//int status;

    for (int i = 0; i < num_children; i++)
	{
        waitpid(child_pids[i], &status, 0);
        ft_update_exit_status(&status, minidata);
    }
	//ft_update_exit_status(&status, minidata);
	close(data.ori_fd_in);
	close(data.ori_fd_out);
	//ft_parent_process(&data, minidata, pid);
}

		// int status;
		// pid_t child_pid;
		// child_pid = waitpid(-1, &status, 0);
