#include "push_swap.h"
#include <assert.h>

t_stack	*test_stack(int n)
{
	t_stack *s = (t_stack *)malloc(sizeof(t_stack));
	int i = 0;

	if (s == NULL)
		return (NULL);
	s->ops = NULL;
	s->j = NULL;
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

t_stack	*n(t_stack *s, t_stack *(*op)(t_stack *))
{
	if (s == NULL)
		return (NULL);
	op(s);
	return (s);
}

void run_test(char *msg, int size, t_stack *(*optype)(t_stack *, t_stack *(*)(t_stack *), int), t_stack *(*op)(t_stack *), int verbose)
{
	t_stack *s = test_stack(size);

	if (verbose == 2)
	{
		print_stack(s->a, 'a');
		print_stack(s->b, 'b');
	}
	ft_printf("%s\n", msg);
	optype(s, op, 0);
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

	s = test_stack(2);
	//print_stack(s->a, 'a');
	//print_stack(s->b, 'b');
	ft_printf("copy_stack\n");
	c = copy_stack(s);
	//b(s, &swap);
	//print_stack(c->a, 'a');
	//print_stack(c->b, 'b');
	ft_printf("s->a:%p c->a:%p\n", s->a, c->a);
	run_test("rra", 8, &r, &rrot, 2);
	s->ops = add_node(0);
	s->ops->next = add_node(1);
	//print_stack(s->ops, 'o');
	s->ops = remove_last(s->ops);
	//print_stack(s->ops, 'o');
	ft_printf("%x", (15 >> 2) & 3);
	return (0);
}
