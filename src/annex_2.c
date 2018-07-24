/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igradea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:36:22 by igradea           #+#    #+#             */
/*   Updated: 2017/09/07 04:48:51 by iongradea        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem-in.h"

int   parse_st_end_room(t_data *data, char *str, t_flag *flag)
{
  ft_printf("parse_st_end_room - str : %s\n", str);
  if (IS_START_ROOM)
  {
    if (!(data->namestart = ft_strdup(str)))
      exit(0);
    ft_printf("namestart : %s\n", data->namestart);
    flag->st_parser = FALSE;
  }
  else if (IS_END_ROOM)
  {
    if (!(data->nameend = ft_strdup(str)))
      exit(0);
    ft_printf("nameend : %s\n", data->nameend);
    flag->end_parser = FALSE;
  }
  return (SUCCESS);
}

int  ft_set_flag(char *line, t_flag *flag)
{
  ft_printf("ft_set_flag - line : %s\n", line);
  if (IS_START_CMD)
    flag->st_parser = TRUE;
  else if (IS_END_CMD)
    flag->end_parser = TRUE;
  return (SUCCESS);
}
