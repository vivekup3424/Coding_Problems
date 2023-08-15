#include <stdio.h>
int main()
{
	int i,num,j;
	printf("ENter the number: ");
	scanf("%d", &num);
	for(i=1;i<num;i++)
		j = j*i;
	printf("The factorial of %d is %d\n",num,j);
}

