/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/11 12:07:20 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

void	handle_if_last_is_pipe(t_cmd *cmd)
{
	char	*line_heredoc;
	char	**arr_of_tokens;

	while (is_pipe_type(cmd->last_token))
	{
		line_heredoc = readline("> ");
		arr_of_tokens = splitter(line_heredoc);
		free(line_heredoc);
		parser(cmd, arr_of_tokens);
	}
}

// echo "jojo" 'nene' > outfile.txt | < infile.txt echo "jojo" 'nene' aha "$USER" '$USER' $USER >> test.out
int	main (void)
{
	char		*line;
	char		*prompt;
	t_cmd		parsed_line;
	t_cmd_tab	cmd_tab;
	char		**arr_of_tokens;

	line = NULL;
	ft_init_cmd_struct(&parsed_line);
	ft_init_cmd_tab_struct(&cmd_tab);
	printf(BLUE);
	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (*line)
			add_history(line);
		check_exit(line);
		check_unclosed_quotes(line);
		arr_of_tokens = splitter(line);
		free(line);
		parser(&parsed_line, arr_of_tokens);
		handle_if_last_is_pipe(&parsed_line);
		// print_cmd(&parsed_line);
		make_cmd_tab(&cmd_tab, &parsed_line);
		ft_delete_cmd(&parsed_line);
		// print_cmd_tab(&cmd_tab);
		// print_cmd_tab(&cmd_tab);
		make_cmd_paths(&cmd_tab);
		make_execve_cmds(&cmd_tab);
		print_cmd_tab(&cmd_tab); // just to show cmd_tab
		ft_delete_cmds_in_cmd_tab(&cmd_tab);
	}
	return (0);
}
