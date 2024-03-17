/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:49:47 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/17 16:21:20 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Executes commands based on their types.
 *
 * Iterates through command tokens, executing each command according to its
 * type: regular commands, built-in commands, or error for command not found.
 *
 * @param cmd Pointer to the command structure to execute.
 */

void	ft_exec_commands(t_command *cmd, t_mini_data *minidata)
{
	t_token	*token;
	token = cmd->first_token;
	while (token)
	{
		if (token->type == CMD)
			ft_execve(cmd, minidata);
		else if (token->type == CMD_BUILT)
			ft_select_built_cmd(cmd);
		else if (token->type == CMD_ERR)
			ft_cmd_not_found(cmd);
		token = token->next;
	}
}

/**
 * @brief Wrapper function around the execve system call.
 *
 * Attempts to execute a command using execve. If execve fails, prints an
 * error message indicating the command was not found and exits with a
 * specific error code.
 *
 * @param cmd Pointer to the command containing the executable and arguments.
 */

void	ft_execve(t_command *cmd, t_mini_data *minidata)
{
	char	*error;
	char	*cmd_name;
	char	**envars;

	envars = ft_convert_list_to_arr(minidata->env_list);
	cmd_name = cmd->execve_cmd[0];
	error = ft_strjoin(cmd_name, ": command not found\n");
	if (execve(cmd->execve_cmd[0], cmd->execve_cmd, envars) - 1)
	{
		errno = ENOENT;
		if (errno == ENOENT)
		{
			ft_putstr_fd(error, STDERR);
			free(error);
			free(envars);
			exit(CMD_NOT_FOUND);
		}
	}
}

/**
 * @brief Selects and executes built-in shell commands.
 *
 * Determines which built-in command to execute based on the first token of
 * the command. Supports a set of predefined built-in commands like echo, pwd,
 * cd, and exit.
 *
 * @param cmd Pointer to the command to identify and execute the built-in command.
 */

void	ft_select_built_cmd(t_command *cmd)
{
	if (ft_strncmp(cmd->execve_cmd[0], "echo", 5) == 0)
		ft_echo(cmd, 1);
	else if (ft_strncmp(cmd->execve_cmd[0], "pwd", 4) == 0)
		ft_pwd(1);
	else if (ft_strncmp(cmd->execve_cmd[0], "cd", 3) == 0)
		ft_cd(cmd, 1);
	else if (ft_strncmp(cmd->execve_cmd[0], "exit", 5) == 0)
		ft_exit(cmd);
	//ft_printf("builtin func");
}

/**
 * @brief Handles execution of unrecognized commands.
 *
 * If a command is determined to be invalid or not found, prints an error
 * message indicating the command was not found and exits with a failure status.
 *
 * @param cmd Pointer to the command that was not recognized.
 */

void	ft_cmd_not_found(t_command *cmd)
{
	char	*error;
	char	*cmd_name;

	errno = ENOENT;
	cmd_name = cmd->execve_cmd[0];
	error = ft_strjoin(cmd_name, ": command not found\n");
	if (errno == ENOENT)
	{
		ft_putstr_fd(error, STDERR);
		free(error);
		exit(CMD_NOT_FOUND);
	}
	free(error);
	exit(EXIT_SUCCESS);
}
