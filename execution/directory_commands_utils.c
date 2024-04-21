/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_commands_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:48:30 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/21 19:36:41 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_too_many_args(t_env_list *env_list, int is_child)
{
	if (is_child)
		exit_minishell(NULL, 1);
	else
	{
		ft_add_env(env_list, "?=1");
		ft_putstr_fd("cd: too many arguments\n", STDERR);
	}
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

void	ft_cd_not_valid_path(t_env_list *env_list, int is_child, char *path)
{
	char	*error;

	if (path != NULL)
		error = ft_strjoin_e(path, ": No such file or directory\n");
	else
		error = ft_strjoin_e("", " No such file or directory\n");
	ft_putstr_fd(error, STDERR_FILENO);
	free(error);
	if (is_child)
		exit_minishell(NULL, 1);
	else
		ft_add_env(env_list, "?=1");
}

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
	env = ft_strjoin_e("PWD=", cwd);
	ft_add_env(env_list, env);
	free(cwd);
	free(env);
}
