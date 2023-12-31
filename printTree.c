
#include "tree.h"

// when no flag is used
void printTree(tnode t)
{
	node *p = t;
	int i;
	char *front = "|----", *down = "|    ";

	if (!p)
		return;

	if (p->isrootNode || p->fname[0] != '.')
	{
		printf("\n");
		for (i = 0; i < count; i++)
		{
			printf("%s", down);
		}

		if (count >= 0 && !p->isrootNode)
		{
			printf("%s", front);
		}

		// print directory name with green colour and file name with normal(default) colour
		if (p->isdir)
		{
			green();
			printf("%s", p->fname);
			reset();
		}
		else
		{
			// access() checks whether file is executable or not
			if (!access(p->fname, X_OK) || !strcmp(p->fname, "a.out"))
			{
				yellow();
				printf("%s", p->fname);
				reset();
			}
			else
				printf("%s", p->fname);
		}

		if (p->isdir)
		{
			if (p->isrootNode)
				printTree(p->inner_ptr);
			else
			{
				dir_count++; // incrementing directory count
				count++;
				printTree(p->inner_ptr);
				count--;
			}
		}
		if (!p->isdir)
			file_count++; // incrementing file count
	}

	printTree(p->next_ptr);

	return;
}

// When -a flag used (print private files and directories also)
void printTree_a(tnode t)
{
	node *p = t;
	int i;
	char *front = "|----", *down = "|    ";
	if (!p)
	{
		return;
	}
	printf("\n");
	for (i = 0; i < count; i++)
	{
		printf("%s", down);
	}

	if (count >= 0 && !p->isrootNode)
	{
		printf("%s", front);
	}

	// print directory name with green colour and file name with normal(default) colour
	if (p->isdir)
	{
		green();
		printf("%s", p->fname);
		reset();
	}
	else
	{
		if (!access(p->fname, X_OK) || !strcmp(p->fname, "a.out"))
		{
			yellow();
			printf("%s", p->fname);
			reset();
		}
		else
			printf("%s", p->fname);
	}

	if (p->isdir)
	{
		if (p->isrootNode)
			printTree_a(p->inner_ptr);
		else
		{
			dir_count++; // incrementing directory count
			count++;
			printTree_a(p->inner_ptr);
			count--;
		}
	}

	if (!p->isdir)
		file_count++; // incrementing file count
	printTree_a(p->next_ptr);
	// printf("\n");

	return;
}

// When -d flag used (print directories only)
void printTree_d(tnode t)
{
	node *p = t;
	int i;
	char *front = "|----", *down = "|    ";

	if (!p)
	{
		return;
	}
	if (p->isdir && (p->isrootNode || p->fname[0] != '.'))
	{
		printf("\n");
		for (i = 0; i < count; i++)
		{
			printf("%s", down);
		}

		if (count >= 0 && !p->isrootNode)
		{
			printf("%s", front);
		}

		// print directory name with green colour and file name with normal(default) colour
		if (p->isdir)
		{
			green();
			printf("%s", p->fname);
			reset();
		}
		/*else {
			if(!access(p->fname,X_OK) || !strcmp(p->fname, "a.out")) {
				yellow();
				printf("%s", p->fname);
				reset();
			}
			else
				printf("%s", p->fname);
		}
		*/
		if (p->isdir)
		{
			if (p->isrootNode)
				printTree_d(p->inner_ptr);
			else
			{
				dir_count++; // incrementing directory count
				count++;
				printTree_d(p->inner_ptr);
				count--;
			}
		}

		if (!p->isdir)
			file_count++; // incrementing file count
	}

	printTree_d(p->next_ptr);

	return;
}

// when -s flag is used (to display filenames along with their size in bytes)
void printTree_s(tnode t)
{
	node *p = t;
	int i;
	char *front = "|----", *down = "|    ";

	if (!p)
		return;

	if (p->isrootNode || p->fname[0] != '.')
	{
		printf("\n");
		for (i = 0; i < count; i++)
		{
			printf("%s", down);
		}

		if (count >= 0 && !p->isrootNode)
		{
			printf("%s", front);
		}

		long int k = p->info.fsize;
		int dig_count = 0;
		if (p->info.fsize)
		{
			while (k)
			{
				k /= 10;
				dig_count++;
			}
		}
		else
			dig_count = 1;

		// print directory name with green colour and file name with normal(default) colour
		if (p->isdir)
		{
			green();
			printf("%s  ", p->fname);
			reset();

			if (!p->isrootNode)
			{
				printf("[");
				// for(i = 0; i < LENGTH_OF_LONG_INT-dig_count; i++)
				//	printf(" ");
				printf("%lu bytes]", p->info.fsize);
			}
		}
		else
		{
			if (!access(p->fname, X_OK) || !strcmp(p->fname, "a.out"))
			{
				yellow();
				printf("%s  ", p->fname);
				reset();
			}
			else
				printf("%s  ", p->fname);

			printf("[");
			// for(i = 0; i < LENGTH_OF_LONG_INT-dig_count; i++)
			//	printf(" ");
			printf("%lu bytes]", p->info.fsize);
		}

		if (p->isdir)
		{
			if (p->isrootNode)
				printTree_s(p->inner_ptr);
			else
			{
				dir_count++;
				count++;
				printTree_s(p->inner_ptr);
				count--;
			}
		}
		if (!p->isdir)
			file_count++;
	}

	printTree_s(p->next_ptr);

	return;
}

