/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:01:44 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/29 10:19:58 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Finds the first argument in a command.
 *
 * Iterates through the tokens of a given command to find the first token
 * that is marked as an argument (ARG). Returns the text of the first ARG
 * token found, or NULL if no ARG token is present.
 *
 * @param cmd Pointer to the command structure to search for an argument.
 * @return Pointer to the text of the first argument found, or NULL if none.
 */

char	*ft_find_arg(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token)
	{
		if (token->type == ARG)
			return (token->text);
		token = token->next;
	}
	return (NULL);
}

void	ft_update_pwd(t_env_list *env_list)
{
	char	*cwd;
	char	*env;

	cwd = getcwd(NULL, 0);
	env = ft_strjoin("PWD=", cwd);
	ft_add_env(env_list, env);
	free(cwd);
	free(env);
}

void	ft_cd_not_valid_path(t_env_list *env_list, int is_child)
{
	ft_putstr_fd("No such file or directory:\n", STDERR_FILENO);
	if (is_child)
		exit_minishell(NULL, 1);
	else
		ft_add_env(env_list, "?=1");
}

void	ft_cd_valid_path(t_env_list *env_list, int is_child)
{
	if (is_child)
		exit_minishell(NULL, 0);
	else
	{
		ft_add_env(env_list, "?=0");
		ft_update_pwd(env_list);
	}
}

/**
 * @brief Changes the current directory and handles errors.
 *
 * Attempts to change the current working directory to the one specified in
 * the command. If the operation fails due to the target directory not being
 * found, an error message is displayed. Exits if in a child process,
 * depending on the outcome of the operation.
 *
 * @param cmd Pointer to the command structure containing the target directory.
 * @param is_child Flag indicating if the function is called in a child process.
 *                 Exits with status 1 on failure, 0 on success if true.
 */

void	ft_cd(t_cmd *cmd, t_env_list *env_list, int is_child)
{
	char	*path;

	if (cmd->size == 1)
	{
		if (is_child)
			exit_minishell(NULL, 1);
		else
			ft_add_env(env_list, "?=0");
	}
	else if (cmd->size == 2)
	{
		path = ft_find_arg(cmd);
		if (chdir(path) != 0)
			ft_cd_not_valid_path(env_list, is_child);
		else
			ft_cd_valid_path(env_list, is_child);
	}
	else if (cmd->size > 2)
	{
		if (is_child)
			exit_minishell(NULL, 1);
		else
		{
			ft_add_env(env_list, "?=1");
			ft_putstr_fd("cd: too many arguments\n", STDERR);
		}
	}
}
