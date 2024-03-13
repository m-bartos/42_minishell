/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:24:52 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/13 12:00:44 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include "./libft/libft.h"
// rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,
# include <readline/readline.h>
// adds rl_clear_history()
# include <readline/history.h>

# define RESET   "\x1B[0m"
# define BLUE    "\x1B[34m"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define FALSE 0
# define TRUE 1

typedef enum s_in_quotes
{
	STR_ERR,
	OUT_OF_QUOTES,
	IN_DOUBLE_QUOTES,
	IN_SINGLE_QUOTES
}		t_in_quotes;

typedef enum s_type
{
	CMD,
	CMD_BUILT,
	CMD_ERR,
	ARG,
	PIPE,
	R_IN,
	R_INFILE,
	R_OUT,
	R_OUTFILE,
	R_OUT_APP,
	R_OUTFILE_APP,
	HERE_DOC,
	HERE_DOC_EOF
}		t_type;

// chaning declaration of *next from t_token to struct s_token due to compilation error on Mac
typedef struct s_token
{
	char			*text;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

/* --- LINKED LIST EXAMPLE (non-sense command) ---
echo	/	aaa 	/	bbb		/	|		/	<		/	file.txt	/	cat			/
CMD	/	ARG		/	ARG		/	PIPE	/	R_IN	/	ARG			/	CMD		/
*/

typedef struct s_cmd
{
	char			**execve_cmd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	t_token			*first_token;
	t_token			*last_token;
	int		size;
}		t_cmd;

typedef struct s_cmd_tab
{
	t_cmd	*first_cmd;
	t_cmd	*last_cmd;
	int		size;
}	t_cmd_tab;

// cmd_path_and_execve_cmd.c
void	expand_token_cmd_path(t_token *ptr_token);
void	make_cmd_paths(t_cmd_tab *cmd_tab);
int		count_cmd_length(t_cmd *cmd);
void	make_one_execve_cmd(t_cmd *cmd);
void	make_execve_cmds(t_cmd_tab *cmd_tab);

// cmd_struct_assign_types.c
void	assign_operator_types(t_cmd *ptr_cmd_tab);
void	assign_cmds_and_args(t_cmd *ptr_cmd_tab);
void	assign_types_to_tokens(t_cmd *ptr_cmd_tab);

// cmd_struct_errors.c
void	check_redirection_errors(t_cmd *ptr_cmd);

// cmd_struct_filler_utils.c
int		is_pipe_type(t_token *ptr_node);
int		is_redirection_type(t_token *ptr_node);
int		is_operator_type(t_token *ptr_node);
int		is_in_single_quotes(t_token *ptr_node);
int		is_in_double_quotes(t_token *ptr_node);

// cmd_struct_filler.c
void	fill_cmd_tab(t_cmd *ptr_cmd_tab, char **arr_of_tokens);

// cmd_struct_ops
void	ft_init_cmd_struct(t_cmd *cmd_table);
void	ft_rotate_token(t_cmd *cmd_table);
void	ft_push_token(t_cmd *cmd, char *token_text, t_type token_type);
void	ft_push_rotate_token(t_cmd *cmd, char *token_text, t_type token_type);
void	ft_delete_cmd(t_cmd *cmd_table);
void	ft_move_token(t_cmd *cmd, t_token *ptr_token);

// cmd_struct_remove_quotes.c
void	remove_quotes(t_token *ptr_node);
void	remove_quotes_from_cmd_tab(t_cmd *ptr_cmd_tab);

// cmd_tab_struct_ops.c
void	ft_init_cmd_tab(t_cmd_tab *cmd_tab);
void	ft_rotate_cmd(t_cmd_tab *cmd_tab);
void	ft_push_cmd(t_cmd_tab *cmd_tab);
void	ft_push_rotate_cmd(t_cmd_tab *cmd_tab);
void	ft_delete_cmds_in_cmd_tab(t_cmd_tab *cmd_tab);

// cmd_tab_make.c
void	make_cmd_tab(t_cmd_tab *cmd_tab, t_cmd *parsed_line);

// error_check.c
int		is_unclosed_quotes (char *str);
void	check_unclosed_quotes(char *line);

// exececution.c
void	ft_exec_commands(char ***cmds);

// exit_free.c
void	check_exit(char *line);
void	free_array(char **arr_of_str);

// expander_var.c
char	*end_of_var(char *str);
char	*get_variable_name(char	*str, size_t i);
char	*get_expanded_var(char *str, size_t i);

// expander.c
t_in_quotes	in_which_quotes(char *str, size_t i);
char		*malloc_new_expanded_str(char *str, size_t i, char *str_expanded_variable);
char		*get_str_with_one_expanded_var(char *str, size_t i, char *expanded_var);
char		*expand_all_vars_in_str(char *str);
void		expand_cmd_tab(t_cmd *ptr_cmd_tab);

// get_prompt.c
char	*get_prompt(void);

// helpers.c
void	print_cmd(t_cmd *ptr_cmd_tab);
void	ft_print_cmd(t_cmd *cmd_table);
void	print_cmd_tab(t_cmd_tab *cmd_tab);

// here_doc.c
char	*get_heredoc_file(char *eof, int index);
void	expand_heredocs(t_cmd *cmd);

// input_output.c
int		ft_input_file(char *file_name);

// parser.c
void	handle_if_last_token_is_pipe(t_cmd *cmd);
void	parse_from_arr_of_tokens_to_one_cmd(t_cmd *cmd, char **arr_of_tokens);
void	parser(t_cmd_tab *cmd_tab, t_cmd *cmd, char **arr_of_tokens);

// splitter_handlers.c
char	*handle_redirections(char *str, size_t *index, char redir_type);
char	*handle_pipe(char *str, size_t *index);
size_t	count_word_length(char *str);
char	*handle_word(char *str, size_t *index);

// splitter_utils.c
int		is_whitespace(char c);
int		is_quote(char c);
int		is_operator(char c);
int		is_end_of_word(char c);
size_t	word_length(char *str);

// splitter.c
int		count_tokens(char *line);
char	**init_arr_of_tokens(char *line);
char	**splitter(char *line);

// main.c


#endif
