/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:01:44 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/21 19:41:33 by aldokezer        ###   ########.fr       */
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
	char		*error;
	char		*path;

	path = ft_find_arg(cmd);
	if (chdir(path) != 0)
	{
		if (errno == ENOENT)
		{
			error = ft_strjoin("cd: no such file or directory: ", path);
			ft_putstr_fd(error, STDERR);
			ft_putstr_fd("\n", STDERR);
			free(error);
			if (is_child)
				exit(1);
			else
				ft_add_env(env_list, "?=1");

		}
		else
		{
			perror("cd");
			if (is_child)
				exit(1);
			else
				ft_add_env(env_list, "?=1");
		}
	}
	else
	{
		ft_add_env(env_list, "?=0");
		ft_update_pwd(env_list);
	}
	if (is_child)
		exit(0);
}

/**
 * @brief Prints the current working directory.
 *
 * Outputs the current working directory to standard output. If executed
 * within a child process and an error occurs, it exits with status 1.
 * On success, exits with status 0 if in a child process.
 *
 * @param is_child Indicates if the function is called within a child process.
 *                 Non-zero values trigger process exit after execution.
 */

void	ft_pwd(t_env_list *env_list, int is_child)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd: ");
		free(cwd);
		if (is_child)
			exit(1);
		else
			ft_add_env(env_list, "?=1");
	}
	else
	{
		ft_putstr_fd(cwd, STDOUT);
		ft_putstr_fd("\n", STDOUT);
		free(cwd);
		if (is_child)
			exit(0);
		else
			ft_add_env(env_list, "?=0");
	}
}
