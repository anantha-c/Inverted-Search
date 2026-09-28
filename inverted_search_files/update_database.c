#include "invertedSearch.h"

int update_db(hash_t *hash_arr)
{
    /* Check if hash_arr is valid or not.*/
    if (hash_arr == NULL)
        return FAILURE;

    /* Read file name from user.*/
    char file_name[128];
    printf("Enter the file name which data you want to update : ");
    scanf("%19s", file_name);
    /* Validate file extenstion.*/
    char *ext = strrchr(file_name, '.');
    if (!ext || strcmp(ext, ".txt") != 0)
    {
        printf("Please enter valid file name.\n");
        return FAILURE;
    }

    /* Check given file is database file or not.*/
    FILE *fptr = fopen(file_name, "r");
    if (!fptr)
    {
        perror("fopen : ");
        return FAILURE;
    }

    char line[256];
    fgets(line, sizeof(line), fptr);
    /* Check is it valid database file or not, By checking '#' on start and end of line.*/
    int len = strlen(line);
    if (len <= 1)
        return FAILURE;
    if (line[0] != '#' || line[len - 2] != '#')
    {
        printf("Not a valid database file, Cannot proceed further.\n");
        return FAILURE;
    }

    /* Get back file pointer to start.*/
    rewind(fptr);

    /* Read file data line by line.*/
    while (fgets(line, sizeof(line), fptr))
    {
        /* Extract index.*/
        char *token = strtok(line, "#;");
        if (!token)
            continue;
        int index = atoi(token);

        /* Extract word.*/
        token = strtok(NULL, ";");
        if (!token)
            continue;
        char *word = token;

        /* Extract file count.*/
        token = strtok(NULL, ";");
        if (!token)
            continue;
        int file_count = atoi(token);

        main_node *main_temp = hash_arr[index].main_link;
        /* Search word in hash table.*/
        main_node *main_prev = NULL;

        while (main_temp)
        {
            if (strcmp(main_temp->word, word) == 0)
                break;
            main_prev = main_temp;
            main_temp = main_temp->next_link;
        }

        /* WORD NOT FOUND -> Create new main node.*/
        if (main_temp == NULL)
        {
            main_node *main_new = malloc(sizeof(main_node));
            if (!main_new)
            {
                perror("main_node : ");
                return FAILURE;
            }
            strcpy(main_new->word, word);
            main_new->file_count = file_count;
            main_new->sub_link = NULL;
            main_new->next_link = NULL;

            sub_node *sub_prev = NULL;

            for (int i = 0; i < file_count; i++)
            {
                /* Extract file name.*/
                token = strtok(NULL, ";");
                if (!token)
                    continue;
                char *file_name = token;

                /* Extract word count.*/
                token = strtok(NULL, ";");
                if (!token)
                    continue;
                int word_count = atoi(token);

                sub_node *sub_new = malloc(sizeof(sub_node));
                if (!sub_new)
                {
                    printf("sub_node : ");
                    return FAILURE;
                }
                strcpy(sub_new->file_name, file_name);
                sub_new->word_count = word_count;
                sub_new->next = NULL;

                if (main_new->sub_link == NULL)
                    main_new->sub_link = sub_new;
                else
                    sub_prev->next = sub_new;

                sub_prev = sub_new;
            }

            if (hash_arr[index].main_link == NULL)
                hash_arr[index].main_link = main_new;
            else
                main_prev->next_link = main_new;
        }
        /* WORD FOUND -> Merge sub nodes.*/
        else
        {
            for (int i = 0; i < file_count; i++)
            {
                /* Extract file name.*/
                token = strtok(NULL, ";");
                if (!token)
                    continue;
                char *file_name = token;

                /* Extract word count.*/
                token = strtok(NULL, ";");
                if (!token)
                    continue;
                int word_count = atoi(token);

                sub_node *sub_temp = main_temp->sub_link;
                sub_node *sub_prev = NULL;

                while (sub_temp)
                {
                    if (strcmp(sub_temp->file_name, file_name) == 0)
                        break;
                    sub_prev = sub_temp;
                    sub_temp = sub_temp->next;
                }

                if (sub_temp) /* FILE EXISTS.*/
                {
                    sub_temp->word_count += word_count;
                }
                else /* FILE NOT EXISTS-> Create new sub node.*/
                {
                    sub_node *sub_new = malloc(sizeof(sub_node));
                    if (!sub_new)
                    {
                        printf("sub_node : ");
                        return FAILURE;
                    }
                    strcpy(sub_new->file_name, file_name);
                    sub_new->word_count = word_count;
                    sub_new->next = NULL;

                    if (main_temp->sub_link == NULL)
                        main_temp->sub_link = sub_new;
                    else
                        sub_prev->next = sub_new;
                    main_temp->file_count++;
                }
            }
        }
    }

    fclose(fptr);
    return SUCCESS;
}