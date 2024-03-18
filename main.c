/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/18 18:14:58 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

// valgrind -s --leak-check=full --show-reachable=yes --error-limit=no --suppressions=minishell.supp --trace-children=yes --track-fds=yes ./minishell
// echo "jojo" 'nene' > outfile.txt | < infile.txt echo "jojo" 'nene' aha "$USER" '$USER' $USER >> test.out
int	main (void)
{
	char		*prompt;
	char		*line;
	t_cmd_tab	cmd_tab;
	//t_mini_data	minidata;

	line = NULL;
	ft_init_cmd_tab(&cmd_tab);
	// ft_init_mini_data(&minidata, envp);
	printf(BLUE);
	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		// if(signal(SIGINT, ft_ctrl_c_sig) == SIG_ERR)
		// {
			// free(line);
			// continue ;
		// }
		if (is_empty_line(line))
			continue ;
		check_exit(line);
		if (*line)
			add_history(line);
		check_unclosed_quotes(line);
		parser(&cmd_tab, line);
		// ft_exec_input(&cmd_tab, &minidata);
		print_cmd_tab(&cmd_tab); // just to show cmd_tab
		unlink_heredoc_files(&cmd_tab);
		ft_delete_cmds_in_cmd_tab(&cmd_tab);
	}
	return (0);
}
