/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:24:52 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/01 19:13:44 by mbartos          ###   ########.fr       */
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

typedef struct s_node
{
	char		*text;
	t_type		type;
	t_node		*next;
}		t_node;

/* --- LINKED LIST EXAMPLE (non-sense command) ---
echo	/	aaa 	/	bbb		/	|		/	<		/	file.txt	/	cat			/
COMMAND	/	ARG		/	ARG		/	PIPE	/	R_IN	/	ARG			/	COMMAND		/
*/
typedef struct s_command_table
{
	t_node	*first_node;
}		t_command_table;

#endif