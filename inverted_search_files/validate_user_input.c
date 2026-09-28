#include "invertedSearch.h"

int process_input_files(valid_file_list **head1, int argc, char *argv[])
{
    int count = 0;
    for (int i = 1; i < argc; i++)
    {
        /* extenstion should be .txt */
        char *ext = strrchr(argv[i], '.');
        if (!ext || strcmp(ext, ".txt") != 0)
            continue;

        /* File should be exist in directory */
        if (is_exist_or_empty(argv[i]) == FAILURE)
            continue;

        /* Check file should not be duplicate */
        if (is_duplicate(head1, argv[i]) == FAILURE)
            continue;

        if (create_file_list(head1, argv[i]) == FAILURE)
        {
            printf("Creating file list failed!\n");
            return FAILURE;
        }
        count++;
    }
    if (count == 0)
    {
        printf("All input file are invalid!\nNo file list is created!\n");
        g_list_flag = 1;
    }
    return SUCCESS;
}

/*******************************************************************************************************************************************************************
 * Function Name : is_exist_or_empty
 * Description   : Checks whether the given file exists and
 *                 verifies that it is not empty.
 * Input         : file_name – name of the file to be checked
 * Return        : SUCCESS – if file exists and is not empty
 *                 FAILURE – if file does not exist or is empty
 *******************************************************************************************************************************************************************/
int is_exist_or_empty(char *file_name)
{
    /* Check file is exist or not */
    FILE *fptr = fopen(file_name, "r");
    if (!fptr)
    {
        perror("fopen: ");
        return FAILURE;
    }
    /* Check file is empty or not */
    fseek(fptr, 0, SEEK_END);
    if (ftell(fptr) == 0)
    {
        printf("File is empty!\n");
        return FAILURE;
    }
    rewind(fptr);
    fclose(fptr);
    return SUCCESS;
}

/*******************************************************************************************************************************************************************
 * Title            : Check Duplicate File
 * Description      : This function checks whether the given file name is already present in the valid file list.
 *                    It traverses the linked list and compares the stored file names with the given file name
 *                    using string comparison. If a duplicate is found, it returns FAILURE, otherwise SUCCESS.
 * Prototype        : int is_duplicate(valid_file_list ***head2, char *file_name);
 *
 * Input Parameters : head2     : Triple pointer to the head of the valid file linked list.
 *                    file_name: Name of the file to be checked for duplication.
 *
 * Output           : Status (SUCCESS if file is not duplicate / FAILURE if duplicate file found)
 *******************************************************************************************************************************************************************/
int is_duplicate(valid_file_list **head2, char *file_name)
{
    if (*head2 == NULL) /* If it is NULL then no node is there */
        return SUCCESS;

    valid_file_list *temp = *head2;
    while (temp != NULL)
    {
        if (!strcmp(temp->files, file_name))
            return FAILURE;

        temp = temp->link;
    }
    return SUCCESS;
}

/***************************************************************************************************
 * Title       : Create File List
 * Description : This function creates a new node with the given file name and appends it
 *               to the end of the valid file linked list. If the list is empty, the new node
 *               becomes the head of the list.
 * Prototype   : int create_file_list(valid_file_list **head, char *file_name);
 * Input       : head      : Double pointer to the head of the valid file linked list.
 *               file_name: Name of the file to be added to the list.
 * Output      : Status (SUCCESS on successful insertion / FAILURE on memory allocation failure)
 ***************************************************************************************************/
int create_file_list(valid_file_list **head, char *file_name)
{
    valid_file_list *new = malloc(sizeof(valid_file_list));
    if (!new)
    {
        perror("Allocation : \n");
        return FAILURE;
    }

    strcpy(new->files, file_name);
    new->link = NULL;
    /* Check if list is empty */
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }
    /* Check if list is not empty */
    valid_file_list *temp = *head;
    while (temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}