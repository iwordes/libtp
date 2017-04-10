/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qpush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:19:18 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/10 09:27:04 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

t_tp_job	*last_(t_tp *tp)
{
	t_tp_job	*last;

	last = JOB.q;
	if (last)
		while (last->next)
			last = last->next;
	return (last);
}

/*
** Add a job to the job queue.
** Will fail if allocation for the new job fails.
*/

bool		tp_qpush(t_tp *tp, void *job, void *ctx)
{
	t_tp_job	*last;

	tp_lock(&JOB.lock);
	last = last_(tp);
	if (last == NULL)
	{
		if ((JOB.q = ZALT(t_tp_job, 1)) == NULL)
			return (false);
		last = JOB.q;
	}
	else
	{
		if ((last->next = ZALT(t_tp_job, 1)) == NULL)
			return (false);
		last = last->next;
	}
	JOB.cnt += 1;
	last->fn = job;
	last->ctx = ctx;
	tp_evfire(&JOB.ev_new);
	tp_unlock(&JOB.lock);
	return (true);
}
