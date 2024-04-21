/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/21 20:31:36 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_line(t_minidata *minidata)
{
	char	*prompt;
	char	*line;

	prompt = get_prompt(minidata);
	line = readline(prompt);
	free(prompt);
	return (line);
}

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
		char **envp)
{
	char		*line;
	t_cmd_tab	cmd_tab;
	t_minidata	minidata;

	init_minishell(&minidata, &cmd_tab, envp);
	disable_ctrl_c_output();
	setup_signal_handling();
	line = NULL;
	while (1)
	{
		if (g_sigint_received)
			g_sigint_received = 0;
		line = ft_read_line(&minidata);
		if (line_error(line))
			continue ;
		if (check_unclosed_quotes(line))
			continue ;
		if (parser(&cmd_tab, line, &minidata) == -1)
			continue ;
		if (!ft_pre_exec(&cmd_tab, &minidata))
			ft_exec_input(&cmd_tab, &minidata);
		clean_minishell(NULL);
	}
	return (0);
}
