/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:43:28 by fmaurer           #+#    #+#             */
/*   Updated: 2024/08/05 20:46:22 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* FT_PRINTF! Supports "diucspxXX" with "0# .-+" & prec & width. */
int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		chars_printed;

	if (!fmt || !ftpr_check_fmt(fmt))
		return (-1);
	if (!*fmt)
		return (0);
	va_start(args, fmt);
	chars_printed = ftpr_parse_args(args, fmt);
	va_end(args);
	return (chars_printed);
}

/*
 * Checks for INVALID conversions.
 *
 * Cases for this: Conversion running off the strings end. To >INT_MAX prec or
 * width numbers.
 * 
 */
int	ftpr_check_fmt(const char *fmt)
{
	while (*fmt)
	{
		if (*fmt == '%')
		{
			if (ftpr_compl_isconv(fmt) == -1)
				return (0);
			while (ftpr_isflagconv(*(++fmt)) != 1)
				;
		}
		fmt++;
	}
	return (1);
}

/* Parse args while scanning fmtstring. Returns number of printed chars. */
int	ftpr_parse_args(va_list args, const char *fmt)
{
	int	c;
	int	output;

	output = 0;
	while (*fmt)
	{
		c = ftpr_is_conversion(fmt);
		if (c == 1)
			fmt += ftpr_smpl_convert(args, fmt, &output);
		else if (c == -1)
		{
			c = ftpr_gather_flags_and_conv(args, fmt, &output);
			if (c < 0)
				return (-1);
			fmt += c;
		}
		else
		{
			ft_putchar(*fmt);
			output++;
			fmt++;
		}
	}
	return (output);
}
