#include "minishell.h"

void ft_unset(t_cmd *cmd)
{
	t_env	*env_temp;
	t_env	*del_temp;
	char 	**str;

	str = cmd->content;
	while (*str)
	{
		env_temp = g_info.env_lst;
		if (env_temp && ft_strcmp(env_temp->key, *cmd->content) == 0)
		{
			g_info.env_lst = env_temp->next;
			free(env_temp->key);
			free(env_temp->value);
			free(env_temp);
		}
		else
		{
		while (env_temp->next && ft_strcmp(env_temp->next->key, *str))
			env_temp = env_temp->next;
		}
		if (!env_temp->next)
			return ; // not a valid identifier
		if (env_temp->next->next == 0)
		{
			del_temp = env_temp->next;
			env_temp->next = 0;
			free(del_temp->key);
			free(del_temp->value);
			free(del_temp);
			return ;
		}
		del_temp = env_temp->next;
		env_temp->next = del_temp->next;
		free(del_temp->key);
		free(del_temp->value);
		free(del_temp);
		str++;
	}
}