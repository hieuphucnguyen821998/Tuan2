#include <stdio.h>
#include <string.h>
#include <conio.h>
int check_file(char *path);
int replace(char *buffer, int *count1, int m);
int read(char *path, char *buffer);
int seek(char *buff3, int k, int *count1, char *path);
int write(int k, int total, int num_col, int num_row, int *col, int *row, char* buff, char* buff2, int *next);
int title_file(char *path);
int main() {
	int n, count1 = 1;
	char buff[20], renew[300];
	int i = 0, j = 0;
	char path[100], path2[100];
	memset(path, 0, sizeof(path));
	memset(path2, 0, sizeof(path2));
	memset(renew, 0, sizeof(renew));
	printf("Nhap ten file:");
	gets(path);
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
	if (check_file(path2) == 1) return 1;
	title_file(path);
	printf("\n1.Search\n2.Replace\n3.Exit");
	do {
		printf("\nPlease choose the feature:");
		scanf("%d", &n);
		fflush(stdin);
		switch (n) {
		case 1:
			printf("\n\nKy tu can tim:");
			gets(buff);
			seek(buff, n, &count1, path2);
			break;
		case 2:
			read(path2, renew);
			replace(renew, &count1, n);
			break;
		}
		count1++;
	} while (n != 3);
	return 0;
}
int title_file(char *path) {
	FILE *file;
	file = fopen("D:\\OUTPUT.TXT", "w");
	if (file) {
		fprintf(file, "Input file:%s\n", path);
		fclose(file);
	}
	else {
		return 1;
	}
	return 0;
}
int check_file(char *path) {
	FILE *file;
	file = fopen(path, "r");
	if (file) {
		printf("\nValid file");
		fclose(file);
	}
	else {
		printf("\nInvalid file");
		return 1;
	}
	return 0;
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
int seek(char *buff3, int k, int *count1, char *path) {
	char buffer[300];
	char buff[20], buff2[20];
	int i = 0, j = 0, c, new_line = 1, x = 0, y = 1, appear = 0, column = 0, column2, line[10], col[10];
	memset(buffer, 0, sizeof(buffer));
	memset(buff2, 0, sizeof(buff2));
	memset(buff, 0, sizeof(buff));
	memset(col, 0, sizeof(col));
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
	i = 0;
	line[0] = 1;
	while (i <= strlen(buffer)) {
		//Doc tung chu trong buffer
		while ((buffer[i] != ' ') && (i != strlen(buffer)) && (buffer[i] != '\n') && (buffer[i] != '.') && (buffer[i] != ',')) {
			buff2[j] = buffer[i];
			i++;
			j++;
			column++;
		}
		column++;
		column2 = column;
		//Neu xuong dong thi tang gia tri new_line va dat gia tri column=0
		if (buffer[i] == '\n') {
			col[x] = -1;
			x++;
			new_line++;
			column = 0;
			line[y] = new_line;
			y++;
		}
		j = 0;
		//So sanh chu vua doc trong buffer va so sanh voi tu can tim
		if (strcmp(buff3, buff2) == 0) {
			col[x] = column2 - 1 - strlen(buff2);
			x++;
			printf("\nLine:%d Column:%d", new_line, (column2 - 1 - strlen(buff2)));
			appear++;
		}
		//dat la gia tri 0 cho bo nho
		memset(buff2, 0, sizeof(buff2));
		i++;
	}
	printf("\nTotal appearance:%d", appear);
	//ghi vao file thao tac vua lam
	write(k, appear, x, y, col, line, buff3, "hello", count1);
	return 0;
}
int replace(char *buffer, int *count1, int m) {
	char seek[20], buff2[20];
	char replacing[20];
	char new_buffer[300];
	int i = 0, j = 0, column[10], col1 = 0, column1 = 0, column2, x = 0, y = 1, new_line = 1, line[10], col[10], appear = 0;
	memset(seek, 0, sizeof(seek));
	memset(column, -1, sizeof(column));
	memset(new_buffer, 0, sizeof(new_buffer));
	printf("%s\n", buffer);
	printf("\nNhap tu can tim:");
	gets(seek);
	line[0] = 1;
	while (i <= strlen(buffer)) {
		while ((buffer[i] != ' ') && (i != strlen(buffer)) && (buffer[i] != '\n') && (buffer[i] != '.') && (buffer[i] != ',')) {
			buff2[j] = buffer[i];
			i++;
			j++;
			column1++;
		}
		column1++;
		column2 = column1;
		if (buffer[i] == '\n') {
			col[x] = -1;
			x++;
			new_line++;
			column1 = 0;
			line[y] = new_line;
			y++;
		}
		j = 0;
		if (strcmp(seek, buff2) == 0) {
			col[x] = column2 - 1 - strlen(buff2);
			x++;
			appear++;
			column[col1] = i - strlen(buff2);
			col1++;
		}
		memset(buff2, 0, sizeof(buff2));
		i++;
	}
	if (appear == 0) {
		printf("\nTu vua nhap khong co...");
		return 1;
	}
	j = 0;
	i = 0;
	int k = 0, g;
	printf("\nNhap tu moi:");
	gets(replacing);
	while (i<strlen(buffer)) {
		if (i == column[k]) {
			for (g = 0; g<strlen(replacing); g++)
			{
				new_buffer[j] = replacing[g];
				j++;
			}
			k++;
			i += strlen(seek);
		}
		new_buffer[j] = buffer[i];
		j++;
		i++;
	}
	printf("\n%s", new_buffer);
	write(m, appear, x, y, col, line, seek, replacing, count1);
	return 0;
}
int write(int k, int total, int num_col, int num_row, int *col, int *row, char* buff, char* buff2, int *next) {
	int i, j = 0;
	FILE *file;
	file = fopen("D:\\OUTPUT.TXT", "a");
	if (file) {
		if (k == 1) {
			fprintf(file, "Context %d: search keyword\n", *next);
			fprintf(file, "Keyword:%s\n", buff);
			fprintf(file, "Total position:%d\n", total);
			for (i = 0; i<num_col; i++) {
				if (col[i] == -1) {
					if (col[i + 1] == 0) break;
					j++;
					i++;
				}
				fprintf(file, "Ln %d, Col %d\n", row[j], col[i]);
			}
		}
		else {
			fprintf(file, "Context %d: replace by new key word\n", *next);
			fprintf(file, "Keyword:%s\n", buff);
			fprintf(file, "New keyword:%s\n", buff2);
			for (i = 0; i<num_col; i++) {
				if (col[i] == -1) {
					if (col[i + 1] == 0) break;
					j++;
					i++;
				}
				fprintf(file, "Ln %d, Col %d\n", row[j], col[i]);
			}
			fprintf(file, "Total position:%d", total);
		}
		fclose(file);
	}
	else return 1;
	return 0;
}

