/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:47:04 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/17 15:29:08 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Updates the shell's exit status environment variable.
 *
 * Converts the exit status to a string and updates the special '?' environment
 * variable to reflect this status in the shell's environment list. This allows
 * the shell to track and provide the exit status of the last executed command.
 *
 * @param status Pointer to the integer holding the exit status to update.
 * @param minidata Pointer to the shell's main data structure containing the
 *                 environment list.
 */

void	ft_update_exit_status(int *status, t_mini_data *minidata)
{
	char	*sta;
	char	*env;

	sta = ft_itoa(*status);
	env = ft_strjoin("?=", sta);
	ft_add_env(minidata->env_list, env);
	free(sta);
	free(env);
}

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

void	ft_parent_process(t_exec_data *data, t_mini_data *minidata)
{
	int	status;

	status = -340;
	wait(&status);
	ft_update_exit_status(&status, minidata);
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
