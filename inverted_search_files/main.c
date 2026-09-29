
#include "invertedSearch.h"

/* Used to check wether valid file list is created or not.*/
int g_list_flag = 0;

int main(int argc, char *argv[])
{
	/* Define the main function here */
	main_node main_list;
	sub_node sub_list;

	valid_file_list file_list;
	valid_file_list *head = NULL;

	/* Create hash table */
	hash_t hash_arr[SIZE];
	create_hashtable(hash_arr);

	/* Validate CLA */
	if (process_input_files(&head, argc, argv) == FAILURE)
	{
		printf("User inputs validation failed!\n");
		return -1;
	}

	int db_created = 0, db_updated = 0;
	while (1)
	{
		/* Main menu */
		int choice;
		printf("1. Create Database\n2. Search Database\n3. Display Database\n4. Update Database\n5. Save Database\n6. Print Valid File List\n7.Exit\n");
		printf("Enter your choice : ");
		if (scanf("%d", &choice) != 1) /* If user enters non-numeric input, program may go into infinte loop. */
		{
			printf("Invalid input.\n");
			while (getchar() != '\n')
				; /* Clear buffer */
			continue;
		}

		switch (choice)
		{
		case 1: /* Create Database */
			if (g_list_flag)/* Check valid file are available or not to create database.*/
			{
				printf("The file list is not available, Cannot create database.\n");
				break;
			}
			if (db_created)/* Check database is already created or not.*/
			{
				printf("Database already created, Cannot create again\n");
				break;
			}
			if (create_db(&head, hash_arr) == FAILURE)
				printf("Create database function failed!\n");
			else
			{
				printf("Create database successfully.\n");
				db_created = 1;
			}
			break;
		case 2: /* Search Database */
			if (!(db_created || db_updated))
			{
				printf("Create database first!\n");
				break;

                
			}
			if (search_db(hash_arr) == FAILURE)
				printf("Search database function failed!\n");
			else
				printf("Search database successfully.\n");
			break;
		case 3: /* Display Database */
			if (!(db_created || db_updated))
			{
				printf("Create database first!\n");
				break;
			}
			if (display_db(hash_arr) == FAILURE)
				printf("Display database function failed!\n");
			else
				printf("Database displed successfully.\n");
			break;
		case 4: /* Update Database */
			if (update_db(hash_arr) == FAILURE)
				printf("Update database function failed!\n");
			else
			{
				printf("Update database successfully.\n");
				db_updated = 1;
			}
			break;
		case 5: /* Save Database */
			if (!(db_created || db_updated))
			{
				printf("Create database first!\n");
				break;
			}
			if (save_db(hash_arr) == FAILURE)
				printf("Save database function failed!\n");
			else
				printf("Save database successfully.\n");
			break;
		case 6: /* Print valid file list.*/
			if (valid_files_list(head) == FAILURE)
				printf("Print valid file list function failed!\n");
			else
				printf("Prints valid file list successfully.\n");
			break;
		case 7: /* Exit program */
			printf("Exiting program\n");
			exit(0);

		default:
			printf("Invalid choice! Try again\n");
		}
	}
	return 0;
}
