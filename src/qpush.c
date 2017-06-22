/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qpush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:19:18 by iwordes           #+#    #+#             */
/*   Updated: 2017/06/22 11:18:49 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

/*
** Safely add a new job to a pool's work queue.
*/

bool	tp_qpush(t_tp *tp, void *job, void *ctx)
{
	tp_mlock(&WORQ.lock);
	if (WORQ.len == WORQ.max)
	{
		tp_munlock(&WORQ.lock);
		return (false);
	}
	WORQ.len += 1;
	WORQ.undone += 1;
	WORQ.q[WORQ.b].fn = job;
	WORQ.q[WORQ.b].ctx = ctx;
	WORQ.b = (WORQ.b + 1) % WORQ.max;
	tp_evfire(&WORQ.ev_new);
	tp_munlock(&WORQ.lock);
	return (true);
}
