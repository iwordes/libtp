/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qpush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:19:18 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/09 16:34:57 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libpt_.h>

t_job	*last_(void)
{
	t_job	*last;

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

bool	tp_qpush(void *job, void *arg)
{
	t_job	*last;

	tp_lock(JOB.lock);
	last = last_();
	if (last == NULL)
	{
		if ((JOB.q = MALT(t_job, 1)) == NULL)
			return (false);
		last = JOB.q;
	}
	else
	{
		if ((last->next = MALT(t_job, 1)) == NULL)
			return (false);
		last = last->next;
	}
	JOB.cnt += 1;
	last->fn = job;
	last->ctx = ctx;
	tp_evfire(JOB.ev_new);
	tp_unlock(JOB.lock);
	return (true);
}
