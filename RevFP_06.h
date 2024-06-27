//HEADER FILE (REVISED)

//Final Project
//Group 6:
//Mirza Ananta Hermawan (2206822212)
//Darrel Khayru Risyad (2206820781)

//A job application tracker program which will help job seekers to manage their job applications
//Bismillah

//REVISIONS MADE:
//1. we have separated the save and exit option into different options
//2. the "delete all applications" option have been added a confirmation before the user deletes all
//3. we have added time.h library for real time access
//4. we have rearranged the main menu so that it is clearer and easier to use


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct job_application {//defining the structure
    char nama_pekerjaan[100];
    char nama_perusahaan[100];
    char tanggal_lamaran[15];
    char status[50];
    struct job_application *next_struct;
} job_application;

job_application* create_application(char *nama_pekerjaan, char *nama_perusahaan, char *tanggal_lamaran, char *status) {
    job_application *baru = (job_application*) malloc(sizeof(job_application));
    if (baru == NULL) {
        printf("error allocating memory\n");
        exit(1);
    }//to create a new job_application structure
    strcpy(baru->nama_pekerjaan, nama_pekerjaan);
    strcpy(baru->nama_perusahaan, nama_perusahaan);
    strcpy(baru->tanggal_lamaran, tanggal_lamaran);
    strcpy(baru->status, status);//copying the existing data to the new structure
    baru->next_struct = NULL;//setting the new pointer so it wouldn't be associated with the previous struture
    return baru;
}//overall, this part is to have a new structure to move in data so the previous structure can receive input again- part of linked list.

job_application* append_application(job_application *head, job_application *baru) {
    if (head == NULL) {
        return baru;
    }
    job_application *cursor = head;
    while (cursor->next_struct != NULL) {
        cursor = cursor->next_struct;
    }
    cursor->next_struct = baru;
    return head;
}//travesing the whole list to find the end of it to indentify if its empty or not.
//if empty, then that point (next_struct) will be appended to be the new head.

void save_application(job_application *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("error opening file!\n");
        return;
    }
    job_application *traverse1 = head;
    while (traverse1 != NULL) {
        fprintf(file, "%s,%s,%s,%s\n", traverse1->nama_pekerjaan, traverse1->nama_perusahaan, traverse1->tanggal_lamaran, traverse1->status);
        traverse1 = traverse1->next_struct;
    }
    fclose(file);
}//file handling (opening and closing the saved data)

job_application* load_application(const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[256];
    job_application *head = NULL;
    job_application *baru = NULL;
    char nama_pekerjaan[100], nama_perusahaan[100], tanggal_lamaran[15], status[50];

    if (file == NULL) {
        printf("error opening file!\n");
        return NULL;//says that there is no file to open/no file in regards to this program as it reads NULL
    }

    while (fscanf(file, "%99[^,],%99[^,],%14[^,],%49[^\n]\n", nama_pekerjaan, nama_perusahaan, tanggal_lamaran, status) != EOF) {
        baru = create_application(nama_pekerjaan, nama_perusahaan, tanggal_lamaran, status);
        head = append_application(head, baru);
    }//telling the code how the file want to be read before creating a structure to be appended with said data and pointing "head" to the start of the list
    fclose(file);
    return head;
}

void tolower_String(char *str) {
     int i = 0;
     for (i; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}//making the strings to be not case sensitive

int convert_date_to_integer(const char *tanggal_lamaran) {
    int day, month, year;
    sscanf(tanggal_lamaran, "%d/%d/%d", &day, &month, &year);
    return year * 10000 + month * 100 + day;
}//changing the date into numbers to be sorted

void bubble_sort_by_date(job_application **head) {
    int swapped;
    job_application *ptr1;
    job_application *ptr2 = NULL;

    if (*head == NULL) return;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next_struct != ptr2) {
            if (convert_date_to_integer(ptr1->tanggal_lamaran) > convert_date_to_integer(ptr1->next_struct->tanggal_lamaran)) {
                // Swap the data of the nodes
                //Swapping and comparison by dates as it compares the integer form pointed by ptr1 and next_struct. if it's bigger, then the swapping occurs
                char temp_nama_pekerjaan[100], temp_nama_perusahaan[100], temp_tanggal_lamaran[15], temp_status[50];
				//dummy/temporary variables
                strcpy(temp_nama_pekerjaan, ptr1->nama_pekerjaan);
                strcpy(temp_nama_perusahaan, ptr1->nama_perusahaan);
                strcpy(temp_tanggal_lamaran, ptr1->tanggal_lamaran);
                strcpy(temp_status, ptr1->status);//segment: copying ptr1 data to temporary variable

                strcpy(ptr1->nama_pekerjaan, ptr1->next_struct->nama_pekerjaan);
                strcpy(ptr1->nama_perusahaan, ptr1->next_struct->nama_perusahaan);
                strcpy(ptr1->tanggal_lamaran, ptr1->next_struct->tanggal_lamaran);
                strcpy(ptr1->status, ptr1->next_struct->status);//segment: copying next_struct data to ptr1

                strcpy(ptr1->next_struct->nama_pekerjaan, temp_nama_pekerjaan);
                strcpy(ptr1->next_struct->nama_perusahaan, temp_nama_perusahaan);
                strcpy(ptr1->next_struct->tanggal_lamaran, temp_tanggal_lamaran);
                strcpy(ptr1->next_struct->status, temp_status);//segment: copying temporary variable data to next_struct

                swapped = 1;//
            }
            ptr1 = ptr1->next_struct;
        }
        ptr2 = ptr1;
    } while (swapped);
}

