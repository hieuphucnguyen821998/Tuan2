#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<malloc.h>
#define N 200
typedef struct {
	char a[N];
	int pos[N];
	int top;
}stack;
void initialize(stack *pile) {
	pile->top = -1;
	memset(pile->pos, -1, sizeof(pile->pos));
}
int stack_full(stack *pile) {
	if (pile->top >= N) return 1;
	return 0;
}
int stack_empty(stack *pile) {
	if (pile->top == -1) return 1;
	return 0;
}
int pop_stack(stack *pile) {
	if (stack_empty(pile) == 1) return 1;
	(pile->top)--;
	return 0;
}
int push_stack(stack *pile, char b, int location) {
	if (stack_full(pile) == 1) return 1;
	pile->top++;
	pile->a[pile->top] = b;
	pile->pos[pile->top] = location;
	return 0;
}
int read(char *path, char *buffer);
int check_file(char *path);
int perform(char *a, stack *pile1, stack *pile2, stack *pile3);
int standardize(char *path, char *path2);
int main() {
	stack *pile1, *pile2, *pile3;
	pile1 = (stack*)calloc(1, sizeof(stack));
	pile2 = (stack*)calloc(1, sizeof(stack));
	pile3 = (stack*)calloc(1, sizeof(stack));
	char a[N], path[30], path2[30];
	int i, j = 0;
	printf("Moi ban nhap file chua day dau ngoac:");
	gets(path);
	standardize(path, path2);
	if (check_file(path2) == 1) {
		printf("file khong ton tai!");
		return 1;
	}
	else {
		read(path2, a);
		initialize(pile1);
		initialize(pile2);
		initialize(pile3);
		perform(a, pile1, pile2, pile3);
		free(pile1);
		free(pile2);
		free(pile3);
		printf("\nThuc hien xong. Hay kiem tra file BRACKET.OUT trong o D:");
	}
	return 0;
}
int standardize(char *path, char *path2)
{
	int i, j = 0;
	for (i = 0; i<strlen(path); i++) {
		if (path[i] == '\\') {
			if ((path[i + 1] != '\\') && path[i - 1] != '\\') {
				path2[j] = '\\';
				j++;
			}
		}
		path2[j] = path[i];
		j++;
	}
}
int read(char *path, char *buffer) {
	int i = 0;
	int c;
	FILE *file;
	file = fopen(path, "r");
	if (file) {
		while ((c = fgetc(file)) != EOF)
		{
			buffer[i] = (char)c;
			i++;
		}
		fclose(file);
	}
	return 0;
}
int check_file(char *path) {
	FILE *file;
	file = fopen(path, "r");
	if (file) {
		fclose(file);
	}
	else {
		return 1;
	}
	return 0;
}
int perform(char *a, stack *pile1, stack *pile2, stack *pile3) {
	char b[N];
	int i, count[N], j = 0, wrong = 0, total = 0;
	memset(count, -1, sizeof(count));
	FILE *doc;
	for (i = 0; i<strlen(a); i++) {
		if ((a[i] == '(') || (a[i] == '[') || (a[i] == '{')) {
			if (stack_full(pile1) == 1) {
				return 1;
			}
			if (stack_full(pile2) == 1) {
				return 1;
			}
			if (stack_full(pile3) == 1) {
				return 1;
			}
			if (a[i] == '(')
				push_stack(pile1, a[i], i);
			if (a[i] == '{')
				push_stack(pile2, a[i], i);
			if (a[i] == '[')
				push_stack(pile3, a[i], i);
		}
		else {
			if (a[i] == ')') {
				if (stack_empty(pile1))
				{
					wrong = 1;
					count[j] = i;
					b[j] = '(';
					j++;
				}
				else pop_stack(pile1);
			}
			else if (a[i] == '}') {
				if (stack_empty(pile2)) {
					wrong = 1;
					count[j] = i;
					b[j] = '{';
					j++;
				}
				else pop_stack(pile2);
			}
			else if (a[i] == ']') {
				if (stack_empty(pile3)) {
					wrong = 1;
					count[j] = i;
					b[j] = '[';
					j++;
				}
				else pop_stack(pile3);
			}
		}
	}
	if ((pile1->top == -1) && (pile2->top == -1) && (pile3->top == -1) && (wrong == 0)) {
		doc = fopen("D:\\BRACKET.OUT.txt", "w");
		fprintf(doc, "0");
	}
	else {
		j = 0;
		while (count[j] != -1)
		{
			total++;
			j++;
		}
		if (stack_empty(pile1) == 0) {
			total += pile1->top;
			total++;
		}
		if (stack_empty(pile2) == 0) {
			total += pile2->top;
			total++;
		}
		if (stack_empty(pile3) == 0) {
			total += pile3->top;
			total++;
		}
		doc = fopen("D:\\BRACKET.OUT.txt", "w");
		fprintf(doc, "%d\n", total);
		i = 0;
		if (stack_empty(pile1) == 0) {
			while (i <= pile1->top) {
				fprintf(doc, ") %d\n", pile1->pos[i] + 1);
				i++;
			}
			i = 0;
		}
		if (stack_empty(pile2) == 0) {
			while (i <= pile2->top) {
				fprintf(doc, "} %d\n", pile2->pos[i] + 1);
				i++;
			}
			i = 0;
		}
		if (stack_empty(pile3) == 0) {
			while (i <= pile3->top) {
				fprintf(doc, "] %d\n", pile3->pos[i] + 1);
				i++;
			}
		}
		i = 0;
		while (count[i] != -1) {
			if (b[i] == '(')
				fprintf(doc, "( %d\n", count[i]);
			if (b[i] == '[')
				fprintf(doc, "[ %d\n", count[i]);
			if (b[i] == '{')
				fprintf(doc, "{ %d\n", count[i]);
			i++;
		}
	}
	fclose(doc);
	return 0;
}
