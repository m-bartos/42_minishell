/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:47:04 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/28 11:11:33 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Extracts the environment variable name from a string.
 *
 * This function takes a string in the format of "KEY=VALUE" and extracts the
 * "KEY" part, returning it as a newly allocated string. It uses '=' as the
 * delimiter to split the string and assumes the format is correct. The caller
 * is responsible for freeing the returned string.
 *
 * @param str The input string containing the environment variable in the
 *            format "KEY=VALUE".
 * @return A newly allocated string containing the extracted environment
 *         variable name. NULL is returned if an error occurs.
 */

char	*ft_extract_env_name(char *str)
{
	char	**str_arr;
	char	**tmp_str_arr;
	char	*temp;
	char	*env_name;

	env_name = NULL;
	str_arr = ft_split(str, '=');
	tmp_str_arr = str_arr;
	env_name = ft_strdup(str_arr[0]);
	while (*str_arr)
	{
		temp = *str_arr;
		free(temp);
		str_arr++;
	}
	free(tmp_str_arr);
	return (env_name);
}


/**
 * @brief Updates the shell's exit status.
 *
 * This function updates the shell's exit status based on the status of the last
 * executed command. If the command exited normally, the exit status is set to
 * the command's exit status. Otherwise, the raw status is used.
 *
 * @param status Pointer to the status returned by waitpid().
 * @param minidata Pointer to the shell's global data structure.
 *
 * The exit status is updated in the shell's environment variable list by
 * creating a new environment variable or updating the existing one. The
 * variable is named "?" and its value is set to the exit status.
 */

void	ft_update_exit_status(int *status, t_mini_data *minidata)
{
	char	*sta;
	char	*env;
	char	*temp;
	if (WIFEXITED(*status))
		sta = ft_itoa(WEXITSTATUS(*status));
	else
		sta = ft_itoa(*status);
	env = ft_strjoin("?=", sta);
	temp = ft_extract_env_name(env);
	ft_remove_env(minidata->env_list, temp);
	ft_add_env(minidata->env_list, env);
	free(sta);
	free(env);
	free(temp);
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

void	ft_parent_process(t_exec_data *data, t_mini_data *minidata, pid_t pid)
{
	int	status;

	status = -99;
	waitpid(pid, &status, 0);
	ft_update_exit_status(&status, minidata);
	close(data->ori_fd_in);
	close(data->ori_fd_out);
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
	exec_data->ori_fd_in = dup(STDIN);
	exec_data->ori_fd_out = dup(STDOUT);
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
