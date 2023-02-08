#include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "despart fraza in cuvinte";
	char *ptr = strtok(str, " ");
    char* maxim;
    int i=0;
	while(ptr != NULL)
	{
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, " ");
		//printf("%d", strlen(ptr));
		char[i]=ptr);
		i++;
	}



	return 0;
}
