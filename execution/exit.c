/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:39:39 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/18 18:50:18 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Exits the minishell program if 'exit' is the only command.
 *
 * Checks if the first command in the command table is 'exit' and if it's
 * the only command present. If both conditions are met, it exits the
 * minishell program. This function is intended for use when 'exit' is not
 * nested within a pipeline and should perform necessary cleanup before exiting.
 *
 * @param tab Pointer to the command table containing all parsed commands.
 */

void	ft_exit_minishell(t_cmd_tab *tab)
{
	t_cmd	*cmd;

	cmd = tab->first_cmd;
	if (ft_strncmp(cmd->execve_cmd[0], "exit", 5) == 0 && tab->size == 1)
	{
		// add cleaning function - to clean the tab or add at_exit()
		exit(EXIT_SUCCESS);
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
		exit(EXIT_SUCCESS);
}
