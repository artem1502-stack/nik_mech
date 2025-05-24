#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define STR_SIZE 1024

typedef struct s_jpg_file{
	size_t	height;
	size_t	width;
	size_t	size;
	char	*name;
}	t_jpg_file;

void readdir_deep(const char *sf, int *n, int *n_max, char ***names)
{
	DIR *dp = opendir(sf);
	char buff[STR_SIZE];

	if (!dp)
		return ;

	struct dirent *de;
	de = readdir(dp);
	while(de)
	{
		if ((strcmp(de->d_name, ".") != 0)
					&& (strcmp(de->d_name, "..") != 0))
		{
			if (de->d_type == 4)
			{
				strcpy(buff, sf);
				strcat(buff, "/");
				strcat(buff, de->d_name);
				//printf("%s\n", buff);
				readdir_deep(buff, n, n_max, names);
			}
			else
			{
				(*names)[*n] = (char *)malloc(STR_SIZE * sizeof(char));
				strcpy((*names)[*n], sf);
				strcat((*names)[*n], "/");
				strcat((*names)[*n], de->d_name);
				(*n)++;
				if (*n >= *n_max)
				{
					(*n_max) *= 2;
					*names = (char **)realloc(*names, (*n_max) * sizeof(char *));
				}
			}
		}
		de = readdir(dp);
	}
	closedir(dp);
}

void free_names(char **names, int n)
{
	int i;

	for (i = 0; i < n; i++)
		free(names[i]);
	free(names);
}

char **get_names(int *n)
{
	int n_max = 64, i;
	char **names;

	*n = 0;
	names = (char **)malloc(n_max * sizeof(char *));
	readdir_deep(".", n, &n_max, &names);
	return names;
}

void del_name(char **names, int n, int index)
{
	int i;

	free(names[index]);
	for (i = index; i < n - 1; i++)
		names[i] = names[i + 1];
}

// 0xFF 0xD8 0xFF

void check_names(char **names, int *n)
{
	int i;
	FILE *f;
	unsigned char bytes[3];

	for (i = 0; i < *n; i++)
	{
		f = fopen(names[i], "r");
		if (!f)
		{
			printf("Cannot open\n");
			del_name(names, *n, i);
			(*n)--;
			i--;
			continue ;
		}
		fread(bytes, 3, 1, f);
		if ((bytes[0] != 0xff) || (bytes[1] != 0xd8) || (bytes[2] != 0xff))
		{
			del_name(names, *n, i);
			(*n)--;
			i--;
		}
		fclose(f);
	}

}

//						   H       W
// ... [ff c0] d8 c3 c2 [ff da] [00 ff]
// 275 × 183 
// 0xffc0
void check_image(const char *image_name, size_t	*height, size_t	*width, size_t *size)
{
	FILE *f;
	int i, i_pos;
	unsigned char *buffer;
	long len;

	f = fopen(image_name, "rb");
	
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = (unsigned char *)malloc((len + 1) * sizeof(unsigned char));
	fread(buffer, 1, len, f);

	for (i = 0; i < len; i++)
	{
		if ((buffer[i]==0xFF) && (buffer[i + 1] == 0xC0))
		{
			i_pos = i;
			break ;
		}
	}

	i_pos += 5;
	*height = buffer[i_pos]<<8|buffer[i_pos + 1];
	*width = buffer[i_pos+2]<<8|buffer[i_pos + 3];
	*size = len;
	free(buffer);
	fclose(f);
}

void print_jpg_file(t_jpg_file *file)
{
	printf("Height = %zu\nWidht = %zu\nSize = %zu\nName = %s\n",
		file->height, file->width, file->size, file->name);
}

void free_files(t_jpg_file **files, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		free(files[i]->name);
		free(files[i]);
	}
	free(files);
}

t_jpg_file **get_files(char **names, int n)
{
	int i;
	t_jpg_file **files;

	files = (t_jpg_file **)malloc(n * sizeof(t_jpg_file *));
	for (i = 0; i < n; i++)
	{
		files[i] = (t_jpg_file *)malloc(sizeof(t_jpg_file));
		check_image(names[i], &files[i]->height, &files[i]->width,
						&files[i]->size);
		files[i]->name = strdup(names[i]);
	}
	return files;
}

void copy_jpg_file(t_jpg_file *src, t_jpg_file *dst)
{
	dst->height = src->height;
	dst->width = src->width;
	dst->size = src->size;
	dst->name = strdup(src->name);
}

void big_file_only(t_jpg_file **files, int *n)
{
	size_t max = 0, max_counter = 0;
	int i, j;

	for (i = 0; i < *n; i++)
	{
		if (files[i]->width > max)
		{
			max = files[i]->width;
			max_counter = 1;
		}
		else if (files[i]->width == max)
		{
			max_counter++;
		}
	}
	printf("max_counter = %zu\n", max_counter);
	for (i = 0; i < *n; i++)
	{
		if (files[i]->width != max)
		{
			free(files[i]->name);
			free(files[i]);
			for (j = i; j < *n - 1; j++)
				files[j] = files[j + 1];
			(*n)--;
			i--;
		}
	}
}

void sort_files(t_jpg_file **files, int n)
{
	int i, j;
	t_jpg_file *temp_file;

	for (i = 0; i < n; i++)
		for (j = 0; j < n - 1; j++)
		{
			if (files[j]->size < files[j + 1]->size)
			{
				temp_file = files[j];
				files[j] = files[j + 1];
				files[j + 1] = temp_file;
			}
		}
}

void copy_file(t_jpg_file *file, int index, const char *dir_name)
{
	char buff[STR_SIZE];
	FILE *in, *out;
	int len;

	sprintf(buff, "%s/file_%d.jpg", dir_name, index);

	in = fopen(file->name, "rb");
	out = fopen(buff, "wb");

	len = fread(buff, 1, STR_SIZE, in);
	while(len > 0)
	{
		fwrite(buff, 1, len, out);
		len = fread(buff, 1, STR_SIZE, in);
	}
	fclose(in);
	fclose(out);
}

void copy_files(t_jpg_file **files, int n, const char *dir_name)
{
	int status = mkdir(dir_name, 0755);
	int i;

	for (i = 0; i < n; i++)
	{
		copy_file(files[i], i, dir_name);
	}
}

int main(int argc, char *argv[])
{
	char **names;
	t_jpg_file **files;
	int n, i;

	if (argc != 2)
	{
		printf("Bad args\n");
		return -1;
	}

	//	Этап 1
	names = get_names(&n);
	//	Этап 2
	check_names(names, &n);
	//	Этап 3
	files = get_files(names, n);
	//	Этап 4
	big_file_only(files, &n);
	//	Этап 5
	sort_files(files, n);
	//	Этап 6
	copy_files(files, n, argv[1]);

	free_names(names, n);
	free_files(files, n);
	return 0;
}
