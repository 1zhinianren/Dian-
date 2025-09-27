#include  <stdio.h>
#include  <string.h>
int main(void)
{
	printf("«Î ‰»Î£∫");
	char* s = "Dian";
	char* t = "Quit";
	char word[100];
	scanf_s("%s", word,100);
	while (strcmp(word, t) != 0) {
		if (strcmp(word, s) == 0) {
			printf("2002\n");
		}
		else {
			printf("Error\n");
		}
		printf("«Î ‰»Î:");
		scanf_s("%s", word,100);
	}
	return 0;

}