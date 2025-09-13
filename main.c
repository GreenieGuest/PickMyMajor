/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_MAJORS 19

struct major {
    int points;
    char name[50];
};
    
void initializeMajors(struct major majors[]);
int takeSurvey(struct major majors[]);
int calculateMajor(int hasTakenSurvey, struct major majors[]);
void displayPoints(int hasTakenSurvey, struct major majors[]);
void search(struct major majors[]);
void saveData(int id);
void displayData();
void question(char questionTitle[], int optionPoints[], struct major majors[]);

int main()
{   
    struct major majors[NUM_MAJORS]; 
    initializeMajors(majors); //Initialize each major according to info in text file

    int choice;
    int status = 0; //Whether or not survey has been taken
    int hasMajor = -1; //Whether or not user calculated major. If != -1, value will be the major.

    printf("---[[[Welcome to Pick My Major!]]]---\n"); //Main menu
    do {
        printf("\n(1) Take the questionnaire\n");
        printf("(2) Calculate your result\n");
        printf("(3) See your points for each major\n");
        printf("(4) Get more information about a major\n");
        printf("(5) Save your data\n");
        printf("(6) Retrieve previous results\n");
        printf("Enter 0 to exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        
        switch(choice) {// this switch case is the main part of the program where every case has a different function that is being chosen
            case 1: status = takeSurvey(majors); break;
            case 2: hasMajor = calculateMajor(status, majors); break;
            case 3: displayPoints(status, majors); break;
            case 4: search(majors); break;
            case 5: saveData(hasMajor); break;
            case 6: displayData(); break;
            case 0: break;
            default: printf("Invalid choice\n");
        }
    } while (choice != 0);
    printf("Exiting");

    return 0;
}

void initializeMajors(struct major majors[]) { //Function to create the structure array of majors, to hold points for survey
    FILE *majorList;
    int id;
    char name[50];

    majorList = fopen("names.txt", "r+"); //Open the list of majors which is formatted (ID Name /newline)

    if (majorList == NULL) {
        printf("Error: major list file failed to open.");
        exit(1);
    }
    while (fscanf(majorList, "%d %[^\n]", &id, name) != EOF) {
        strcpy(majors[id - 1].name, name); //In the text files the major IDs start from 1, this is to put them in an array.
    }
    for (int i = 0; i < NUM_MAJORS; i++) {
        majors[i].points = 0; //Sets all points to 0 for survey
    }
}

int takeSurvey(struct major majors[]) //This will return an Integer to let the program know the survey has been taken.
{
    for (int i = 0; i < NUM_MAJORS; i++) {
        majors[i].points = 0; //Always reset points before each survey
    }

    //General Questions

    int question1Points[] = {1,1,1,1,0, 0,0,0,0,0, 0,1,0,0,0, 0,0,0,0};
    question("Question 1 - Do you see yourself working with technology or elsewhere in the engineering field in the future?", question1Points, majors);
    
    int question2Points[] = {0,0,0,1,0, 0,0,0,1,1, 0,0,1,1,1, 0,0,0,0};
    question("Question 2 - Is working in the healthcare field, either directly with patients or indirectly, something you could see yourself doing?", question2Points, majors);
    
    int question3Points[] = {0,0,0,0,1, 1,1,1,0,0, 0,0,0,0,0, 0,0,0,0};
    question("Question 3 - Do you see yourself pursuing a career in arts and humanities?", question3Points, majors);

    int question4Points[] = {0,0,0,0,0, 0,0,0,0,0, 1,1,0,0,0, 0,0,0,0};
    question("Question 4 - Do you see yourself working in a business environment?", question4Points, majors);
    
    int question5Points[] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,1,1,0};
    question("Question 5 - Are you interested in the design of buildings or structures, whether interior or exterior?", question5Points, majors);
    
    int question6Points[] = {0,0,0,0,0, 0,1,0,0,0, 0,0,0,0,0, 0,0,0,2};
    question("Question 6 - Do you enjoy teaching or informing others, no matter which subject?", question6Points, majors);
    
    //Specific Questions

    int question7Points[] = {0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0};
    question("Question 7 - You are interested in aircraft, spacecraft and/or the study of aerodynamics.", question7Points, majors);
    
    int question8Points[] = {0,0,0,0,0, 0,1,0,0,0, 0,0,0,0,0, 0,0,0,0};
    question("Question 8 - Does analyzing literature, or journaling, interest you?", question8Points, majors);
    
    int question9Points[] = {0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0};
    question("Question 9 - Are you interested in politics and the way government entities function?", question9Points, majors);
    
    int question10Points[] = {0,0,0,0,0, 0,0,0,1,0, 0,0,0,0,0, 0,0,0,0};
    question("Question 10 - Do you see yourself working directly with patients as a nurse?", question10Points, majors);
    
    int question11Points[] = {0,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0};
    question("Question 11 - You see yourself working with or maintaining financial systems.", question11Points, majors);
    
    int question12Points[] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 2,0,0,0};
    question("Question 12 - You enjoy the study of energy and/or how it interacts on the scale of space and time.", question12Points, majors);
    
    //Either/Or Questions

    int question13Points[] = {-1,1,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0};
    question("Question 13 - You prefer to work with software instead of hardware. ('Neutral' for neither)", question13Points, majors);
    
    int question14Points[] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,-1,1,0};
    question("Question 14 - You prefer the study of the interior designs of buildings, rather than their architecture. ('Neutral' for neither)", question14Points, majors);
    
    int question15Points[] = {0,0,0,0,0, 0,0,0,0,-1, 0,0,0,0,1, 0,0,0,0};
    question("Question 15 - You prefer the study of the human mind, instead of the study of the human body and how it functions. ('Neutral' for neither)", question15Points, majors);
    
    int question16Points[] = {0,0,0,0,0, 0,0,0,0,0, 0,0,1,-1,0, 0,0,0,0};
    question("Question 16 - You prefer the study of living organisms over the study of elements and matter itself. ('Neutral' for neither)", question16Points, majors);
    
    int question17Points[] = {0,0,0,0,-1, 1,0,0,0,0, 0,0,0,0,0, 0,0,0,0};
    question("Question 17 - You prefer the study of music theory over the study of theatre and playwriting. ('Neutral' for neither)", question17Points, majors);

    printf("You have finished the questionnaire and can now proceed with options to calculate your results!\n");
    return 1; //After this function is called, the program will know the user has taken the survey.
}