void search_application(job_application *head, const char *keyword) {
    job_application *traverse2 = head;
    char searching[100];
    strcpy(searching, keyword);
    tolower_String(searching);
	//to display the result/data
    printf("\nSearch results:\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("|%-30s|%-20s|%-10s|%-30s|\n", "Job title", "Company name", "Date", "Status");
    printf("-----------------------------------------------------------------------------------------------\n");
	
    while (traverse2 != NULL) { //a pointer to go to each node of the list
        char pekerjaan_lower[100], perusahaan_lower[100];
        strcpy(pekerjaan_lower, traverse2->nama_pekerjaan);//copying the data in nama_pekerjaan to pekerjaan_lower
        strcpy(perusahaan_lower, traverse2->nama_perusahaan);//copying the data in nama_pekerjaan to pekerjaan_lower
        tolower_String(pekerjaan_lower);//turning the data to lower case
        tolower_String(perusahaan_lower);//turning the data to lower case

        if (strstr(pekerjaan_lower, searching) != NULL || strstr(perusahaan_lower, searching) != NULL) {
            printf("|%-30s|%-20s|%-10s|%-30s|\n", traverse2->nama_pekerjaan, traverse2->nama_perusahaan, traverse2->tanggal_lamaran, traverse2->status);
        }//if the data sent is not null, then it will print the result.
        traverse2 = traverse2->next_struct;
    }
    printf("-----------------------------------------------------------------------------------------------\n");
}

void print_application(job_application *head) {
    job_application *traverse1 = head;
    int index = 1;
    printf("\nCurrent job applications:\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-30s | %-20s | %-10s | %-30s |\n", "No", "Job title", "Company name", "Date", "Status");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    while (traverse1 != NULL) {
        printf("| %-3d | %-30s | %-20s | %-10s | %-30s |\n", index++, traverse1->nama_pekerjaan, traverse1->nama_perusahaan, traverse1->tanggal_lamaran, traverse1->status);
        traverse1 = traverse1->next_struct;
    }
    printf("-------------------------------------------------------------------------------------------------------------\n");
}//displaying the applications/tracker

void display_help(void) {
    printf("Help menu:\n");
    printf("1. Add new job application = add new job application\n");
    printf("2. Show all applications = display all recorded job applications\n");
    printf("3. Edit status application = edit the status of an existing job application\n");
    printf("4. Save = save all changes made\n");
    printf("5. Help = display this help menu\n");
    printf("6. Delete all applications = remove all job applications from the list\n");
    printf("7. Exit program = well... exit the program\n");
}//display the "help" part just in case someone need some explanation

void delete_all_application(job_application **head) {
    job_application *traverse1 = *head;//initialize traverse1 to the head
    job_application *next = NULL;
    int i;
    
	printf("confirm of deletion? if so, please press 1. If not, press any number (you will return to main menu):");
	scanf("%d", &i);
	
	switch (i){
		case 1:
			 while (traverse1 != NULL) {
        next = traverse1->next_struct;//next is set to point to to the next node
        free(traverse1);//freeing memomry
        traverse1 = next;
   	 		}
    		*head = NULL;
    		printf("All job applications have been deleted.\n");
    		break;
    	default:
    		break;
	}
   
}

void show_application(job_application *head) {//function whether to show or search data
    int choice;
    while (1) {
        printf("\n1. Sort by Date\n2. Search by Keyword\n3. Return\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1:
                bubble_sort_by_date(&head);
                print_application(head);
                break;
            case 2:
                printf("Enter search keyword (job title or company name): ");
                char keyword[100];
                scanf(" %[^\n]", keyword);
                search_application(head, keyword);
                break;
            case 3:
                return;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

void edit_status(job_application *head) {
    if (head == NULL) {
        printf("No job applications available to edit.\n");
        return;//if there's not data in the first place
    }

    print_application(head);

    int index, count = 1;
    job_application *traverse2 = head;//setting the traverse to the head of the list
    printf("Enter the number of the application you want to edit: ");
    scanf("%d", &index);
    getchar();  // consume newline

    while (traverse2 != NULL && count < index) {
        traverse2 = traverse2->next_struct;//setting traverse to point to next node
        count++;
    }

    if (traverse2 == NULL) {
        printf("Invalid application number.\n");
        return;
    }

    printf("Current status: %s\n", traverse2->status);
    printf("Enter new status: ");
    scanf(" %[^\n]", traverse2->status);//changing the status
    printf("Status updated successfully.\n");
}
