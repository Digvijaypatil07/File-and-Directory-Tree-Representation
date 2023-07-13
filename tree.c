#include "tree.h"

// when 1 command line argument is used
void tree_arg1(char *rootname)
{
	tnode p = NULL;

	// creating tree structure and sorting alphabetically
	p = createTree(rootname);
	printTree(p);
	printf("\n");

	printf("\n%d directories, %d files\n", dir_count, file_count);
}

// when 2 command line arguments are used
void tree_arg2(char *rootname, char *flag)
{

	// creating tree structure and sorting alphabetically
	tnode p = createTree(rootname);

	// comparing command line argument with different flags
	if (!strcmp(flag, "-a"))
	{
		printTree_a(p);
		printf("\n");

		printf("\n%d directories, %d files\n", dir_count, file_count);
	}
	else if (!strcmp(flag, "-d"))
	{
		printTree_d(p);
		printf("\n");

		printf("\n%d directories\n", dir_count);
	}
	else if (!strcmp(flag, "-s"))
	{
		printTree_s(p);
		printf("\n");

		printf("\n%d directories, %d files\n", dir_count, file_count);
	}
	else if (!strcmp(flag, "-f"))
	{
		printTree_f(p);
		printf("\n");

		printf("\n%d directories, %d files\n", dir_count, file_count);
	}
	else if (!strcmp(flag, "-Q"))
	{
		printTree_Q(p);
		printf("\n");

		printf("\n%d directories, %d files\n", dir_count, file_count);
	}
	else if (!strcmp(flag, "-h"))
	{
		printTree_h(p);
		printf("\n");

		printf("\n%d directories, %d files\n", dir_count, file_count);
	}
	else if (!strcmp(flag, "-all"))
	{
		printTree_all(p);
		printf("\n");

		printf("\n%d directories, %d files\n", dir_count, file_count);
	}
	else if (!strcmp(flag, "-u"))
	{
		printTree_u(p);
		printf("\n");

		printf("\n%d directories, %d files\n", dir_count, file_count);
	}

	else
	{
		printf("\nEnter valid flag\n");
	}
}

void tree_arg3(char *rootname, char *arg1, char *arg2)
{
	if (!strcmp(arg1, "-L"))
	{
		tnode p = createTree(rootname);

		// checking level exceeded or not
		if (atoi(arg2) > 0)
		{
			printTree_L(p, atoi(arg2));
			printf("\n");

			printf("\n%d directories, %d files\n", dir_count, file_count);
		}
		else
		{
			printf("Level must be greater than 0\n");
		}
	}
}
