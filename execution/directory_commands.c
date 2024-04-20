/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:01:44 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/20 10:50:32 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			ft_cd_not_valid_path(env_list, is_child, path);
		else
			ft_cd_valid_path(env_list, is_child);
	}
	else if (cmd->size > 2)
		ft_too_many_args(env_list, is_child);
}
