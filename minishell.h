/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:24:52 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/02 13:18:05 by mbartos          ###   ########.fr       */
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

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define FALSE 0
# define TRUE 1

typedef enum s_type
{
	COMMAND,
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
COMMAND	/	ARG		/	ARG		/	PIPE	/	R_IN	/	ARG			/	COMMAND		/
*/
typedef struct s_command_table
{
	t_node	*first_node;
	t_node	*last_node;
	int		size;
}		t_command_table;

// command_table functions
void	ft_init_command_table(t_command_table *cmd_table);
void	ft_rotate_token(t_command_table *cmd_table);
void	ft_push_token(t_command_table *cmd_table, char *token);
void	ft_push_rotate_token(t_command_table *cmd_table, char *token);
void	ft_delete_nodes(t_command_table *cmd_table);

// expander_var.c
char	*end_of_var(char *str);
char	*get_variable_name(char	*str);
char	*get_expanded_var(char *str);

// expander.c
char	*expand_all_vars_in_str(char *str);

// splitter.c
void	splitter(char *line);

// splitter_utils.c
int		is_whitespace(char c);
int		is_quote(char c);
int		is_token(char c);
int		is_end_of_word(char c);
size_t	word_length(char *str);


#endif
