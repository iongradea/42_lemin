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

/*
check ants : not a digit
*/
static int		ch_nb_ants(char *line, int *flag)
{
	int		i;

	i = 0;
  ft_printf("ch_ant\n");
	while (line[i])
	{
		if (!ft_isdigit(line[i]) || IS_ZERO)
			exit(PRT_ERROR);
		i++;
	}
	*flag = ROOM;
	return (SUCCESS);
}

/*
checks room :
- not a tube
- not 3 elts or room saved already
- incorrect room name
- room coordinates are not digits
*/
static int    ch_room(t_data *data, char *line, int *flag, int *st_end_flg)
{
  char  **tab;
  int   i;

  tab = ft_strsplit_c(line, ' ');
  ft_printf("ch_room\n");
  if (NO_THREE_ELTS && *st_end_flg == TRUE)
    exit(PRT_ERROR);
  if (IS_TUBE)
    return (ft_tube(tab, flag));
  if (NO_THREE_ELTS)
    exit(PRT_ERROR);
  if (INCORRECT_ROOM_NAME)
    exit(PRT_ERROR);
  if (ROOM_ALREADY_SAVED)
    exit(PRT_ERROR);
  i = -1;
	while (tab[1][++i])
		if (!ft_isdigit(tab[1][i]))
			exit(PRT_ERROR);
	i = -1;
	while (tab[2][++i])
		if (!ft_isdigit(tab[2][i]))
			exit(PRT_ERROR);
	ft_free_tab(tab);
  *st_end_flg = FALSE;
  return (SUCCESS);
}

/*
check list :
- 2 elements for tube
- rooms have been saved
- tube rooms presents in room list
- tube is present only once
*/
static int    ch_tube(t_data *data, char *line)
{
  char  **tab;

  tab = ft_strsplit_c(line, '-');
  ft_printf("ch_tube\n");
  if (NO_TWO_ELTS)
    exit(PRT_ERROR);/*
  if (THERE_ARE_ROOMS == FALSE)
    exit(PRT_ERROR);
  if (ft_index_room(data, tab[0]) != NOT_FOUND ||
    ft_index_room(data, tab[1]) != NOT_FOUND)
    exit(PRT_ERROR);
  if (TUBE_ALREADY_SAVED)
    exit(PRT_ERROR);*/
  ft_free_tab(tab);
  return (SUCCESS);
}

static int  ch_st_end(t_data *data, char *line, int *st_end_flg)
{
  if (IS_START_CMD)
    data->st_cmd++;
  else if (IS_END_CMD)
    data->end_cmd++;
  *st_end_flg = TRUE;
  return (SUCCESS);
}


/*
check errors :
- line is NULL
- empty line
- line starts with ##start or ##end before the ant number or just after a valid
cmd
- checks ant
- check room
- check tube
*/
int				check_line(t_data *data, char *line, int *flag)
{
  static int i = 0;
  static int st_end_flg = FALSE;

  ft_printf("%d\n", i);
  i++;
	if (line == NULL)
		return (FAIL);
	if (IS_EMPTY_LINE)
		return (FAIL);
	if (IS_COMMENT && !IS_START_CMD && !IS_END_CMD)
		return (COMMENT);
  if ((IS_START_CMD || IS_END_CMD) && (*flag == ANT || st_end_flg == TRUE))
    exit(PRT_ERROR);
	if (*flag == ANT)
		return (ch_nb_ants(line, flag));
  if (IS_START_CMD || IS_END_CMD)
    return (ch_st_end(data, line, &st_end_flg));
	if (*flag == ROOM)
    ch_room(data, line, flag, &st_end_flg);
  ft_printf("flag : %d\n", *flag);
	if (*flag == TUBE)
		ch_tube(data, line);
	return (SUCCESS);
}
