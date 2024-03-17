/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:47:04 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/17 10:59:22 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Handles the parent process after forking.
 *
 * Waits for the child process to finish and adjusts file descriptors for
 * subsequent command execution in a pipeline. Closes the write-end of the
 * pipe and sets the read-end as the standard input for the next command.
 *
 * @param data Pointer to the execution data structure containing process
 *             and file descriptor information.
 */

void	ft_parent_process(t_exec_data *data)
{
	wait(&data->exit_status);
	data->fd_out = 1;
	close(data->pipe_fd[1]);
	data->fd_in = data->pipe_fd[0];
}

/**
 * @brief Initializes the execution data structure.
 *
 * Sets the initial values for the execution data, including zero exit status,
 * standard input for file descriptor in, and standard output for file descriptor
 * out.
 *
 * @param exec_data Pointer to the execution data structure to initialize.
 */

void	ft_init_exec_data(t_exec_data *exec_data)
{
	exec_data->exit_status = 0;
	exec_data->fd_in = STDIN;
	exec_data->fd_out = STDOUT;
}

/**
 * @brief Prints the exit status of a process.
 *
 * Checks if the process exited normally and prints the exit status. This is
 * useful for debugging and understanding the outcome of executed commands.
 *
 * @param status Pointer to the integer status returned by wait().
 */

void	ft_exit_status(int *status)
{
	if (WIFEXITED(*status))
	{
		ft_putnbr_fd(WEXITSTATUS(*status), 1);
		ft_putstr_fd("\n", 1);
	}
}
