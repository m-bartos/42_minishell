/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:24:52 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/08 13:18:37 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
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

typedef enum s_type
{
	CMD,
	CMD_ERR,
	ARG,
	PIPE,
	R_IN,
	R_OUT,
	R_OUT_APPND,
	HERE_DOC
}		t_type;

// chaning declaration of *next from t_node to struct s_node due to compilation error on Mac
typedef struct s_node
{
	char			*token;
	t_type			type;
	struct s_node	*next;
	struct s_node	*prev;
}		t_node;

/* --- LINKED LIST EXAMPLE (non-sense command) ---
echo	/	aaa 	/	bbb		/	|		/	<		/	file.txt	/	cat			/
CMD	/	ARG		/	ARG		/	PIPE	/	R_IN	/	ARG			/	CMD		/
*/
typedef struct s_command_table
{
	t_node	*first_node;
	t_node	*last_node;
	int		size;
}		t_cmd_tab;

// new types to categorize tokens
typedef enum s_type
{
	CMD,
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

// new struct to hold parsed token and commands
typedef struct s_token
{
	char			*text;
	t_type			type;
	t_token			*next;
	t_token			*prev;
}		t_token;

typedef struct s_command
{
	char		**execve_cmd;
	t_command	*next_cmd;
	t_command	*prev_cmd;
	t_token		*first_token;
	t_token		*last_token;
	int			size;
}		t_command;

typedef struct s_cmd_tab
{
	t_command	*first_command;
	t_command	*last_command;
	int			size;
}		t_cmd_tab;



// command_table functions
void	ft_init_command_table(t_cmd_tab *cmd_table);
void	ft_rotate_token(t_cmd_tab *cmd_table);
void	ft_push_token(t_cmd_tab *cmd_table, char *token);
void	ft_push_rotate_token(t_cmd_tab *cmd_table, char *token);
void	ft_delete_nodes(t_cmd_tab *cmd_table);

// expander_var.c
char	*end_of_var(char *str);
char	*get_variable_name(char	*str);
char	*get_expanded_var(char *str);

// expander.c
// char	*expand_all_vars_in_str(char *str);
void	expand_cmd_tab(t_cmd_tab *ptr_cmd_tab);

// get_prompt.c
char	*get_prompt(void);

// parser.c
void	parser(t_cmd_tab *ptr_cmd_tab, char *line);

// splitter.c
char	**splitter(char *line);

// splitter_handlers.c
char	*handle_redirections(char *str, size_t *index, char redir_type);
char	*handle_pipe(char *str, size_t *index);
char	*handle_quotes(char *str, size_t *index, char quotes_type);
char	*handle_word(char *str, size_t *index);

// splitter_utils.c
int		is_whitespace(char c);
int		is_quote(char c);
int		is_operator(char c);
int		is_end_of_word(char c);
size_t	word_length(char *str);

// cmd_tab_assign_types.c
void	assign_types_to_tokens(t_cmd_tab *ptr_cmd_tab);


// cmd_tab_filler.c
void	init_and_fill_cmd_tab(t_cmd_tab *ptr_cmd_tab, char **arr_of_tokens);
void	print_cmd_tab(t_cmd_tab *ptr_cmd_tab);

// cmd_tab_filler_utils.c
int		is_pipe_type(t_node *ptr_node);
int		is_redirection_type(t_node *ptr_node);
int		is_operator_type(t_node *ptr_node);
int		is_in_single_quotes(t_node *ptr_node);
int		is_in_double_quotes(t_node *ptr_node);

// cmd_tab_remove_quotes.c
void	remove_quotes_from_cmd_tab(t_cmd_tab *ptr_cmd_tab);

void	ft_init_command_table(t_cmd_tab *cmd_table);
void	ft_rotate_token(t_cmd_tab *cmd_table);
void	ft_push_token(t_cmd_tab *cmd_table, char *token);
void	ft_push_rotate_token(t_cmd_tab *cmd_table, char *token);
void	ft_delete_nodes(t_cmd_tab *cmd_table);

// helper functions
void	ft_print_cmd(t_cmd_tab *cmd_table);

// exec functions
void	ft_exec_commands(char ***cmds);

// input output
int		ft_input_file(char *file_name);
#endif
