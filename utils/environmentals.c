/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmentals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:42:36 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/16 17:15:50 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// init

// add

// remove

// read all

// convert list to array of str

// convert array to list


void	ft_init_env_list(t_env_list *env_list)
{
	env_list->top = NULL;
	env_list->size = 0;
}

void	ft_init_env(t_env *env)
{
	env->next = NULL;
	env->value = NULL;
}

void	ft_add_env(t_env_list *env_list, char *env)
{
	t_env	*node;

	ft_remove_env(env_list, env);
	node = malloc(sizeof(t_env));
	if (!node)
	{
		perror("Add env:");
		exit(1);
	}
	ft_init_env(node);
	node->value = ft_strdup(env);
	node->next = env_list->top;
	env_list->top = node;
	env_list->size++;
}

// Remove only value from node and set the val to NULL
int	ft_remove_env(t_env_list *env_list, char *var_name)
{
	t_env	*node;

	node = env_list->top;
	while (node)
	{
		if (node->value != NULL)
		{
			if (ft_strncmp(node->value, var_name, ft_strlen(var_name)) == 0 && *(node->value + (ft_strlen(var_name))) == '=')
			{
				free(node->value);
				node->value = NULL;
				env_list->size--;
				return (0);
			}
		}
		node = node->next;
	}
	return (1);
}

// Mimics getenv() to get a value represented by var name
// Malloc = free the returned pointer!
char	*ft_get_env(t_env_list *env_list, char *var_name)
{
	t_env	*env;
	char	*env_value;

	env = env_list->top;
	while (env)
	{
		if (env->value != NULL)
		{
			if (ft_strncmp(env->value, var_name, ft_strlen(var_name)) == 0 && *(env->value + (ft_strlen(var_name))) == '=')
			{
				env_value = env->value;
				while(*env_value != '=')
					env_value++;
				env_value++;
				env_value = ft_strdup(env_value);
				return (env_value);
			}
		}
		env = env->next;
	}
	return (NULL);
}

// mimics the env command without option or arguments
void	ft_list_env(t_env_list *env_list)
{
	t_env	*env;
	env = env_list->top;
	while (env)
	{
		if (env->value != NULL)
		{
			ft_putstr_fd(env->value, STDOUT);
			ft_putstr_fd("\n", STDOUT);
		}
		env = env->next;
	}
}

// Adds strings from envp array passed by main function
void	ft_convert_arr_to_list(t_env_list *env_list, char **envp)
{
	while (*envp)
		ft_add_env(env_list, *envp++);
		envp++;
}

char **ft_convert_list_to_arr(t_env_list *tab)
{
	int		i;
	char	**envp;
	t_env	*env;

	i = 0;
	envp = malloc(sizeof(char *)* (tab->size + 1));
	if (!envp)
	{
		perror("Convert list to arr: ");
		exit(1);
	}
	env = tab->top;
	while (env)
	{
		if (env->value != NULL)
			envp[i] = env->value;
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
