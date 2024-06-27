//.C FILE (REVISED)

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



#include "RevFP_06.h" //include from header file

//main function
int main(void) {
    job_application *head = load_application("applications.csv");
    int pilihan;
    char nama_pekerjaan[100], nama_perusahaan[100], tanggal_lamaran[15], status[50];

    while (1) {
        printf("\n=====================================\n");
        printf("Welcome to the JobSeeker's Companion\n");
        printf("=====================================\n");
        printf("1. Add new job application\n");
        printf("2. Show all applications\n");
        printf("3. Edit status application\n");
        printf("4. Saving file\n");
        printf("5. Help\n");
        printf("6. Delete all applications\n");
        printf("7. Exit program\n");
        printf("\nplease keep in mind that after deleting all file, press save\n");
        printf("first before exiting for the data to be permenantly deleted\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &pilihan);
        getchar(); //consume newline

        switch (pilihan) {
            case 1: //to add new application
                printf("Enter job title: ");
                scanf(" %[^\n]", nama_pekerjaan);
                printf("Enter company name: ");
                scanf(" %[^\n]", nama_perusahaan);
                printf("Enter application date (DD/MM/YYYY): ");
                scanf(" %[^\n]", tanggal_lamaran);
                printf("Enter status: ");
                scanf(" %[^\n]", status);
                job_application *new = create_application(nama_pekerjaan, nama_perusahaan, tanggal_lamaran, status);
                head = append_application(head, new);
                break;
            case 2: //calling show application function
                show_application(head);
                break;
            case 3: //calling edit status function
                edit_status(head);
                break;
            case 4: //save file
                save_application(head, "applications.csv");
    			printf("Application saved.");
    			break;
            case 5: //showing help
                display_help();
                break;
            case 6: //calling delete application function
                delete_all_application(&head);
                break;
            case 7:
            	printf ("Exiting...\n");
            	return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