int calculateMajor(int hasTakenSurvey, struct major majors[]) {
    //Find the top major

    if (hasTakenSurvey)
    {
        int top = -1, topid = -1;
        for (int i = 0; i < NUM_MAJORS; i++) {
            //printf("%d: %s - %d\n",i,majors[i].name,majors[i].points); //Troubleshooter to print out each major and points
            if (majors[i].points > top) {
                top = majors[i].points;
                topid = i;
            }
        }
        
        switch(topid) {
            case -1:
                printf("We could not find a major for you, sorry.\n");
                return -1;
                break;
            default:
                printf("Based on your choices, the major we recommend for you is %s!\n", majors[topid].name);
                return topid;
        }
    }
    else
    {
        printf("You must take the questionnaire first!\n");
        return -1;
    }
}

void displayPoints(int hasTakenSurvey, struct major majors[]) {
    if (hasTakenSurvey)
    {
        printf("\n");
        for (int i = 0; i < NUM_MAJORS; i++) {
            printf("%d. %s: %d\n",i+1,majors[i].name,majors[i].points); //Troubleshooter to print out each major and points (repurposed into a function)
        }
    }
    else
    {
        printf("You must take the questionnaire first!\n");
    }
}

void search(struct major majors[])
{
    //This function shows info on a major of users choosing.
    FILE *majorlist;
    FILE *major;
    int selectedId;
    char name[50];
    char term[100];
    majorlist = fopen("names.txt", "r");// opens list of majors
    if (majorlist == NULL){
        printf("There was an error opening the file. \n");
        exit(1);
    }
    printf("\n");
    while(fgets(name, sizeof(name), majorlist)){
        printf("%s", name);// prints list of majors
    }
    printf("Please choose a number corresponding to the major you would like to learn about: \n");// user puts a number matching with the major
    do {
        scanf("%d", &selectedId);
    } while (selectedId < 1 || selectedId > 20);//to make sure user inputs a number between 1-20
    
    //This takes the usr's inputted ID, finds it in the structure array and gets the name for it
    struct major selectedMajor = majors[selectedId - 1]; //-1 because user selected from a list starting from 1

    char filename[50] = "majors/"; //Takes the name associated with the ID and finds the file for it
    strcat(filename, selectedMajor.name);
    strcat(filename,".txt");
    major = fopen(filename, "r+");

    if (!major) {
        printf("There was an error opening the file.\n");
    } else
    {
        char text[100];
        
        while(fgets(text, sizeof(text)-1, major)){
            printf("%s", text);
        }
        fclose(major);
    }
    
    fclose(majorlist);//closes both text files
}

