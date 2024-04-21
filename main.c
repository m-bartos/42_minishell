/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/21 13:10:53 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"


// valgrind -s --leak-check=full --show-reachable=yes --error-limit=no --suppressions=minishell.supp --trace-children=yes --track-fds=yes ./minishell
// echo "jojo" 'nene' > outfile.txt | < infile.txt echo "jojo" 'nene' aha "$USER" '$USER' $USER >> test.out


int	main (int argc, char *argv[], char *envp[])
{
	char		*prompt;
	char		*line;
	t_cmd_tab	cmd_tab;
	t_minidata	minidata;

	disable_ctrl_c_output();
	setup_signal_handling();
	line = NULL;
	ft_init_cmd_tab(&cmd_tab);
	ft_init_minidata(&minidata, &cmd_tab, envp);
	exit_minishell(&minidata, 0);
	clean_minishell(&minidata);
	// Get PID to see process information
	// ft_printf("%d\n", getpid());
	while (1)
	{
		// ft_putstr_fd(BLUE, 1);
		// ft_putstr_fd(BLUE, 2);
		if (g_sigint_received)
			g_sigint_received = 0;
		prompt = get_prompt(&minidata);
		line = readline(prompt);
		free(prompt);
		if (line == NULL)
			ft_exit_minishell(NULL, NULL, NULL);
		if (is_empty_line(line))
			continue ;
		// check_exit(line);
		if (*line)
			add_history(line);
		if (check_unclosed_quotes(line))
			continue ;
		if (parser(&cmd_tab, line, &minidata) == -1)
			continue ;
		// print_cmd_tab(&cmd_tab); // just to show cmd_tab
		if (ft_pre_exec(&cmd_tab, &minidata))
		{
			clean_minishell(NULL);
			continue ;
		}
		ft_exec_input(&cmd_tab, &minidata);
		clean_minishell(NULL);
	}
	return (0);
}
