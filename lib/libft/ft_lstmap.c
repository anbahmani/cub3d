/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 08:21:10 by abahmani          #+#    #+#             */
/*   Updated: 2021/01/23 11:42:09 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l;
	t_list	*new;
	t_list	*head;

	if (!lst)
		return (NULL);
	l = lst->next;
	head = ft_lstnew((*f)(lst->content));
	if (!head)
		return (NULL);
	new = head;
	lst = l;
	while (l)
	{
		new->next = ft_lstnew((*f)(l->content));
		if (!(new->next))
		{
			ft_lstclear(&head, (*del));
			return (NULL);
		}
		new = new->next;
		l = l->next;
		lst = l;
	}
	return (head);
}
