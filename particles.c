#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{

	long long int N, L, K, *a_time, *b_time, *a_vel, *b_vel, i;

	scanf("%lld %lld %lld", &N, &L, &K);

	a_time = malloc(N * sizeof(long long int));
	b_time = malloc(N * sizeof(long long int));
	a_vel = malloc(N * sizeof(long long int));
	b_vel = malloc(N * sizeof(long long int));

	long long int tmax = 0;

	for(i=0; i<N; i++)
	{
		scanf("%lld", &a_time[i]);
		if (a_time[i] > tmax)
			tmax = a_time[i];
		scanf("%lld", &a_vel[i]);
	}

	for(i=0; i<N; i++)
	{
		scanf("%lld", &b_time[i]);
		if (b_time[i] > tmax)
			tmax = b_time[i];
		scanf("%lld", &b_vel[i]);
	}

	long long int first_a, first_b, second_a, second_b,j;
	long double mid, left, right, pos_first_a, pos_first_b, pos_sec_a, pos_sec_b, temp;

	second_a = 0;
	second_b = 0;
	left = a_time[0];

	if (b_time[0] > left)
		left = b_time[0];

	bool flag;

	for(i=0; i<K; i++)
	{
		if (a_vel[second_a] != 0 || b_vel[second_b] != 0)
			right = (L + a_vel[second_a]*a_time[second_a] + b_vel[second_b] * b_time[second_b])/(a_vel[second_a] + b_vel[second_b]) + 5;
		else
			right = L + 1000000000;

		while (left <= right)
		{
			mid = (left + right) / 2;
			flag = true;
			j = 0;
			pos_first_a = 0;
			pos_sec_a = 0;

			while (flag)
			{
				if (a_time[j] > mid)
					flag = false;
				else {
					temp = (mid - a_time[j]) * (a_vel[j]);
					if (temp > pos_first_a) {
						pos_sec_a = pos_first_a;
						second_a = first_a;
						pos_first_a = temp;
						first_a = j;
					} else if (temp > pos_sec_a) {
						pos_sec_a = temp;
						second_a = j;
					}

					j++;
					if (j > N - 1)
						flag = false;
				}
			}

			flag = true;
			j = 0;
			pos_first_b = L;
			pos_sec_b = L;

			while (flag)
			{
				if (b_time[j] > mid)
					flag = false;
				else
				{
					temp = L - ((mid - b_time[j]) * (b_vel[j]));
					if (temp < pos_first_b)
					{
						pos_sec_b = pos_first_b;
						second_b = first_b;
						pos_first_b = temp;
						first_b = j;
					}
					else if (temp < pos_sec_b)
					{
						pos_sec_b = temp;
						second_b = j;
					}
				}
				j++;
				if (j > N - 1)
					flag = false;
			}
			if (pos_first_a < pos_first_b)
				left = mid;
			else if ((pos_sec_a > pos_sec_b) || (pos_sec_a > pos_first_b) || (pos_sec_b < pos_first_a))
				right = mid;
			else
			{
				left = 1;
				right = 0;
				printf("%lld %lld\n", first_a + 1, first_b + 1);
			}

		}
		left=(L+a_vel[first_a]*a_time[first_a]+b_vel[first_b]*b_time[first_b])/(a_vel[first_a]+b_vel[first_b]);
		a_vel[first_a] = 0;
		b_vel[first_b] = 0;
		a_time[first_a] = 0;
		b_time[first_b] = 0;
	}

	return 0;
}
