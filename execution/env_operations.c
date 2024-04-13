/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:43:53 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/13 20:33:05 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_export(t_env_list *env_list, int is_child,
		int exit_code, int is_ident)
{
	if (is_child)
		exit_minishell(NULL, exit_code);
	else
	{
		if (is_ident == 1)
			ft_putstr_fd(" not a valid identifier\n", STDERR);
		if (exit_code == 1)
			ft_add_env(env_list, "?=1");
		else
			ft_add_env(env_list, "?=0");
		return ;
	}
}

void	ft_shorter_export(t_env_list *env_list, t_cmd *cmd, int is_child)
{
	char	*key;

	if (ft_is_cmd_valid_export(cmd))
	{
		key = ft_extract_key(cmd->execve_cmd[1]);
		if (ft_is_key_valid(key))
		{
			ft_add_env(env_list, cmd->execve_cmd[1]);
			ft_add_env(env_list, "?=0");
			free(key);
			return ;
		}
		else
		{
			free(key);
			ft_exit_export(env_list, is_child, 1, 1);
		}
	}
	else
		ft_exit_export(env_list, is_child, 1, 1);
}
/**
 * @brief Adds an environment variable to the list, exits if not child
 *        process.
 * Adds an environment variable found via command to the environment list.
 * Terminates the program if the operation is performed at the top level
 * (not nested).
 *
 * @param env_list Pointer to the list where the variable will be added.
 * @param cmd Pointer to the command structure for finding the argument.
 * @param is_nested Flag indicating if the operation is nested. Exits the
 *                  program if false and the addition is successful.
 */

void	ft_export(t_env_list *env_list, t_cmd *cmd, int is_child)
{
	char	*key;
	char	*value;

	if (cmd->size == 1)
		ft_exit_export(env_list, is_child, 1, 0);
	else if (cmd->size > 1 && ft_strncmp(cmd->execve_cmd[1],
			"=", ft_strlen(cmd->execve_cmd[1] + 1)) == 0)
		ft_exit_export(env_list, is_child, 1, 1);
	else if (cmd->size > 1 && !ft_is_cmd_valid_export(cmd)
		&& ft_is_str_digit(cmd->execve_cmd[1]))
		ft_exit_export(env_list, is_child, 1, 1);
	else if (cmd->size > 1 && !ft_is_cmd_valid_export(cmd)
		&& !ft_is_key_valid(cmd->execve_cmd[1]))
		ft_exit_export(env_list, is_child, 1, 1);
	else if (cmd->size > 1 && !ft_is_cmd_valid_export(cmd))
		ft_exit_export(env_list, is_child, 0, 0);
	else if (cmd->size > 1)
		ft_shorter_export(env_list, cmd, is_child);
}

/**
 * @brief Removes an environment variable, exits if in a child process.
 *
 * Searches and removes a specified environment variable from the given list.
 * If executed within a child process (is_child true) and removal is successful,
 * it exits the program.
 *
 * @param env_list Pointer to the list from which the variable is removed. The
 *                 list is modified in place.
 * @param cmd Pointer to a command structure containing the variable name to
 *            remove.
 * @param is_child Flag indicating if operation occurs within a child process.
 *                 If true and removal is successful, the function exits the
 *                 program.
 */

void	ft_unset(t_env_list *env_list, t_cmd *cmd, int is_child)
{
	char	*arg;

	arg = ft_find_arg(cmd);
	ft_remove_env(env_list, arg);
	if (is_child)
		exit_minishell(NULL, 0);
	else
		ft_add_env(env_list, "?=0");
}

/**
 * @brief Displays environment variables, exits if in a child process.
 *
 * Iterates over the environment list, displaying each variable using
 * ft_list_env. If called within a child process (as indicated by is_child),
 * it terminates the program after displaying the variables.
 *
 * @param env_list Pointer to the list containing environment variables.
 * @param is_child Flag indicating if the function is called within a child
 *                 process. If non-zero, the program exits after displaying.
 */

void	ft_env(t_env_list *env_list, int is_child)
{
	ft_list_env(env_list);
	if (is_child)
		exit_minishell(NULL, 0);
	else
		ft_add_env(env_list, "?=0");
}
