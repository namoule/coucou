/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:20:10 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/04 12:45:07 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_quotes_s(char c, t_quote_context *ctx)
{
	if (c == '\'' && !(ctx->in_double_quote))
		ctx->in_single_quote = !(ctx->in_single_quote);
	else if (c == '\"' && !(ctx->in_single_quote))
		ctx->in_double_quote = !(ctx->in_double_quote);
}

void	process_special_char(char *str, char *res, t_quote_context *ctx)
{
	if (ctx->i > 0 && str[ctx->i - 1] != ' ')
		res[ctx->j++] = ' ';
	res[ctx->j++] = str[ctx->i];
	if (str[ctx->i + 1] == str[ctx->i])
		res[ctx->j++] = str[ctx->i++];
	if (str[ctx->i + 1] != ' ')
		res[ctx->j++] = ' ';
}

void	process_char(char *str, char *res, t_quote_context *ctx)
{
	handle_quotes_s(str[ctx->i], ctx);
	if (!(ctx->in_single_quote || ctx->in_double_quote))
	{
		if (str[ctx->i] == '<' || str[ctx->i] == '>' || str[ctx->i] == '|')
			process_special_char(str, res, ctx);
		else
			res[ctx->j++] = str[ctx->i];
	}
	else
		res[ctx->j++] = str[ctx->i];
}

int	check_invalid_quotes(char *str, char *res)
{
	if (check_pair_quotes(str))
	{
		free(res);
		return (1);
	}
	return (0);
}

char	*good_char(char *str)
{
	char			*res;
	t_quote_context	ctx;

	res = malloc(sizeof(char) * (good_len(str) + 1));
	if (!res)
		return (NULL);
	ctx.i = 0;
	ctx.j = 0;
	ctx.in_single_quote = 0;
	ctx.in_double_quote = 0;
	while (str[ctx.i])
	{
		process_char(str, res, &ctx);
		ctx.i++;
	}
	if (check_invalid_quotes(str, res))
		return (NULL);
	res[ctx.j] = '\0';
	return (res);
}