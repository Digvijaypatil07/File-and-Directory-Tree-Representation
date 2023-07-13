#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>

#define LENGTH_OF_LONG_INT 10

extern int count;
extern int file_count;
extern int dir_count;

// struct ADT
typedef struct node
{
    char *fname;
    int isdir;
    int isrootNode;

    struct information
    {
        unsigned long int fsize;
        char *fpath;
        char *fuser_name;
    } info;

    struct node *next_ptr;
    struct node *inner_ptr;
} node;

typedef node *tnode;

// creating tree functions
node *createTreeNode(char *name);
node *createTree_1(char *rootname);
node *createTree(char *rootname);


// file details related functions
unsigned long int get_Size(char *file_name);
long int get_fileSize(char *file_path);
char *get_username(char *file_name);

// printing tree functions for various flags
void printTree(tnode t);
void printTree_a(tnode t);
void printTree_d(tnode t);
void printTree_s(tnode t);
void printTree_f(tnode t);
void printTree_Q(tnode t);
void printTree_L(tnode t, int level);
void printTree_h(tnode t);
void printTree_u(tnode t);
void printTree_all(tnode t);

// declarations for different ANSI colours
void black();
void red();
void green();
void yellow();

void blue();
void purple();
void cyan();
void white();

void reset();

// function for --help flag
void help(char *file_name);

// functions according to number command line arguments
void tree_arg1(char *rootname);
void tree_arg2(char *rootname, char *flag);
void tree_arg3(char *rootname, char *arg1, char *arg2);
