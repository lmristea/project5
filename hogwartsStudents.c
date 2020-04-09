#include <stdio.h>
#include <stdlib.h>
#include "Student.h"

void insert(Student** root, Student* node);
Student* search(Student* root, char* first, char* last);
Student* delete(Student** root, char* first, char* last);
void quit(Contact* root);

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

int main(int argc, char **argv)
{
  Student student;

  Student* GryffindorRoot = NULL;
  Student* SlytherinRoot = NULL;
  Student* HufflepuffRoot = NULL;
  Student* RavenclawRoot = NULL;
  Student* deceasedRoot = NULL;
  Student* found = NULL;

  char input[20];
  scanf("%s\n", input);

  int i = 1;
  char* filename;
  char* firstname;
  char* lastname;
  int points;
  int year;
  int number;
  House house;

  while(i < argc)
  {
    if (strcmp(input, "quit") != 0)
    {
       printf("Please enter a command.\n");

       if (strcmp(input, "help") == 0)
       {
         printf("load: \nAdds all the student records in <filename> to the roster. The file is arranged one student per line where each record has the following format.");
         printf("save: \nSave the records of all living students in the roster to <filename>. ");
         printf("clear: \nClear the rosters for the four houses and for the list of deceased students. Delete all allocated memory.");
         printf("inorder: \nPrint out each house in an inorder traversal.");
         printf("preorder: \nPrint out each house in a preorder traversal.");
         printf("postorder: \nPrint out each house in a postorder traversal.");
         printf("add: \nAdd a student with the given attributes to the roster.");
         printf("kill: \nFind the given student in the given house's roster, remove the student from the house's roster, and add the student to the list of deceased students.");
         printf("find: \nFind the given student in the given house's roster and print out his or her data.");
         printf("points: \nFind the given student in the given house's roster and add <number> points to their point total.");
         printf("score: \nPrint out the current point scores for all houses. Points for deceased students are not factored into their house totals");
         printf("quit: \nQuit the program. ");
       }
       if (strcmp(input, "load") == 0)
       {
         ++i;
        filename = argv[i];
       }
       if (strcmp(input, "save") == 0)
       {
         ++i;
        filename = argv[i];
       }
       if (strcmp(input, "clear") == 0)
       {

       }
       if (strcmp(input, "inorder") == 0)
       {

       }
       if (strcmp(input, "preorder") == 0)
       {

       }
       if (strcmp(input, "postorder") == 0)
       {

       }
       if (strcmp(input, "add") == 0)
       {
         ++i;
         firstname = argv[i];
         ++i;
         lastname = argv[i];
         ++i;
         points = argv[i];
         ++i;
         year = argv[i];
         ++i;
         house = argv[i];
       }
       if (strcmp(input, "kill") == 0)
       {
        ++i;
        firstname = argv[i];
        ++i;
        lastname = argv[i];
        ++i;
        house = argv[i];
       }
       if (strcmp(input, "find") == 0)
       {
         ++i;
         firstname = argv[i];
         ++i;
         lastname = argv[i];
         ++i;
         house = argv[i];
       }
       if (strcmp(input, "points") == 0)
       {
         ++i;
         firstname = argv[i];
         ++i;
         lastname = argvi[i];
         ++i;
         house = argv[i];
         ++i;
         number = argv[i];
       }
       if (strcmp(input, "score") == 0)
       {

       }

    //quit();

    }

  }

  return 0;
}
