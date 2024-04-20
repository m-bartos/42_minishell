/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:49:47 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/20 10:09:52 by aldokezer        ###   ########.fr       */
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

void	ft_exec_commands(t_cmd *cmd, t_mini_data *minidata)
{
	t_token	*token;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	token = cmd->first_token;
	while (token)
	{
		if (token->type == CMD)
			ft_execve(cmd, minidata);
		else if (token->type == CMD_BUILT)
			ft_select_built_cmd(cmd, *minidata->env_list);
		else if (token->type == CMD_ERR)
			ft_cmd_error(cmd);
		token = token->next;
	}
	exit_minishell(NULL, EXIT_SUCCESS);
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

void	ft_execve(t_cmd *cmd, t_mini_data *minidata)
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
			exit_minishell(NULL, CMD_NOT_FOUND);
		}
	}
}

/**
 * @brief Selects and executes built-in shell commands.
 *
 * Determines which built-in command to execute based on the
 * first token of the command. Supports a set of predefined
 * built-in commands like echo, pwd,
 * cd, and exit.
 *
 * @param cmd Pointer to the command to identify and execute
 * the built-in command.
 */

void	ft_select_built_cmd(t_cmd *cmd, t_env_list env_list)
{
	char	*cmd_name;

	cmd_name = cmd->execve_cmd[0];
	if (ft_strncmp(cmd_name, "echo", ft_strlen(cmd_name) + 1) == 0)
		ft_echo(cmd, NULL, 1);
	else if (ft_strncmp(cmd->execve_cmd[0], "pwd", 4) == 0)
		ft_pwd(NULL, 1);
	else if (ft_strncmp(cmd->execve_cmd[0], "cd", 3) == 0)
		ft_cd(cmd, NULL, 1);
	else if (ft_strncmp(cmd->execve_cmd[0], "exit", 5) == 0)
		ft_exit(cmd);
	else if (ft_strncmp(cmd->execve_cmd[0], "export", 7) == 0)
		ft_export(&env_list, cmd, 1);
	else if (ft_strncmp(cmd->execve_cmd[0], "unset", 6) == 0)
		ft_unset(&env_list, cmd, 1);
	else if (ft_strncmp(cmd->execve_cmd[0], "env", 4) == 0)
		ft_env(&env_list, 1);
}

/**
 * @brief Handles execution of unrecognized commands.
 *
 * If a command is determined to be invalid or not found, prints an error
 * message indicating the command was not found and exits with a failure status.
 *
 * @param cmd Pointer to the command that was not recognized.
 */

void	ft_cmd_error(t_cmd *cmd)
{
	char	*error;
	char	*cmd_name;

	cmd_name = cmd->execve_cmd[0];
	if (cmd_name == NULL)
		exit_minishell(NULL, IS_EMPTY);
	if (ft_is_path(cmd_name))
	{
		if (ft_is_path_valid(cmd->execve_cmd[0]))
		{
			if (access(cmd_name, F_OK | R_OK) == 0)
				ft_error(cmd_name, ": Is a directory\n", IS_DIRECTORY);
			else
				ft_error(cmd_name, ": Permission denied\n", PERMISSION_DENIED);
		}
		else
		{
			if (errno == ENOENT)
				ft_error(cmd_name, ": No such file or directory\n",
					NO_FILE_OR_DIR);
		}
	}
	else
		ft_error(cmd_name, ": command not found\n", CMD_NOT_FOUND);
}
