#include "invertedSearch.h"

/***************************************************************************************************
 * Title       : Create Database from Files
 * Description : This function traverses the linked list of valid files, opens each file,
 *               reads it line by line, tokenizes each line into words, and stores each word
 *               in the hash table along with the file reference. If a file cannot be opened,
 *               it is skipped. The database (hash table) is populated with words and their
 *               corresponding file occurrences.
 * Prototype   : int create_db(valid_file_list **head, hash_t *hash_arr);
 * Input       : head     : Double pointer to the head of the valid file linked list.
 *               hash_arr : Pointer to the hash table to store words and file occurrences.
 * Output      : Status (SUCCESS on successful database creation / FAILURE on any error)
 ***************************************************************************************************/
int create_db(valid_file_list **head, hash_t *hash_arr)
{
    if (*head == NULL)
    {
        printf("File list is empty.\n");
        return FAILURE;
    }

    valid_file_list *temp = *head;
    while (temp != NULL)
    {
        FILE *fptr = fopen(temp->files, "r");
        if (!fptr)
        {
            temp = temp->link;
            perror("fopen : ");
            continue; /* skip current file */
        }

        char line[1024];
        char *word;
        while (fgets(line, sizeof(line), fptr))
        {
            word = strtok(line, " \t\n.,;:!?\"'()[]{}<>-_/\\");
            while (word)
            {
                if (store_word(word, temp->files, hash_arr) == FAILURE)
                {
                    printf("Word storing failed\n");
                    fclose(fptr);
                    return FAILURE;
                }
                word = strtok(NULL, " \t\n.,;:!?\"'()[]{}<>-_/\\");
            }
        }

        fclose(fptr);
        temp = temp->link;
    }
    return SUCCESS;
}

/***************************************************************************************************
 * Title       : Store Word in Hash Table
 * Description : This function converts the given word to lowercase, computes its hash index,
 *               searches for the word in the hash table, and inserts it if not present.
 *               Each word maintains a list of files (sub-nodes) where it appears, along with
 *               the count of occurrences in each file. If the word already exists, the function
 *               updates the appropriate sub-node count or adds a new sub-node for a new file.
 * Prototype   : int store_word(char *word, char *file_name, hash_t *hash_arr);
 * Input       : word     : The word to be stored (converted to lowercase internally)
 *               file_name: Name of the file where the word was found
 *               hash_arr : Pointer to the hash table
 * Output      : Status (SUCCESS on successful insertion/update / FAILURE on memory allocation failure)
 ***************************************************************************************************/
int store_word(char *word, char *file_name, hash_t *hash_arr)
{
    /* Non-fatal cases: just skip (Returning SUCCESS to avoid file closing to proceed operation for further words.)*/
    if (word == NULL || word[0] == '\0')
        return SUCCESS;
    if (!isalpha((unsigned char)word[0]))
        return SUCCESS;

    /* Converting word to lower case. */
    if (normlize_word(word) == FAILURE)
        return FAILURE;

    int Index = hash_index_function(word);
    /* Check index is valid or not.*/
    if (Index < 0 || Index >= SIZE)
        return FAILURE;

    main_node *temp = hash_arr[Index].main_link;
    /* Search word in main list */
    while (temp != NULL)
    {
        if (strcmp(temp->word, word) == 0)
            break;
        temp = temp->next_link;
    }

    if (temp == NULL)
    {
        /* Create new main node */
        main_node *new_main = malloc(sizeof(main_node));
        if (!new_main)
            return FAILURE;
        new_main->file_count = 1;
        strcpy(new_main->word, word);

        /* Create new sub node */
        sub_node *new_sub = malloc(sizeof(sub_node));
        if (!new_sub)
        {
            free(new_main);
            return FAILURE;
        }
        new_sub->word_count = 1;
        strcpy(new_sub->file_name, file_name);
        new_sub->next = NULL;

        new_main->sub_link = new_sub;

        new_main->next_link = hash_arr[Index].main_link;
        hash_arr[Index].main_link = new_main;
    }
    else
    {
        /* Word exists -> check file list */
        sub_node *cur = temp->sub_link;
        sub_node *prev = NULL;

        while (cur != NULL)
        {
            if (strcmp(cur->file_name, file_name) == 0)
                break;
            prev = cur;
            cur = cur->next;
        }

        if (cur == NULL)
        {
            /* New file entry */
            sub_node *new_sub = malloc(sizeof(sub_node));
            if (!new_sub)
                return FAILURE;
            new_sub->word_count = 1;
            strcpy(new_sub->file_name, file_name);
            new_sub->next = NULL;

            if (prev == NULL)
                temp->sub_link = new_sub;
            else
                prev->next = new_sub;

            temp->file_count++;
        }
        else
        {
            cur->word_count++;
        }
    }
    return SUCCESS;
}

/***************************************************************************************************
 * Title       : Compute Hash Index
 * Description : This function computes the hash index for a given word based on its first letter.
 *               If the first character is a lowercase letter 'a'-'z', the index is 0-25.
 *               All other characters (digits, symbols, uppercase if not converted) are mapped
 *               to index 26. This ensures a total of 27 buckets in the hash table.
 * Prototype   : int hash_index_function(char *word);
 * Input       : word : The word for which the hash index is to be computed.
 * Output      : Returns the hash table index (0-26) corresponding to the first character.
 ***************************************************************************************************/
int hash_index_function(char *word)
{
    if (word[0] >= 'a' && word[0] <= 'z')
        return word[0] - 'a';
    else
        return 26;
}

/***************************************************************************************************
 * Title       : Normalize Word
 * Description : This function converts all characters of the given word
 *               to lowercase. It modifies the input string in place and
 *               ensures safe handling by validating the input pointer.
 * Prototype   : int normlize_word(char *word);
 * Input       : word : Pointer to the string that needs to be normalized.
 * Output      : The input string is converted to lowercase.
 * Return      : SUCCESS if normalization is completed successfully,
 *               FAILURE if the input pointer is NULL.
 ***************************************************************************************************/
int normlize_word(char *word)
{
    char *ptr = word;

    while (*ptr)
    {
        *ptr = tolower((unsigned char)*ptr);
        ptr++;
    }
    return SUCCESS;
}