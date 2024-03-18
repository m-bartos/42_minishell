
#include "../minishell.h"
#include <errno.h>

char	*ft_strjoin_e(const char *s1, const char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	if(new_str == NULL)
	{
		perror("Minishell: ");
		exit(EXIT_FAILURE);
	}
	return (new_str);
}

char	*ft_strdup_e(const char *s1)
{
	char	*new_str;

	new_str = ft_strdup(s1);
	if(new_str == NULL)
	{
		perror("Minishell: ");
		exit(EXIT_FAILURE);
	}
	return (new_str);
}

char	*ft_substr_e(const char *s1, unsigned int start, size_t len)
{
	char	*new_str;

	new_str = ft_substr(s1, start, len);
	if(new_str == NULL)
	{
		perror("Minishell: ");
		exit(EXIT_FAILURE);
	}
	return (new_str);
}