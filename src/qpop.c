/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qpop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 10:20:38 by iwordes           #+#    #+#             */
/*   Updated: 2017/06/22 11:18:19 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

/*
** Safely copy and remove the next job to work on from a pool.
*/

t_tp_job	tp_qpop(t_tp *tp)
{
	t_tp_job	job;

	tp_mlock(&WORQ.lock);
	while (WORQ.len == 0)
		tp_evwait(&WORQ.ev_new, &WORQ.lock);
	WORQ.len -= 1;
	job = WORQ.q[WORQ.f];
	WORQ.f = (WORQ.f + 1) % WORQ.max;
	tp_munlock(&WORQ.lock);
	return (job);
}
