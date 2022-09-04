#include "circular_buffer.h"
#include <stdio.h>
#include <stdlib.h>

int circular_buffer_create(struct circular_buffer_t* a, int N)
{
	if (a == NULL || N <= 0) return 1;
	a->ptr = malloc(sizeof(int) * N);
	if (a->ptr == NULL) return 2;
	a->begin = 0;
	a->end = 0;
	a->capacity = N;
	a->full = 0;

	return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t** cb, int N)
{
	if (cb == NULL || N <= 0) return 1;
	*cb = malloc(sizeof(struct circular_buffer_t));
	if (*cb == NULL) return 2;
	if (circular_buffer_create(*cb, N) == 2)
	{
		free(*cb);
		return 2;
	}

	return 0;
}

void circular_buffer_destroy(struct circular_buffer_t* a)
{
	if (a != NULL && a->ptr != NULL)
		free(a->ptr);
}

void circular_buffer_destroy_struct(struct circular_buffer_t** a)
{
	if (a != NULL)
	{
		circular_buffer_destroy(*a);
		free(*a);
	}
}

int circular_buffer_push_back(struct circular_buffer_t* cb, int value)
{
	if (cb == NULL) return 1;
	if (cb->begin < 0 || cb->begin >= cb->capacity || cb->end < 0 || cb->end >= cb->capacity || cb->ptr == NULL) return 1;
	if (circular_buffer_empty(cb))
	{
		*(cb->ptr + cb->end) = value;
		if (cb->end == cb->capacity - 1)
			cb->end = 0;
		else
			cb->end += 1;
		if (cb->end == cb->begin) cb->full = 1;
	}
	else if (circular_buffer_full(cb))
	{
		*(cb->ptr + cb->end) = value;
		if (cb->end == cb->capacity - 1)
			cb->end = 0;
		else
			cb->end += 1;
		cb->begin = cb->end;
	}
	else 
	{
		*(cb->ptr + cb->end) = value;
		if (cb->end == cb->capacity - 1)
			cb->end = 0;
		else
			cb->end += 1;
		if (cb->begin == cb->end) cb->full = 1;

	}
	return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t* a, int* err_code)
{
	if (a == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return 0;
	}
	if (a->begin < 0 || a->begin >= a->capacity || a->end < 0 || a->end >= a->capacity || a->ptr == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return 1;
	}
	if (circular_buffer_empty(a))
	{
		if (err_code != NULL)
			*err_code = 2;
		return 0;
	}
	int b = *(a->ptr + a->begin);
	if (circular_buffer_full(a))
	{
		a->full = 0;
		if (a->begin == a->capacity - 1)
			a->begin = 0;
		else
			a->begin += 1;
	}
	else
	{
		if (a->begin == a->capacity - 1)
			a->begin = 0;
		else
			a->begin += 1;
	}
	if (err_code != NULL)
		*err_code = 0;
	return b;
}

int circular_buffer_pop_back(struct circular_buffer_t* a, int* err_code)
{
	if (a == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return 0;
	}
	if (a->begin < 0 || a->begin >= a->capacity || a->end < 0 || a->end >= a->capacity || a->ptr == NULL)
	{
		if (err_code != NULL)
			*err_code = 1;
		return 1;
	}
	if (circular_buffer_empty(a))
	{
		if (err_code != NULL)
			*err_code = 2;
		return 0;
	}
	if (circular_buffer_full(a))
	{
		a->full = 0;
		if (a->end == 0)
			a->end = a->capacity - 1;
		else
			a->end -= 1;
	}
	else
	{
		if (a->end == 0)
			a->end = a->capacity - 1;
		else
			a->end -= 1;
	}
	if (err_code != NULL)
		*err_code = 0;
	return *(a->ptr + a->end);
}

int circular_buffer_empty(const struct circular_buffer_t* a)
{
	if (a == NULL) return -1;
	if (a->begin < 0 || a->begin >= a->capacity || a->end < 0 || a->end >= a->capacity || a->ptr == NULL) return -1;
	if (a->begin == a->end && circular_buffer_full(a) == 0) return 1;
	else return 0;
}

int circular_buffer_full(const struct circular_buffer_t* a)
{
	if (a == NULL) return -1;
	if (a->begin < 0 || a->begin >= a->capacity || a->end < 0 || a->end >= a->capacity || a->ptr == NULL) return -1;
	if (a->full == 1) return 1;
	else return 0;
}

void circular_buffer_display(const struct circular_buffer_t* a)
{
	if (a != NULL && circular_buffer_empty(a) == 0)
	{
		int i = a->begin;
		if (a->begin == a->end)
		{
			printf("%d ", *(a->ptr + i));
			if (a->begin == a->capacity - 1)
				i = 0;
			else
				i++;
		}
		while (i != a->end)
		{
			printf("%d ", *(a->ptr + i));
			if (i == a->capacity - 1)
				i = 0;
			else
				i++;
		}
	}
}
