#include "invertedSearch.h"

/***************************************************************************************************
 * Title       : Print File List
 * Description : This function traverses the valid file linked list and prints each file name
 *               in sequence. If the list is empty, it displays an appropriate message.
 *
 * Prototype   : void print_list(valid_file_list *head);
 *
 * Input       : head : Pointer to the head of the valid file linked list.
 *
 * Output      : Prints the file names in the list followed by NULL.
 ***************************************************************************************************/
int valid_files_list(valid_file_list *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
	    while (head)		
	    {
		    printf("%s -> ", head -> files);
		    head = head -> link;
	    }

	    printf("NULL\n");
    }
	return SUCCESS;
}

/***************************************************************************************************
 * Title       : Initialize Hash Table
 * Description : This function initializes all hash table buckets by assigning index values
 *               and setting the main linked list pointers to NULL.
 * Prototype   : void init_hashtable(hash_t *hash_arr);
 * Input       : hash_arr : Pointer to the hash table array.
 * Output      : Initializes the hash table buckets.
 ***************************************************************************************************/
void create_hashtable(hash_t *hash_arr)
{
    for (int i = 0; i < SIZE; i++)
    {
        hash_arr[i].index = i;
        hash_arr[i].main_link = NULL;
    }
}