#include "minishell.h"

void ft_env(t_cmd *cmd)
{
	t_env *env;

	if (cmd->content)
		return ;
	env = g_info.env_lst;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}