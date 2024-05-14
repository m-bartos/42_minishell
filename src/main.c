/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/14 17:36:30 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_line(t_minidata *minidata)
{
	char	*prompt;
	char	*line;
	int		status;

	status = 0;
	prompt = get_prompt(minidata);
	line = readline(prompt);
	free(prompt);
	if (g_sigint_received == 130)
	{
		status = g_sigint_received;
		ft_update_exit_status(&status, minidata);
		g_sigint_received = 0;
	}
	return (line);
}

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
		char **envp)
{
	char		*line;
	t_cmd_tab	cmd_tab;
	t_minidata	minidata;

	init_minishell(&minidata, &cmd_tab, envp);
	line = NULL;
	while (1)
	{
		disable_ctrl_c_output();
		setup_signal_handling();
		line = ft_read_line(&minidata);
		if (line_error(line))
			continue ;
		if (check_unclosed_quotes(line))
			continue ;
		if (parser(&cmd_tab, line, &minidata) == -1)
			continue ;
		if (g_sigint_received == 130)
		{
			clean_minishell(NULL);
			continue ;
		}
		if (!ft_pre_exec(&cmd_tab, &minidata))
			ft_exec_input(&cmd_tab, &minidata);
		clean_minishell(NULL);
	}
	return (0);
}
