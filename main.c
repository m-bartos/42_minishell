/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/18 11:14:07 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

int	is_empty_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else
			break ;
	}
	if (line[i] == '\0')
	{
		free(line);
		return (1);
	}
	else
		return (0);
	
}

// valgrind -s --leak-check=full --show-reachable=yes --error-limit=no --suppressions=minishell.supp --trace-children=yes --track-fds=yes ./minishell
// echo "jojo" 'nene' > outfile.txt | < infile.txt echo "jojo" 'nene' aha "$USER" '$USER' $USER >> test.out
int	main (void)
{
	char		*line;
	char		*prompt;
	t_cmd		parsed_line;
	t_cmd_tab	cmd_tab;

	line = NULL;
	ft_init_cmd_struct(&parsed_line);
	ft_init_cmd_tab(&cmd_tab);
	printf(BLUE);
	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (is_empty_line(line))
			continue ;
		check_exit(line);
		if (*line)
			add_history(line);
		check_unclosed_quotes(line);
		parser(&cmd_tab, &parsed_line, line);
		print_cmd_tab(&cmd_tab); // just to show cmd_tab
		unlink_heredoc_files(&cmd_tab);
		ft_delete_cmds_in_cmd_tab(&cmd_tab);
	}
	return (0);
}
