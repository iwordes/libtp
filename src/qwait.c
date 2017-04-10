/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qwait.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:20:20 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/09 20:11:28 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

void	tp_qwait(t_tp *tp)
{
	tp_lock(&JOB.lock);
	while (JOB.cnt != 0)
		tp_evwait(&JOB.ev_done, &JOB.lock);
	tp_unlock(&JOB.lock);
}
