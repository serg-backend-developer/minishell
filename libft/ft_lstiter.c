#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst_pointer;

	if (!lst || !f)
		return ;
	lst_pointer = lst;
	while (lst_pointer)
	{
		f(lst_pointer->content);
		lst_pointer = lst_pointer->next;
	}
}
