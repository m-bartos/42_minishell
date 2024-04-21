/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:24:15 by mbartos           #+#    #+#             */
/*   Updated: 2024/04/21 13:10:45 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_exit(char *line)
{
	if (line == NULL || ft_strncmp(line, "exit", 5) == 0)
	{
		printf("exit\n");
		free(line);
		printf(RESET);
		exit(0);
	}
}

void	clean_minishell(t_minidata *minidata)
{
	t_minidata static	*static_minidata;

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
	t_minidata static	*static_minidata;

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
