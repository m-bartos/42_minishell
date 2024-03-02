/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:24:52 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/02 22:26:47 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "unistd.h"
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

// helper functions
void	ft_print_cmd(t_command_table *cmd_table);


// exec functions
void	ft_exec_commands(char ***cmds);
#endif
