/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/09 21:24:21 by mbartos          ###   ########.fr       */
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
	if (ft_strncmp(line, "exit", 5) == 0)
	{
		printf("exit\n");
		free_program(cmd, line, prompt);
		exit(0);
	}
}

void	free_array(char **arr_of_str)
{
	int	index;

	index = 0;
	while (arr_of_str[index] != NULL)
	{
		free(arr_of_str[index]);
		index++;
	}
	free(arr_of_str);
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

void	expand_cmd_path(t_token *ptr_token)
{
	char	*path;
	char	*temp_path;
	char	**arr_of_paths;
	int		i;

	temp_path = getenv("PATH");
	arr_of_paths = ft_split(temp_path, ':');
	i = 0;
	while (arr_of_paths[i] != NULL)
	{
		temp_path = ft_strjoin(arr_of_paths[i], "/");
		path = ft_strjoin(temp_path, ptr_token->text);
		free(temp_path);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		i++;
	}
	if (arr_of_paths[i] == NULL)
		ptr_token->type = CMD_ERR;
	else
	{
		free(ptr_token->text);
		ptr_token->text = path;
	}
	free_array(arr_of_paths);
}

void	make_cmd_paths(t_cmd_tab *cmd_tab)
{
	t_cmd	*ptr_cmd;
	t_token	*ptr_token;

	ptr_cmd = cmd_tab->first_cmd;
	while (ptr_cmd != NULL)
	{
		ptr_token = ptr_cmd->first_token;
		while(ptr_token != NULL)
		{
			if (ptr_token->type == CMD)
			{
				expand_cmd_path(ptr_token);
			}
			ptr_token = ptr_token->next;
		}
		ptr_cmd = ptr_cmd->next;
	}
}

int		count_cmd_length(t_cmd *cmd)
{
	t_token	*ptr_token;
	int		length;

	ptr_token = cmd->first_token;
	length = 0;
	while(ptr_token != NULL)
	{
		if (ptr_token->type == CMD || ptr_token->type == ARG)
			length++;
		else if (ptr_token->type == CMD_ERR)
			return (-1);
		ptr_token = ptr_token->next;
	}
	return (length);
}

void	make_execve_array(t_cmd *cmd)
{
	t_token	*ptr_token;
	char	**arr_of_cmds;
	int		length;
	int		index;

	length = count_cmd_length(cmd);
	if (length == -1)
	{
		cmd->execve_cmd = NULL;
		return ;
	}
	arr_of_cmds = (char **) malloc(sizeof(char *) * (length + 1));
	ptr_token = cmd->first_token;
	index = 0;
	while(index < length)
	{
		if (ptr_token->type == CMD || ptr_token->type == ARG)
			arr_of_cmds[index++] = ptr_token->text;
		ptr_token = ptr_token->next;
	}
	arr_of_cmds[index] = NULL;
	cmd->execve_cmd = arr_of_cmds;
}

void	make_execve_cmds(t_cmd_tab *cmd_tab)
{
	t_cmd	*ptr_cmd;

	ptr_cmd = cmd_tab->first_cmd;
	while (ptr_cmd != NULL)
	{
		make_execve_array(ptr_cmd);
		ptr_cmd = ptr_cmd->next;
	}
}

// echo "jojo" 'nene' > outfile.txt | < infile.txt echo "jojo" 'nene' aha "$USER" '$USER' $USER >> test.out
int	main (void)
{
	char		*line;
	char		*prompt;
	t_cmd		parsed_line;
	t_cmd_tab	cmd_tab;

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
		check_redirection_errors(&parsed_line, line, prompt);
		handle_if_last_is_pipe(&parsed_line);
		// print_cmd(&parsed_line); // just show table
		make_cmd_tab(&cmd_tab, &parsed_line);
		// print_cmd_tab(&cmd_tab);
		expand_heredocs(&cmd_tab);
		// print_cmd_tab(&cmd_tab);
		make_cmd_paths(&cmd_tab);
		make_execve_cmds(&cmd_tab);
		print_cmd_tab(&cmd_tab);
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
