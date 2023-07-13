#include "tree.h"

int count;
int file_count;
int dir_count;

// This functions initializes the information about a file/directory
node *createTreeNode(char *name)
{
    node *nn = (node *)malloc(sizeof(node));
    nn->fname = name;
    nn->isdir = 1;
    nn->isrootNode = 0;

    nn->info.fsize = 0;

    nn->info.fpath = (char *)calloc(1000, sizeof(char));
    nn->info.fuser_name = (char *)calloc(30, sizeof(char));

    // self referencial pointers
    nn->inner_ptr = NULL;
    nn->next_ptr = NULL;

    return nn;
}

node *createTree(char *rootname)
{
    DIR *dir = opendir(rootname);
    // if it fails to open root directory then return
    if (!dir)
    {
        printf("Failed to open %s ...", rootname);
        return NULL;
    }
    closedir(dir);

    node *rootNode = createTreeNode(rootname);
    rootNode->isrootNode = 1;
    rootNode->inner_ptr = createTree_1(rootname);
    rootNode->info.fpath = ".";
    return rootNode;
}

node *createTree_1(char *rootname)
{
    node *p = NULL, *q = NULL;
    node *t_start = NULL;

    char name[1000];
    struct dirent *dr = NULL;

    // opening a directory
    DIR *dir = opendir(rootname);
    if (!dir)
    {
        printf("Failed to open %s...\n", rootname);
        return NULL;
    }

    // traversing until end of directory stream
    while ((dr = readdir(dir)) != NULL)
    {

        // Not to consider sub-directories "." and ".."
        if (strcmp((dr->d_name), ".") != 0 && strcmp((dr->d_name), "..") != 0)
            p = createTreeNode(dr->d_name);
        else
        {
            p = NULL;
            continue;
        }

        // t_start will point to first node in root directory
        if (!q)
            t_start = p;
        else
            q->next_ptr = p;

        // if current stream is directory
        if ((dr->d_type) == DT_DIR)
        {
            p->isdir = 1;
            strcpy(name, rootname);

            p->inner_ptr = createTree_1(strcat((strcat(name, "/")), dr->d_name));
            p->info.fsize = get_Size(name);

            // printf("%s\n", name);
            strcpy(p->info.fpath, name);
            strcpy(p->info.fuser_name, get_username(name));
            strcpy(name, rootname);

        } // else current stream is not directory
        else
        {
            p->isdir = 0;
            p->inner_ptr = NULL;

            strcpy(name, rootname);
            strcat((strcat(name, "/")), dr->d_name);
            p->info.fsize = get_Size(name);

            // printf("%s\n", name);

            strcpy(p->info.fpath, name);
            strcpy(p->info.fuser_name, get_username(name));
            strcpy(name, "");
        }

        q = p;
    }

    // returning start node of tree structure
    return t_start;
}

// get the size of directory using stat()
unsigned long int get_Size(char *file_name)
{
    struct stat st; // declare stat variable

    if (stat(file_name, &st) == 0)
        return st.st_size;
    else
        return 0;
}

// get the size of file using fseek() and ftell()
long int get_fileSize(char *file_path)
{
    FILE *fp = fopen(file_path, "r");
    if (!fp)
    {
        return -1;
    }
    long int size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fclose(fp);
    return size;
}

// To get the username of file
char *get_username(char *file_name)
{
    struct stat st;
    stat(file_name, &st);
    struct passwd *pwuser;
    pwuser = getpwuid(st.st_uid);
    return pwuser->pw_name;
}

// when --help flag is used
void help(char *file_name)
{
    FILE *fp = fopen(file_name, "r");
    if (!fp)
    {
        return;
    }

    char c = fgetc(fp);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(fp);
    }
    return;
}
