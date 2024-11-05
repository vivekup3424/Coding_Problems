#include <stdio.h>
void drawNormal(int height){
	char arr[height+1][2 * height+1];
	for(int j = 0; j < 2 * height+1; j++){
		int rem = j % height;
		for(int i = 0; i < height+1; i++){
			if(rem>0){
				arr[i][j] = '-';
				rem--;
			}else{
				arr[i][j] = '#';
			}
		}
	}
	for(int i = 0; i < 2*height+1; i++){
		for(int j = 0; j < height+1; j++){
			printf("%c",arr[i][j]);
		}
		printf("\n");
	}
}
int main(int argc, char *argv[])
{
	printf("Enter the height of the normal curve:-\n");
	int n;
	scanf("%d",&n);
	drawNormal(n);
	return 0;
}

