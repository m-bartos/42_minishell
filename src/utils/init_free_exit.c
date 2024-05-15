/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:24:15 by mbartos           #+#    #+#             */
/*   Updated: 2024/05/15 09:19:51 by mbartos          ###   ########.fr       */
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

	g_sigint_received = 0;
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
