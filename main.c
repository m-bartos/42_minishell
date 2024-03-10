/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/10 10:49:03 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

void	handle_if_last_is_pipe(t_cmd *cmd, char *prompt)
{
	char	*line_heredoc;
	char	**arr_of_tokens;

	while (is_pipe_type(cmd->last_token))
	{
		line_heredoc = readline("> ");
		arr_of_tokens = splitter(line_heredoc);
		free(line_heredoc);
		parser(cmd, arr_of_tokens, prompt);
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
	while (1)
	{
		printf(BLUE);
		prompt = get_prompt();
		line = readline(prompt);
		if (*line)
			add_history(line);
		check_exit(&parsed_line, line, prompt);
		check_unclosed_quotes(&parsed_line, line, prompt);
		arr_of_tokens = splitter(line);
		free(line);
		parser(&parsed_line, arr_of_tokens, prompt);
		handle_if_last_is_pipe(&parsed_line, prompt);
		// print_cmd(&parsed_line); // just show table
		make_cmd_tab(&cmd_tab, &parsed_line);
		// print_cmd_tab(&cmd_tab);
		// print_cmd_tab(&cmd_tab);
		make_cmd_paths(&cmd_tab);
		make_execve_cmds(&cmd_tab);
		print_cmd_tab(&cmd_tab);
		free_program(&parsed_line, prompt);
		ft_delete_cmds_in_cmd_tab(&cmd_tab);
	}
	return (0);
}
