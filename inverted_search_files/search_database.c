#include "invertedSearch.h"

/***************************************************************************************************
 * Title       : Search Database
 * Description : This function searches for a given word in the inverted index
 *               database. It takes a word from the user, converts it to lower
 *               case, finds the corresponding hash index, and checks whether
 *               the word exists in the database. If the word is found, the
 *               related index, file names, and word counts are displayed.
 *               If the word is not present, a message is shown to the user.
 * Prototype   : int search_db(hash_t *hash_arr);
 * Input       : hash_arr : Pointer to the hash table.
 * Output      : Displays the search result on the screen.
 * Return      : SUCCESS if the word is found,
 *               FAILURE if the word is not found or an error occurs.
 ***************************************************************************************************/
int search_db(hash_t *hash_arr)
{
    /* Check if hash_arr is valid.*/
    if (hash_arr == NULL)
        return FAILURE;

    /* Read word from user. */
    printf("Enter the word to search : ");
    char word[30];
    scanf("%29s", word);

    /* Convert word to lower case.*/
    if (normlize_word(word) == FAILURE)
        return FAILURE;

    int Index = hash_index_function(word);
    /* Check index is valid or not.*/
    if (Index < 0 || Index >= SIZE)
        return FAILURE;

    /* Check the index link is NULL or not.*/
    if (hash_arr[Index].main_link == NULL)
    {
        printf("The %s is not found.\n", word);
        return FAILURE;
    }
    /* Traverse through the main node(upto NULL).*/
    main_node *main_temp = hash_arr[Index].main_link;
    while (main_temp != NULL)
    {
        /* Check the word is matching or not.*/
        if (strcmp(word, main_temp->word) == 0)
        {
            printf("%-7s %-20s %-12s %-20s %-12s\n",
                   "Index", "Word", "File_Count", "File_Name", "Word_Count");
            printf("-------------------------------------------------------------------------\n");
            printf("%-7d %-20s %-12d ",
                   Index, main_temp->word, main_temp->file_count);

            sub_node *sub_temp = main_temp->sub_link;
            while (sub_temp)
            {
                printf("%-20s %-12d\n", sub_temp->file_name, sub_temp->word_count);
                sub_temp = sub_temp->next;

                if (sub_temp)
                    printf("%-42s", " ");
            }
            printf("-------------------------------------------------------------------------\n");
            return SUCCESS;
        }
        main_temp = main_temp->next_link;
    }

    printf("The %s is not found.\n", word);
    return FAILURE;
}