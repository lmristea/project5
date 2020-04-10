#include <stdio.h>
#include <stdlib.h>
#include "Student.h"

void insert(Student** root, Student* node);
Student* search(Student* root, char* first, char* last);
Student* delete(Student** root, char* first, char* last);
void quit(Student* root);

//Insert a node into a tree, obeying ordering constraints. Note: You should check that a student doesn't exist before adding him or her to a tree. There should be no duplicates in a roster.
void insert(Student** root, Student* node)
{

}

//Search in a tree for a student with a given first and last name. Return a pointer to the student if found, NULL otherwise.
Student* search(Student* root, char* first, char* last)
{

}

//Remove a student from a tree and return a pointer to the node containing the student or NULL if the student is not found.
Student* delete(Student** root, char* first, char* last)
{

}

int main()
{
  Student student;

  Student* GryffindorRoot = NULL;
  Student* SlytherinRoot = NULL;
  Student* HufflepuffRoot = NULL;
  Student* RavenclawRoot = NULL;
  Student* deceasedRoot = NULL;
  Student* found = NULL;

  //int i = 1;
  char* filename;
  char* firstname;
  char* lastname;
  int points;
  int year;
  int number;
  House house;

  char input[20];

   while(strcmp(input, "quit") != 0)
  {
    printf("Please enter a command.\n");
    scanf("%[^\n]%*c", input);

     if (strcmp(input, "help") == 0)
     {
       printf("load: \nAdds all the student records in <filename> to the roster. The file is arranged one student per line where each record has the following format.\n");
       printf("\n");
       printf("save: \nSave the records of all living students in the roster to <filename>.\n");
       printf("\n");
       printf("clear: \nClear the rosters for the four houses and for the list of deceased students. Delete all allocated memory.\n");
       printf("\n");
       printf("inorder: \nPrint out each house in an inorder traversal.\n");
       printf("\n");
       printf("preorder: \nPrint out each house in a preorder traversal.\n");
       printf("\n");
       printf("postorder: \nPrint out each house in a postorder traversal.\n");
       printf("\n");
       printf("add: \nAdd a student with the given attributes to the roster.\n");
       printf("\n");
       printf("kill: \nFind the given student in the given house's roster, remove the student from the house's roster, and add the student to the list of deceased students.\n");
       printf("\n");
       printf("find: \nFind the given student in the given house's roster and print out his or her data.\n");
       printf("\n");
       printf("points: \nFind the given student in the given house's roster and add <number> points to their point total.\n");
       printf("\n");
       printf("score: \nPrint out the current point scores for all houses. Points for deceased students are not factored into their house totals\n");
       printf("\n");
       printf("quit: \nQuit the program.\n");
       printf("\n");
     }
     if (strcmp(input, "load") == 0)
     {
      filename = scanf("%[^\n]%*c", filename);
     }
     if (strcmp(input, "save") == 0)
     {
      filename = scanf("%[^\n]%*c", filename);
     }
     if (strcmp(input, "clear") == 0)
     {
       printf("call clear().\n");
     }
     if (strcmp(input, "inorder") == 0)
     {
       printf("call inorder().\n");
     }
     if (strcmp(input, "preorder") == 0)
     {
       printf("call preorder().\n");
     }
     if (strcmp(input, "postorder") == 0)
     {
       printf("call postorder().\n");
     }
     if (strcmp(input, "add") == 0)
     {
       firstname = scanf("%[^\n]%*c", firstname);
       lastname = scanf("%[^\n]%*c", lastname);
       points = scanf("%d", &points);
       year = scanf("%d", &year);
       house = scanf("%[^\n]%*c", house);
     }
     if (strcmp(input, "kill") == 0)
     {
      firstname = scanf("%[^\n]%*c", firstname);
      lastname = scanf("%[^\n]%*c", lastname);
      house = scanf("%[^\n]%*c", house);
     }
     if (strcmp(input, "find") == 0)
     {
       firstname = scanf("%[^\n]%*c", firstname);
       lastname = scanf("%[^\n]%*c", lastname);
       house = scanf("%[^\n]%*c", house);
     }
     if (strcmp(input, "points") == 0)
     {
       firstname = scanf("%[^\n]%*c", firstname);
       lastname = scanf("%[^\n]%*c", lastname);
       house = scanf("%[^\n]%*c", house);
       number = scanf("%d", &number);
     }
     if (strcmp(input, "score") == 0)
     {
       printf("call score()\n");
     }

  }

  printf("call quit()\n");

  return 0;
}
