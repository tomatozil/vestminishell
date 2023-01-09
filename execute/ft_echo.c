#include "../minishell.h"

int	check_n(char *content)
{
	long i;

	i = 0;
	while (content[0] == '-' && content[++i] == 'n')
		;
	if (content[i] == 0)
		return (1);
	return (0);
}

void	ft_echo(t_cmd	*cmd)
{
	long	n;
	long	i;
	long	j;
	
	j = -1;
	i = 0;
	n = check_n(cmd->content[0]);
	while (cmd->content[++j])
	{
		if (j == 0 && n)
			j = 1;
		else
			i = 0;
		while (cmd->content[j][i])
		{
			write(1, &cmd->content[j][i], 1);
			i++;
		}
		write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
	return ;
}