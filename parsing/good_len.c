/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:20:10 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/02 14:04:42 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	handle_redirects(char *str, int *i, int *len)
{
	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
	{
		if (*i > 0 && str[*i - 1] != ' ')
			(*len)++;
		(*len)++;
		if (str[*i + 1] == str[*i])
			(*i)++;
		if (str[*i + 1] != ' ')
			(*len)++;
	}
	return (*i);
}

static void	update_quotees(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		(*in_single_quote) = !(*in_single_quote);
	else if (c == '"' && !(*in_single_quote))
		(*in_double_quote) = !(*in_double_quote);
}

int	good_len(char *str)
{
	int	i;
	int	len;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	len = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i])
	{
		update_quotees(str[i], &in_single_quote, &in_double_quote);
		if (!in_single_quote && !in_double_quote)
			i = handle_redirects(str, &i, &len);
		len++;
		i++;
	}
	return (len);
}
