#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
void OptionsPrint(char *DietOptions[4],int size){
    for(int i=0; i < size; i++){
        printf("\n-%s", DietOptions[i]);
    }

}
void ReadFile(){
}
int main(){

    //Variables for later
    typedef struct{
        char name[100];
        char link[500];
    } Recipe;
    Recipe recipes[100];
    
    //File stuff
    FILE *ChosenFile;


    //introduction
    printf("Hello, welcome to the Meal Planner program!\n This program will print out a week-long meal plan(Sunday-Saturday) based on your diet preference");
   //ask user the date
   char date[50];
   printf("\nPlease enter todays date(Format dosen't matter this is for you to read): ");
   fgets(date, 50, stdin);

   //declare diet options and scan selection from user
    char *DietOptions[4] = {"None", "Vegetarian", "Vegan", "High-Protein"};
    char UserDiet[50];
    int ValidInput = 0;
    int size = sizeof(DietOptions) / sizeof(DietOptions[0]);

    while(!ValidInput){
        printf("\n\nPlease enter your diet/diet preference. Type in one of the options listed below");
        OptionsPrint(DietOptions, size);
        printf("\n");
        fgets(UserDiet, sizeof(UserDiet), stdin);
        UserDiet[strcspn(UserDiet, "\n")] = 0;
        for(int i=0; i < size; i++){
            if(strcmp(UserDiet, DietOptions[i]) == 0)
                ValidInput = 1;
        }
        if(!ValidInput)
            printf("Please Try again");
    
    }

    //From diet selection, determine the list and file being used
    
    if(strcmp(UserDiet, "None") == 0){
        ChosenFile = fopen("None.txt", "r");
    }
    else if(strcmp(UserDiet, "Vegetarian") == 0){
        ChosenFile = fopen("Vegetarian.txt", "r");
    }
    else if(strcmp(UserDiet, "Vegan") == 0){
        ChosenFile = fopen("Vegan.txt", "r");
    }
    else if(strcmp(UserDiet, "High-Protein") == 0){
        ChosenFile = fopen("HighProtein.txt", "r");
    }

    //Read off chosen file and store in matrix
    if (ChosenFile == NULL) {
        perror("Error opening file");
        return 0;
    }

    int i = 0;
    while (i < 100 && fscanf(ChosenFile, "%99[^\n]\n%499[^\n]\n", recipes[i].name, recipes[i].link) == 2) {
        i++;
    }
    fclose(ChosenFile);
    //randomly generate random numbers and put them in
    srand(time(NULL));
    int randNumbers[7];
    for (int i = 0; i < 7; i++) {
        randNumbers[i] = rand() % 22;  // Random numbers between 0 and 21
    }
    //check for duplicatesv and replace
    int count = sizeof(randNumbers) / sizeof(randNumbers[0]);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (randNumbers[i] == randNumbers[j]) {
                randNumbers[i] = rand() % 22;
            }
        }
    }
    //Use random numbers to select meals and print
    char *DaysOfWeek[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thurday", "Friday", "Saturday"};
    for(int i = 0; i < 7; i++){
        printf("%s: \n%s\n%s\n", DaysOfWeek[i], recipes[randNumbers[i]].name, recipes[randNumbers[i]].link);
    }
    //create a new file for user that prints out mealplan
    FILE *UserFile;
    UserFile = fopen("UserMealPlan.txt", "w");

    fprintf(UserFile, "Date: ");
    for(int i=0; i < 50; i++){
    fprintf(UserFile,"%c", date[i]);
    }

    for(int i = 0; i < 7; i++){
    fprintf(UserFile, "\n%s: \n%s\n%s\n", DaysOfWeek[i], recipes[randNumbers[i]].name, recipes[randNumbers[i]].link);}
    fclose(UserFile);

    //check print is put in comment form when not being used
    //printf("%s", UserDiet);
    return 0;
}
