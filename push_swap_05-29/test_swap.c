#include "push_swap.h"
#include <assert.h>

t_stack	*test_stack(int n)
{
	t_stack *s = (t_stack *)malloc(sizeof(t_stack));
	int i = 0;

	if (s == NULL)
		return (NULL);
	s->a = add_node(++i);
	s->i = s->a;
	while (i++ < n / 2)
		s->i = append_node(i, s->i);
	s->b = add_node(i);
	s->i = s->b;
	while (i++ < n)
		s->i = append_node(i, s->i);
	return (s);
}

void print_stack(t_node *n, char c)
{
	if (c)
	{
		ft_printf("%c: ");
		c = 0;
	}
	if (n != NULL)
		ft_printf("[%d]", n->data);
	if (n->next != NULL)
		{
			ft_printf("->");
			print_stack(n->next, 0);
		}
	else 
		ft_printf("\n");
}

t_stack	*n(t_stack *s, t_stack *(*op)(t_stack *))
{
	if (s == NULL)
		return (NULL);
	op(s);
	return (s);
}

void run_test(char *msg, int size, t_stack *(*optype)(t_stack *, t_stack *(*)(t_stack *)), t_stack *(*op)(t_stack *), int verbose)
{
	t_stack *s = test_stack(size);

	if (verbose == 2)
	{
		print_stack(s->a, 'a');
		print_stack(s->b, 'b');
	}
	ft_printf("%s\n", msg);
	optype(s, op);
	if (verbose > 0)
	{
		print_stack(s->a, 'a');
		print_stack(s->b, 'b');
	}
}

int main(void)
{
	t_stack	*s;
	t_stack *c;

	s = test_stack(6);
	print_stack(s->a, 'a');
	print_stack(s->b, 'b');
	ft_printf("copy_stack\n");
	c = copy_stack(s);
	//b(s, &swap);
	print_stack(c->a, 'a');
	print_stack(c->b, 'b');
	ft_printf("s->a:%p c->a:%p", s->a, c->a);
	//run_test("rrr", 6, &r, &rrot, 1);

	return (0);
}