// when -f flag is used (to display subdirectories and files along with their paths)
void printTree_f(tnode t)
{
	node *p = t;
	int i;
	char *front = "|----", *down = "|    ";
	// char *last = "'----";
	if (!p)
		return;

	if (p->isrootNode || p->fname[0] != '.')
	{
		printf("\n");
		for (i = 0; i < count; i++)
		{
			printf("%s", down);
		}

		if (count >= 0 && !p->isrootNode)
		{
			// if(p->next_ptr)
			printf("%s", front);
			// else
			//	printf("%s", last);
		}

		// print directory name with green colour and file name with normal(default) colour
		if (p->isdir)
		{
			green();
			printf("%s", p->info.fpath);
			reset();
		}
		else
		{
			if (!access(p->fname, X_OK) || !strcmp(p->fname, "a.out"))
			{
				yellow();
				printf("%s", p->info.fpath);
				reset();
			}
			else
				printf("%s", p->info.fpath);
		}

		if (p->isdir)
		{
			if (p->isrootNode)
				printTree_f(p->inner_ptr);
			else
			{
				dir_count++;
				count++;
				printTree_f(p->inner_ptr);
				count--;
			}
		}
		if (!p->isdir)
			file_count++;
	}

	printTree_f(p->next_ptr);

	return;
}

// when -Q flag is used (to quote the names of files in double quotes)
void printTree_Q(tnode t)
{
	node *p = t;
	int i;
	char *front = "|----", *down = "|    ";
	// char *last = "'----";
	if (!p)
		return;

	if (p->isrootNode || p->fname[0] != '.')
	{
		printf("\n");
		for (i = 0; i < count; i++)
		{
			printf("%s", down);
		}

		if (count >= 0 && !p->isrootNode)
		{
			// if(p->next_ptr)
			printf("%s", front);
			// else
			//	printf("%s", last);
		}

		// print directory name with green colour and file name with normal(default) colour
		if (p->isdir)
		{
			green();
			if (p->isrootNode)
				printf("%s", p->fname);
			else
				printf("\"%s\"", p->fname);
			reset();
		}
		else
		{
			if (!access(p->fname, X_OK) || !strcmp(p->fname, "a.out"))
			{
				yellow();
				printf("\"%s\"", p->fname);
				reset();
			}
			else
				printf("\"%s\"", p->fname);
		}

		if (p->isdir)
		{
			if (p->isrootNode)
				printTree_Q(p->inner_ptr);
			else
			{
				dir_count++;
				count++;
				printTree_Q(p->inner_ptr);
				count--;
			}
		}
		if (!p->isdir)
			file_count++;
	}

	printTree_Q(p->next_ptr);

	return;
}

// when -L level flag is used (print tree structure upto depth L)
void printTree_L(tnode t, int level)
{
	if (count >= level)
		return;
	node *p = t;
	int i;
	char *front = "|----", *down = "|    ";
	// char *last = "'----";
	if (!p)
		return;

	if (p->isrootNode || p->fname[0] != '.')
	{
		printf("\n");
		for (i = 0; i < count; i++)
		{
			printf("%s", down);
		}

		if (count >= 0 && !p->isrootNode)
		{
			// if(p->next_ptr)
			printf("%s", front);
			// else
			//	printf("%s", last);
		}

		// print directory name with green colour and file name with normal(default) colour
		if (p->isdir)
		{
			green();
			printf("%s", p->fname);
			reset();
		}
		else
		{
			if (!access(p->fname, X_OK) || !strcmp(p->fname, "a.out"))
			{
				yellow();
				printf("%s", p->fname);
				reset();
			}
			else
				printf("%s", p->fname);
		}

		if (p->isdir)
		{
			if (p->isrootNode)
				printTree_L(p->inner_ptr, level);
			else
			{
				dir_count++;
				count++;
				printTree_L(p->inner_ptr, level);
				count--;
			}
		}
		if (!p->isdir)
			file_count++;
	}

	printTree_L(p->next_ptr, level);

	return;
}

