/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/08 23:27:39 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

void	free_program(t_cmd *cmd, char *line, char *prompt)
{
	ft_delete_nodes(cmd);
	free(line);
	free(prompt);
	printf(RESET);
}

void	check_exit(t_cmd *cmd, char *line, char *prompt)
{
	if (ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
	{
		printf("exit\n");
		free_program(cmd, line, prompt);
		exit(0);
	}
}

void	handle_if_last_is_pipe(t_cmd *cmd)
{
	char	*line;

	while (is_pipe_type(cmd->last_token))
	{
		line = readline("> ");
		parser(cmd, line);
		free(line);
	}
}

void	check_unclosed_quotes(t_cmd *cmd, char *line, char *prompt)
{
	if (is_unclosed_quotes(line) == 1)
	{
		printf("Minishell cannot handle open quotes (\", \').\n");
		free_program(cmd, line, prompt);
		exit(0);
	}
}

void	make_cmd_tab(t_cmd_tab *cmd_tab, t_cmd *parsed_line)
{
	t_token	*token;
	t_token	*temp;

	token = parsed_line->first_token;
	ft_push_rotate_cmd(cmd_tab);
	while(token != NULL)
	{
		temp = token->next;
		if (is_pipe_type(token->prev))
			ft_push_rotate_cmd(cmd_tab);
		ft_move_token(cmd_tab->last_cmd, token);
		token = temp;
	}
	ft_init_cmd_struct(parsed_line);
}

// echo "jojo" 'nene' > outfile.txt | < infile.txt echo "jojo" 'nene' aha "$USER" '$USER' $USER >> test.out
int	main (void)
{
	char		*line;
	char		*prompt;
	t_cmd		parsed_line;
	t_cmd_tab	cmd_tab;
	t_cmd		*cmd;

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
		parser(&parsed_line, line);
		check_double_redirect(&parsed_line, line, prompt);
		handle_if_last_is_pipe(&parsed_line);
		print_cmd(&parsed_line); // just show table
		make_cmd_tab(&cmd_tab, &parsed_line);
		cmd = (&cmd_tab)->first_cmd;
		while(cmd != NULL)
		{
			print_cmd(cmd);
			cmd = cmd->next;
		}
		free_program(&parsed_line, line, prompt);
		ft_delete_cmds_in_cmd_tab(&cmd_tab);
	}
	return (0);
}
// int main() {
//     t_command_table cmd_table;
// 	char 	*prompt;
//     char	*input;

//     ft_init_cmd_struct(&cmd_table);
// 	prompt = "minishell> ";
//     while ((input = readline(prompt)) != NULL) {
// 		// Add non-empty lines to history - push the arrow up on you keyboard buddy
//         if (*input)
// 			add_history(input);

//         // Process the input
//         ft_printf("You entered: %s\n", input);
// 		// Test the command_table and push_rotate ops - every input will be in the table
// 		ft_push_rotate_token(&cmd_table, ft_strdup(input));
//         t_token  *node;
//         node = cmd_table.first_token;
//         while (node != NULL)
//         {
//             ft_printf("Content of cmd_table: %s\n", node->text);
//             node = node->next;
//         }
//         free(input);
//     }
// 	ft_delete_nodes(&cmd_table);
//     return 0;
// }
