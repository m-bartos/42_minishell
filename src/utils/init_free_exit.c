/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:24:15 by mbartos           #+#    #+#             */
/*   Updated: 2024/05/15 09:39:07 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes the minishell environment and command table.
 * 
 * This function initializes the command table and minishell data structures
 * using provided environment variables. It then exits the minishell and
 * cleans up resources.
 * 
 * @param minidata A pointer to the structure containing shell-related data.
 * @param cmd_tab A pointer to the command table to be initialized.
 * @param envp The environment variables to initialize the minishell with.
 */
void	init_minishell(t_minidata *minidata, t_cmd_tab *cmd_tab, char **envp)
{
	ft_init_cmd_tab(cmd_tab);
	ft_init_minidata(minidata, cmd_tab, envp);
	exit_minishell(minidata, 0);
	clean_minishell(minidata);
}

/**
 * @brief Cleans up minishell resources.
 * 
 * This function manages the cleanup of minishell resources, including
 * unlinking heredoc files and deleting commands in the command table. It uses
 * a static pointer to maintain a reference to the minishell data across
 * multiple calls.
 * 
 * @param minidata A pointer to the structure containing shell-related data,
 * or NULL to perform cleanup.
 */
void	clean_minishell(t_minidata *minidata)
{
	static t_minidata	*static_minidata;

	g_sigint_received = 0;
	if (minidata != NULL)
	{
		static_minidata = minidata;
		return ;
	}
	unlink_heredoc_files(static_minidata->cmd_tab);
	ft_delete_cmds_in_cmd_tab(static_minidata->cmd_tab);
}

/**
 * @brief Exits the minishell and performs necessary cleanup.
 * 
 * This function handles the exit process for the minishell, including
 * unlinking heredoc files, deleting commands, removing the environment list,
 * and freeing allocated memory. It uses a static pointer to maintain
 * a reference to the minishell data across multiple calls.
 * 
 * @param minidata A pointer to the structure containing shell-related data,
 * or NULL to perform cleanup and exit.
 * @param exit_status The exit status code to use when exiting the minishell.
 */
void	exit_minishell(t_minidata *minidata, int exit_status)
{
	static t_minidata	*static_minidata;

	if (minidata != NULL)
	{
		static_minidata = minidata;
		return ;
	}
	unlink_heredoc_files(static_minidata->cmd_tab);
	ft_delete_cmds_in_cmd_tab(static_minidata->cmd_tab);
	ft_remove_env_list(static_minidata->env_list);
	free(static_minidata->env_arr);
	exit(exit_status);
}

/**
 * @brief Cleans up command-related resources.
 * 
 * This function manages the cleanup of a command, including closing file
 * descriptors, freeing allocated memory for the EOF string, and deleting
 * the command structure. It uses static variables to maintain references to
 * the command data across multiple calls.
 * 
 * @param cmd A pointer to the command structure to be cleaned,
 * or NULL to perform cleanup.
 * @param fd The file descriptor to be closed, or 0 to indicate no file
 * descriptor operation.
 * @param eof The EOF string to be freed, or NULL to indicate no EOF operation.
 */
void	clean_cmd(t_cmd *cmd, int fd, char *eof)
{
	static t_cmd	*static_cmd;
	static int		static_fd;
	static char		*static_eof;

	if (cmd != NULL)
		static_cmd = cmd;
	if (fd != 0)
		static_fd = fd;
	if (eof != NULL)
		static_eof = eof;
	if (cmd == NULL && fd == 0 && eof == NULL)
	{
		close(static_fd);
		free(static_eof);
		ft_delete_cmd(static_cmd);
	}
}
