/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsar <nsar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:06 by mnikolov          #+#    #+#             */
/*   Updated: 2022/10/20 16:09:32 by nsar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_export(char **export)
{
	int		i;
	int		j;
	char	life;

	i = 0;
	while (export[i])
	{
		life = 1;
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (export[i][j])
		{
			ft_putchar_fd(export[i][j], 1);
			if (export[i][j] == '=' && life)
			{
				ft_putchar_fd('"', 1);
				life--;
			}
			j++;
		}
		if (!life)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	sort_export(t_lst *ms)
{
	char	**export;
	char	*tmp;
	int		i;
	int		j;

	export = env_2_str(ms);
	i = -1;
	while (export[++i])
	{
		j = i;
		while (export[++j])
		{
			if (ft_strcmp(export[i], export[j]) > 0)
			{
				tmp = export[i];
				export[i] = export[j];
				export[j] = tmp;
			}
		}
	}
	print_export(export);
	free_2ptr(export);
}

static void	sort_env(char *str, t_env **env)
{
	t_env	*cur;
	t_env	*aft;
	t_env	*tmp;

	tmp = *env;
	while (tmp->next)
	{
		aft = tmp;
		tmp = tmp->next;
	}
	aft->next = NULL;
	cur = *env;
	while (cur->next)
	{
		aft = cur->next;
		if (!ft_strncmp(aft->value, "OLDPWD=", 7))
		{
			tmp->next = aft;
			cur->next = tmp;
			return ;
		}
		cur = cur->next;
	}
}

static int	check_export(char *str, t_lst *ms)
{
	t_env	*temp;
	char	**id;
	int		i;

	temp = ms->env;
	i = -1;
	while (str[++i] && str[i] != '=')
		;
	i++;
	while (temp)
	{
		if (!ft_strncmp(temp->value, str, i))
		{
			free(temp->value);
			temp->value = ft_strdup(str);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	ft_export(char *str, t_lst *ms)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '*' || ft_isdigit(str[i]))
		{
			ft_error("export", str);
			return (1);
		}
	i++;
	}
	if (!check_export(str, ms))
	{
		new_env(str, ms);
		sort_env(str, &ms->env);
	}
	return (0);
}
