/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/06 15:27:05 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	free_program(t_cmd_tab *cmd_tab, char *line, char *prompt)
{
	ft_delete_nodes(cmd_tab);
	free(line);
	free(prompt);
}

void	check_exit(t_cmd_tab *cmd_tab, char *line, char *prompt)
{
	if (ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
	{
		free_program(cmd_tab, line, prompt);
		printf("exit\n");
		exit(0);
	}
}

// echo "jojo" 'nene' > outfile.txt | < infile.txt echo "jojo" 'nene' aha "$USER" '$USER' $USER >> test.out
int	main (void)
{
	char		*line;
	char		*prompt;
	t_cmd_tab	cmd_tab;

	line = NULL;
	while (1)
	{
		prompt = get_prompt();
		printf(BLUE);
		line = readline(prompt);
		printf(RESET);
		if (*line)
			add_history(line);
		check_exit(&cmd_tab, line, prompt);
		parser(&cmd_tab, line);
		print_cmd_tab(&cmd_tab); // just show table
		free_program(&cmd_tab, line, prompt);
	}
	return (0); 
}