// when -h flag is used (to display filenames along with their size in human readable format)
void printTree_h(tnode t)
{
	node *p = t;
	int i;
	char *front = "|----", *down = "|    ";
	// char *last = "'----";
	if (!p)
		return;

	if (p->isrootNode || p->fname[0] != '.')
	{
		printf("\n");
		for (i = 0; i < count; i++)
		{
			printf("%s", down);
		}

		if (count >= 0 && !p->isrootNode)
		{
			// if(p->next_ptr)
			printf("%s", front);
			// else
			//	printf("%s", last);
		}

		long int k = p->info.fsize;
		int dig_count = 0;
		if (p->info.fsize)
		{
			while (k)
			{
				k /= 10;
				dig_count++;
			}
		}
		else
			dig_count = 1;

		// print directory name with green colour and file name with normal(default) colour
		if (p->isdir)
		{
			green();
			printf("%s  ", p->fname);
			reset();
			if (!p->isrootNode)
			{
				// printf("[");
				// for(i = 0; i < LENGTH_OF_LONG_INT-dig_count; i++)
				//	printf(" ");
				if (p->info.fsize < 1000)
					printf("[%lu]", p->info.fsize);
				else if (p->info.fsize < 1000000)
					printf("[%.1fK]", p->info.fsize / 1000.0);
				else if (p->info.fsize < 1000000)
					printf("[%.1fM]", p->info.fsize / 1000000.0);
				else if (p->info.fsize < 1000000000)
					printf("[%.1fG]", p->info.fsize / 1000000000.0);
			}
		}
		else
		{
			// printf("[");
			// for(i = 0; i < LENGTH_OF_LONG_INT-dig_count; i++)
			//	printf(" ");
			if (!access(p->fname, X_OK) || !strcmp(p->fname, "a.out"))
			{
				yellow();
				printf("%s  ", p->fname);
				reset();
			}
			else
				printf("%s  ", p->fname);

			if (p->info.fsize < 1000)
				printf("[%lu]  ", p->info.fsize);
			else if (p->info.fsize < 1000000)
				printf("[%.1fK]  ", p->info.fsize / 1000.0);
			else if (p->info.fsize < 1000000)
				printf("[%.1fM]  ", p->info.fsize / 1000000.0);
			else if (p->info.fsize < 1000000000)
				printf("[%.1fG]  ", p->info.fsize / 1000000000.0);
		}

		if (p->isdir)
		{
			if (p->isrootNode)
				printTree_h(p->inner_ptr);
			else
			{
				dir_count++;
				count++;
				printTree_h(p->inner_ptr);
				count--;
			}
		}
		if (!p->isdir)
			file_count++;
	}

	printTree_h(p->next_ptr);

	return;
}

// when -u flag is used (to print files along with their username)
void printTree_u(tnode t)
{
	node *p = t;
	int i;
	char *front = "|----", *down = "|    ";
	// char *last = "'----";
	if (!p)
		return;

	if (p->isrootNode || p->fname[0] != '.')
	{
		printf("\n");
		for (i = 0; i < count; i++)
		{
			printf("%s", down);
		}

		if (count >= 0 && !p->isrootNode)
		{
			// if(p->next_ptr)
			printf("%s", front);
			// else
			//	printf("%s", last);
		}

		// print directory name with green colour and file name with normal(default) colour
		if (p->isdir)
		{
			green();
			printf("%s  ", p->fname);
			reset();
			if (!p->isrootNode)
				printf("[%s ]", p->info.fuser_name);
		}
		else
		{
			if (!access(p->fname, X_OK) || !strcmp(p->fname, "a.out"))
			{
				yellow();
				printf("%s  ", p->fname);
				reset();
			}
			else
				printf("%s  ", p->fname);
			printf("[%s ]", p->info.fuser_name);
		}

		if (p->isdir)
		{
			if (p->isrootNode)
				printTree_u(p->inner_ptr);
			else
			{
				dir_count++;
				count++;
				printTree_u(p->inner_ptr);
				count--;
			}
		}
		if (!p->isdir)
			file_count++;
	}

	printTree_u(p->next_ptr);

	return;
}

void printTree_all(tnode t)
{
	node *p = t;
	int i;
	char *front = "|----", *down = "|    ";
	// char *last = "'----";
	if (!p)
		return;

	if (p->isrootNode || p->fname[0] != '.')
	{
		printf("\n");
		for (i = 0; i < count; i++)
		{
			printf("%s", down);
		}

		if (count >= 0 && !p->isrootNode)
		{
			// if(p->next_ptr)
			printf("%s", front);
			// else
			//	printf("%s", last);
		}

		// print directory name with green colour and file name with normal(default) colour
		if (p->isdir)
		{
			green();
			printf("%s", p->fname);
			reset();
			if (!p->isrootNode)
			{
				// displaying directory details
				printf("   %s", p->info.fuser_name);
				printf("   %lu bytes", p->info.fsize);
				printf("   %s ]", p->info.fpath);
			}
		}
		else
		{
			if (!access(p->fname, X_OK) || !strcmp(p->fname, "a.out"))
			{
				yellow();
				printf("%s", p->fname);
				reset();
			}
			else
				printf("%s", p->fname);

			// displaying file details
			printf("   %s", p->info.fuser_name);
			printf("   %lu bytes", p->info.fsize);
			printf("   %s ]", p->info.fpath);
		}

		if (p->isdir)
		{
			if (p->isrootNode)
				printTree_all(p->inner_ptr);
			else
			{
				dir_count++; // incrementing directory count
				count++;
				printTree_all(p->inner_ptr);
				count--;
			}
		}
		if (!p->isdir)
			file_count++; // incrementing file count
	}

	printTree_all(p->next_ptr);

	return;
}
