/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:07:41 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/20 10:40:59 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
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
			exit_minishell(NULL, 1);
		else
			ft_add_env(env_list, "?=1");
	}
	else
	{
		ft_putstr_fd(cwd, STDOUT);
		ft_putstr_fd("\n", STDOUT);
		free(cwd);
		if (is_child)
			exit_minishell(NULL, 0);
		else
			ft_add_env(env_list, "?=0");
	}
}
