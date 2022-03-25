/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:31:27 by sahafid           #+#    #+#             */
/*   Updated: 2022/03/16 14:31:28 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	error(void)
{
	write(1, "ERROR\n", 6);
	exit(0);
}

void	error_duplicate(char	**splited, int *array)
{
	free_parsing(splited);
	free(array);
	error();
}

void	checkvalid(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			i++;
			j++;
		}
		else if (isdigit(str[i]))
			i++;
		else if ((str[i] == '+' && isdigit(str[i - 1])) \
			|| (str[i] == '-' && isdigit(str[i - 1])))
			error();
		else if ((str[i] == '+' || str[i] == '-') && isdigit(str[i + 1]))
			i++;
		else
			error();
	}
	if (i == j)
		error();
}

void	checkduplicate(char	**splited, int i)
{
	int	*array;
	int	j;
	int	t;

	j = 0;
	array = NULL;
	array = (int *)malloc(sizeof(int) * i);
	i = 0;
	while (splited[i])
	{
		array[i] = ft_atoi(splited[i]);
		i++;
	}
	while (j < i)
	{
		t = 0;
		while (t < i)
		{
			if ((array[j] == array[t]) && t != j)
				error_duplicate(splited, array);
			t++;
		}
		j++;
	}
	free(array);
}

char	**parsings(char **argv, int *i)
{
	char	**splited;

	splited = NULL;
	splited = parsing_utils(splited, argv, *i);
	*i = 0;
	while (splited[*i])
		(*i)++;
	checkduplicate(splited, (*i));
	checkmaxint(splited, (*i));
	return (splited);
}
