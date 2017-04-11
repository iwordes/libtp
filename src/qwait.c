/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qwait.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:20:20 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/11 10:47:00 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

/*
** TODO: Wait for specific tasks
** (create a per-job condition)
**
** Would return a t_tp_evt* for the job in question.
** void	*tp_qpush(t_tp *tp, void *job, void *ctx);
**
** ...
**
** tp_qwait(tp, job*, ..., NULL)
**
** job
** {
**     t_tp_evt	done;
**     ...
** }
*/

void	tp_qwait(t_tp *tp)
{
	tp_lock(&JOB.lock);
	while (JOB.cnt != 0)
		tp_evwait(&JOB.ev_done, &JOB.lock);
	tp_unlock(&JOB.lock);
}