void displayData()
{
    FILE *data;
    FILE *major;
    char input[50];
    char username[50];
    char majorOnFile[50];
    char userMajor[50];
    printf("Enter saved name: ");
    scanf("%s",input); //Because we used scanf, the usernames will only contain one word (easier to deal with data file/search function).

    data = fopen("data.txt", "r");
    if (data == NULL){
        printf("Error: The data file failed to open.");
        exit(1);
    }
    
    int found = 0;
    while (fscanf(data,"%s %[^\n]", username, majorOnFile) != EOF) {
        if (strcmp(input, username) == 0) {
            found = 1;
            strcpy(userMajor, majorOnFile); //Takes the LAST result of the username in the file. To get the first result, simply use break;
        }
    }
    if (found == 1)
    {
        printf("Your recorded major from the questionnaire is %s.\n",userMajor);
    }
    else
    {
        printf("Invalid name.\n");
    }
    
    fclose(data);
}
void saveData(int id)
{
    if (id >= 0)
    {
        FILE *data;
        FILE *major;
        char input[50]; //User input
        char username[50]; //Username returned from fscanf
        char majorOnFile[50]; //Major data returned from fscanf
        char majorName[50]; //Name of the major, which will be found when fscanf returns a hit
        int majorId;
    
        printf("Enter save name (no spaces): ");
        scanf("%s",input); //Using scanf because users entering savenames with spaces would kinda mess up our groove and whatnot
    
        data = fopen("data.txt", "a"); //Open the files containing the major data and the user save data
        major = fopen("names.txt", "r+");
        if (data == NULL || major == NULL){
            printf("Error: One of the data files failed to open.");
            exit(1);
        }
    
        while (fscanf(major, "%d %[^\n]", &majorId, majorName) != EOF) {
            if (majorId == id+1) { //Since we are dealing with the names.txt file (starts from 1), index will have to be + 1
                break; //takes the name of the topId's associated major when the loop finds a match for it
            }
        }
        fclose(major);
        
        //When the search function goes through, it will return the last result for a name, so no need to check for previous names
        fprintf(data, "%s %s\n", input, majorName);
        
        fclose(data);
    }
    else
    {
        printf("You must calculate your major first!\n");
    }
}

void question(char questionTitle[], int optionPoints[], struct major majors[]) //Simple Likert Scale function
{
    int ans;
    printf("\n%s\n", questionTitle);
    printf("(1) Strongly Agree\n");
    printf("(2) Agree\n");
    printf("(3) Neutral\n");
    printf("(4) Disagree\n");
    printf("(5) Strongly Disagree\n");
    //For each question, each major in the structure array will be given points (via question points array) based on user answer
    do {
        scanf("%d", &ans);
        switch(ans) {
            case 1:
                for (int i = 0; i < NUM_MAJORS; i++) {
                    majors[i].points += (optionPoints[i] * 2);
                }
                break;
            case 2:
                for (int i = 0; i < NUM_MAJORS; i++) {
                    majors[i].points += optionPoints[i];
                }
                break;
            case 3:
                break;
            case 4:
                for (int i = 0; i < NUM_MAJORS; i++) {
                    majors[i].points += (optionPoints[i] * -1);
                }
                break;
            case 5:
                for (int i = 0; i < NUM_MAJORS; i++) {
                    majors[i].points += (optionPoints[i] * -2);
                }
                break;
            default:
                printf("Invalid choice, answer again\n");
        }
    } while ((ans < 0) || (ans > 5));
}