#include "invertedSearch.h"

/***************************************************************************************************
 * Title       : Save Database
 * Description : This function saves the entire inverted index database into a text file. 
 *               It prompts the user to enter a file name, validates that it has a ".txt" extension, 
 *               and then writes the database contents in a structured format. 
 *               The hash table is traversed, and for each main word, its associated file names 
 *               and word counts are stored. Each main word block is separated by "#".
 * Prototype   : int save_db(hash_t *hash_arr);
 * Input       : hash_arr : Pointer to the hash table array.
 * Output      : Creates/overwrites a text file containing the database information.
 * Return      : SUCCESS on successful save,
 *               FAILURE if an error occurs (e.g., invalid pointer, invalid file name, or file open failure).
 ***************************************************************************************************/
int save_db(hash_t *hash_arr)
{
    /* Check if hash_arr is valid or not.*/
    if (hash_arr == NULL)
        return FAILURE;

    /* Read file name from user.*/
    char file_name[20];
    printf("Enter the file name to save database : ");
    scanf("%19s", file_name);

    /* Validate file extenstion.*/
    char *ext = strrchr(file_name, '.');
    if (!ext || strcmp(ext, ".txt") != 0)
    {
        printf("Please enter valid file name.\n");
        return FAILURE;
    }
    /* Open file in write mode.*/
    FILE *fptr = fopen(file_name, "w");
    if(!fptr)
    {
        perror("fopen : ");
        return FAILURE;
    }

    /* Traverse hash index.*/
    for (int i = 0; i < SIZE; i++)
    {
        if (hash_arr[i].main_link == NULL)
            continue;
        /* Traverse main node upto NULL.*/
        main_node *main_temp = hash_arr[i].main_link;
        while (main_temp != NULL)
        {
            fprintf(fptr, "#%d;%s;%d;", i, main_temp->word, main_temp->file_count);
            
            /* Traverse sub node uptp NULL.*/
            sub_node *sub_temp = main_temp->sub_link;
            while (sub_temp != NULL)
            {
                fprintf(fptr, "%s;%d;", sub_temp->file_name, sub_temp->word_count);
                sub_temp = sub_temp->next;
            }
            fprintf(fptr, "#\n");
            main_temp = main_temp->next_link;
        }
    }
    fclose(fptr);
    return SUCCESS;
}