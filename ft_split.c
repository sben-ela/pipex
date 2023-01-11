/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:32:50 by sben-ela          #+#    #+#             */
/*   Updated: 2022/12/07 21:17:18 by sben-ela         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_lenword(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_fullstr(char const *str, char c)
{
	char	*word;
	int		i;
	int		len;

	i = 0;
	len = ft_lenword(str, c);
	word = malloc(len + 1);
	if (!word)
		return (0);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_free(char **strs, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(strs[j]);
		j++;
	}
	free(strs);
}

static	char	**ft_second(char **strs, const char *str, int c)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
		{
			strs [i] = ft_fullstr(str, c);
			if (!strs [i])
			{
				ft_free(strs, i);
				return (0);
			}
			i++;
		}
		while (*str && *str != c)
			str++;
	}
	strs [i] = 0;
	return (strs);
}

char	**ft_split(char const *str, char c)
{
	char	**strs;
	int		count;
	int		i;

	count = 1;
	i = 0;
	if (!str)
		return (0);
	while (str [i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			count ++;
		while (str[i] && str[i] != c)
		i++;
	}
	strs = (char **)malloc(sizeof(char *) * count);
	if (!strs)
		return (0);
	strs = ft_second(strs, str, c);
	return (strs);
}
