/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:24:52 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/13 11:37:50 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "./libft/libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define FALSE 0
# define TRUE 1

# define CMD_NOT_FOUND 127

// new types to categorize tokens
typedef enum s_type
{
	CMD,
	CMD_ERR,
	CMD_BUILT,
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
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_command
{
	char				**execve_cmd;
	struct s_command	*next_cmd;
	struct s_command	*prev_cmd;
	t_token				*first_token;
	t_token				*last_token;
	int					size;
}		t_command;

typedef struct s_cmd_tab
{
	t_command	*first_cmd;
	t_command	*last_cmd;
	int			size;
}		t_cmd_tab;

typedef struct s_exec_data
{
	int	exit_status;
	int	fd_in;
	int	fd_out;
	int	pipe_fd[2];
}		t_exec_data;

// exec functions
void	ft_exec_input(t_cmd_tab *tab);

// I/O functions
int		ft_input_file(char *file_name);
int		ft_output_file(char *file_name);
int		ft_append_file(char *file_name);

// Redirection functions
void	ft_input_redirection(char *file_name, int *fd_in);
void	ft_output_redirection(char *file_name, int *fd_out);
void	ft_append_redirection(char *file_name, int *fd_out);

// Redirection utils
int	ft_has_out_redir(t_command *cmd);

// NEW command table ops
void	ft_init_token(t_token *token);
void	ft_init_cmd(t_command *cmd);
void	ft_init_cmd_table(t_cmd_tab *cmd_tab);
void	ft_push_cmd_to_tab(t_cmd_tab *cmd_table, t_command *cmd);
void	ft_append_cmd_to_tab(t_cmd_tab *cmd_table, t_command *cmd);
void	ft_append_token_to_cmd(t_command *cmd, t_token *token);
void	ft_append_token_to_cmd_v2(t_command *cmd, char *text, t_type type);
t_token	*ft_create_token(char *text, t_type type);

// Signal
void	ft_ctrl_c_sig(int signal);
void	ft_ctrl_slash_sig (int signal);
#endif
