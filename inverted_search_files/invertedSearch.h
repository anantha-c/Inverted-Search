#ifndef INVERTEDSEARCH_H
#define INVERTEDSEARCH_h

#include <stdio.h>
#include <string.h>
#include <errno.h>  /* It's needed to use perror() */
#include <stdlib.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1
#define SIZE 27

extern int g_list_flag;

/* Sub Node */
typedef struct sub_node
{
    int word_count;
    char file_name[50];
    struct sub_node *next;
}sub_node;

/* Main Node */
typedef struct main_node
{
    int file_count;
    char word[50];
    struct sub_node *sub_link;  /* Contain list node link */
    struct main_node *next_link;    /* Contain next hash nod e link which having same index */
}main_node;

/* Contain index of main nodes */
typedef struct hash_table
{
    int index;
    struct main_node *main_link;
}hash_t;

/* Contain valid files */
typedef struct valid_file_list
{
    char files[50];
    struct valid_file_list *link;
}valid_file_list;

/*------------------------------------------------------------------------------------------*/
/* Initializes the hash table by setting all index links to NULL. */
void create_hashtable(hash_t *hash_arr);

/* Traverses and prints all file names stored in the valid file linked list */
int valid_files_list(valid_file_list *head);

/*------------------------------------------------------------------------------------------*/
/* Processes command-line inputs, validates files, and builds the valid file linked list */
int process_input_files(valid_file_list  **head1, int argc, char *argv[]);
/* Checks whether the given file exists and is not empty */
int is_exist_or_empty(char *file_name);
/* Checks if the given file name already exists in the valid file linked list */
int is_duplicate(valid_file_list **head2, char *file_name);
/* Creates a new node with the file name and appends it to the valid file linked list */
int create_file_list(valid_file_list **head, char *file_name);

/*------------------------------------------------------------------------------------------*/
/* Converts all characters of the word to lowercase for consistent storage/search. */
int normlize_word(char *word);
/* Generates the hash index for storing or searching a word in the table. */
int hash_index_function(char *word);

/*------------------------------------------------------------------------------------------*/
/* Creates the inverted index database using the list of valid input files. */
int create_db(valid_file_list **head, hash_t *hash_arr);
/* Stores a word and its file information into the hash table. */
int store_word(char *word, char *file_name, hash_t *hash_arr);

/*------------------------------------------------------------------------------------------*/
/* Searches for a word in the database and displays its details if found. */
int search_db(hash_t *hash_arr);

/*------------------------------------------------------------------------------------------*/
/* Displays the contents of the hash table in a readable table format. */
int display_db(hash_t *hash_arr);

/*------------------------------------------------------------------------------------------*/
/* Saves the contents of the hash table database to an output file. */
int save_db(hash_t *hash_arr);

/*------------------------------------------------------------------------------------------*/
int update_db(hash_t *hash_arr);
#endif