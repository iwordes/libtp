/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qwait.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:20:20 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/09 16:01:11 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libpt.h>

/*
** Wait for the queue to empty.
*/

void	tp_qwait(void)
{
	tp_lock(JOB.lock);
	while (JOB.cnt != 0)
		tp_evwait(JOB.ev_done, JOB.lock);
	tp_unlock(JOB.lock);
}
