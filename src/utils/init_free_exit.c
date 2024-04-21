/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:24:15 by mbartos           #+#    #+#             */
/*   Updated: 2024/04/21 20:31:41 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minidata *minidata, t_cmd_tab *cmd_tab, char **envp)
{
	ft_init_cmd_tab(cmd_tab);
	ft_init_minidata(minidata, cmd_tab, envp);
	exit_minishell(minidata, 0);
	clean_minishell(minidata);
}

void	clean_minishell(t_minidata *minidata)
{
	static t_minidata	*static_minidata;

	if (minidata != NULL)
	{
		static_minidata = minidata;
		return ;
	}
	unlink_heredoc_files(static_minidata->cmd_tab);
	ft_delete_cmds_in_cmd_tab(static_minidata->cmd_tab);
}

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
