/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:39:39 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/21 14:25:00 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Checks if the argument string represents a number.
 *
 * Evaluates whether the provided argument string can be converted to an
 * integer using `ft_atoi`. It returns 1 if the conversion is possible,
 * indicating the argument is numeric, otherwise returns 0.
 *
 * @param arg The string argument to check.
 * @return 1 if `arg` is a number, 0 otherwise.
 */

int	ft_is_arg_number(char *arg)
{
	if (!ft_atoi(arg))
		return (0);
	else
		return (1);
}

/**
 * @brief Converts a numeric argument string to an unsigned integer.
 *
 * First checks if the argument string represents a numeric value using
 * `ft_is_arg_number`. If yes, converts the string to an unsigned integer
 * and updates `arg_number`. Returns 0 on success, 1 if the argument is not
 * numeric.
 *
 * @param arg The string argument to convert.
 * @param arg_number Pointer to store the converted unsigned int value.
 * @return 0 on successful conversion, 1 if `arg` is not a number.
 */

int	ft_convert_arg_number(char *arg, unsigned int *arg_number)
{
	if (ft_is_arg_number(arg))
	{
		*arg_number = (unsigned int) ft_atoi(arg);
		return (0);
	}
	else
		return (1);
}

/**
 * @brief Handles the exit process for commands with exactly two arguments.
 *
 * This function is called when an exit command is issued with exactly one
 * argument. It checks if the argument is numeric. If not, it outputs an
 * error message and sets the environment variable `?` to 2. If the argument
 * is numeric, it converts it to an unsigned integer, prints "exit", and
 * exits the shell with the converted argument value as the exit status.
 *
 * @param cmd Pointer to the command structure.
 * @param env_list Pointer to the environment list structure.
 * @param arg_number Pointer to store the numeric argument value.
 */

void	ft_echo_cmd_size_2(t_cmd *cmd, t_env_list *env_list,
		unsigned int *arg_number, t_exec_data *data)
{
	char				*arg;

	arg = cmd->execve_cmd[1];
	if (!ft_is_arg_number(arg))
	{
		ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
		ft_add_env(env_list, "?=2");
	}
	else
	{
		ft_convert_arg_number(arg, arg_number);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		if (data != NULL)
		{
			close(data->ori_fd_in);
			close(data->ori_fd_out);
		}
		exit_minishell(NULL, (unsigned int) *arg_number);
	}
}

/**
 * @brief Exits mini-shell or handles errors based on command arguments.
 *
 * Implements exit behavior for a mini-shell. Checks the number of arguments
 * provided and acts accordingly:
 * - With only the exit command, exits the shell successfully.
 * - With one additional argument, processes it accordingly.
 * - With more than one additional argument, reports an error.
 *
 * @param cmd Pointer to t_cmd with the parsed command and its arguments.
 *            Includes a size attribute indicating the number of arguments.
 * @param env_list Pointer to t_env_list representing environment variables.
 *                 May be modified to set environment variables as a result
 *                 of the command's execution.
 *
 * @note Can terminate the program with `exit(EXIT_SUCCESS)` if the exit
 *       conditions are met. If there are too many arguments, sets an
 *       environment variable (?) to 1, indicating an error, but does not exit.
 */

void	ft_exit_minishell(t_cmd *cmd, t_env_list *env_list, t_exec_data *data)
{
	unsigned int	arg_number;

	if (cmd == NULL || cmd->size == 1)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		if (data != NULL)
		{
			close(data->ori_fd_in);
			close(data->ori_fd_out);
		}
		exit_minishell(NULL, EXIT_SUCCESS);
	}
	else if (cmd->size == 2)
		ft_echo_cmd_size_2(cmd, env_list, &arg_number, data);
	else if (cmd->size > 2)
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		ft_add_env(env_list, "?=1");
	}
}

/**
 * @brief Exits the child process when 'exit' command is encountered.
 *
 * Checks if the command to execute is 'exit'. If so, it terminates the
 * current process. This function is specifically useful for handling 'exit'
 * commands that are nested within a pipeline, causing only the child process
 * to exit.
 *
 * @param cmd Pointer to the command structure to check for 'exit'.
 */

void	ft_exit(t_cmd *cmd)
{
	if (ft_strncmp(cmd->execve_cmd[0], "exit", 5) == 0)
		exit_minishell(NULL, EXIT_SUCCESS);
}
