#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Student.h"


Student* createStudent(char* first, char* last, int points, int year, House house);
Student* insert(Student* root, Student* node);
Student* search(Student* root, char* first, char* last);
Student* delete(Student** root, char* first, char* last);
int compareStudent(Student* student, char* first, char* last);
void printStudent(const Student* student);
void quit(Student* root);

/*
 * Function: createStudent, takes information about a student and creates a new node.
 * Returns:  a pointer to a student. 
 */
Student* createStudent(char* first, char* last, int points, int year, House house)
{
  Student* temp = (Student*)malloc(sizeof(Student));
  temp->first = strdup(first);
  temp->last = strdup(last);
  temp->points = points;
  temp->year = year;
  temp->house = house;
  temp->left = NULL;
  temp->right = NULL;

  return temp;
}

/*
 * Function: printStudent, prints student information
 * Returns:  
 */

void printStudent(const Student* student) {
  printf("\t%s %s\n", student->first, student->last);
  printf("\t%d", student->points);
  printf("\t%d", student->year);
  printf("\t%u", student->house);
}

/*
 * Function: compareStudent, takes a pointer to a student, then compares the node's name 
 *            with the given first and last name.
 * Returns:  an int, 0 if they are equal, greater than 0 if the s1 is > than s2, and less than 0 if s1 > s2.
 */
int compareStudent(Student* student, char* first, char* last) {
  int difference = strcmp(student->last, last);
  if (difference == 0) {
    difference = strcmp(student->first, first);
  }
  return difference;
}

/*
 * Function: insert, inserts a node into a tree.
 * Returns:  a pointer to a student. 
 */

Student* insert(Student* root, Student* node) 
{
  if(root == NULL) {
    return node;
  }
  int difference = compareStudent(root, node->first, node->last);
  if( difference == 0)
    printf("Error: Student exist");
  else if(difference > 0) 
    root->left = insert(root->left, node);
  else 
    root->right = insert(root->right, node);
  
  return root;
}

/*
 * Function: search, searches for a student by first and last name.
 * Returns:  a pointer to a student. 
 */

Student* search(Student* root, char* first, char* last)
{
  if(root == NULL) {
    return root;
  }
  int difference = compareStudent(root, first, last);
  if(difference == 0) 
    return root;
  else if(difference > 0) {
    return search(root->left, first, last); 
  } else 
    return search(root->right, first, last);
}

/*
 * Function: delete, searches through a tree and removes the Student from the tree if the student exists.
 * Returns:  a pointer to a student. 

//Remove a student from a tree and return a pointer to the node containing the student or NULL if the student is not found.
Student* delete(Student** root, char* first, char* last)
{
  
}
 */

int main()
{
  //an array (one for each house) initialized to null.
  Student* houses[] = { NULL, NULL, NULL, NULL, NULL };
  
  Student* found = NULL;

  // intialize all arrays to size 1024, so we can fill them later
  char fileName[1024];
  char firstName[1024];
  char lastName[1024];
  char houseName[1024];
  int points;
  int year;
  int number;
  int i = 0;
  House house;

  char input[1024] = "";

   while(strcmp(input, "quit") != 0)
  {
    printf("Please enter a command.\n");
    scanf("%s", input);

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
     else if (strcmp(input, "load") == 0)
     {
       /*
        * Note: We changed the regex things because scanf returns an int, the number of things 
        * read correctly, not the actual string. Which is why I went through and changed all of the 
        * char*'s above to just char[] arrays of size 1024 so we can read the string into them.
        * 
        * This changes are the only thing we did to the menu.
        */ 
      scanf("%s", fileName);
     }
     else if (strcmp(input, "save") == 0)
     {
      scanf("%s", fileName);
     }
     else if (strcmp(input, "clear") == 0)
     {
       printf("call clear().\n");
     }
     else if (strcmp(input, "inorder") == 0)
     {
       printf("call inorder().\n");
     }
     else if (strcmp(input, "preorder") == 0)
     {
       printf("call preorder().\n");
     }
     else if (strcmp(input, "postorder") == 0)
     {
       printf("call postorder().\n");
     }
     else if (strcmp(input, "add") == 0)
     {
       printf("Student's First Name: ");
       scanf("%s", firstName);
       printf("\nStudent's Last Name: ");
       scanf("%s", lastName);
       printf("\nStudent's Points: ");
       scanf("%d", &points);
       printf("\nStudent's Year Number: ");
       scanf("%d", &year);
       printf("\nStudent's House Name: ");
       scanf("%s", houseName);
       Student* node = createStudent(firstName, lastName, points, year, house);
       insert(houses[i], node);
     }
     else if (strcmp(input, "kill") == 0)
     {
      printf("Student's First Name: ");
      scanf("%s", firstName);
      printf("\nStudent's Last Name: ");
      scanf("%s", lastName);
      printf("\nStudent's House Name: ");
      scanf("%s", houseName);
     }
     else if (strcmp(input, "find") == 0)
     {
       printf("Student's First Name: ");
       scanf("%s", firstName);
       printf("\nStudent's Last Name: ");
       scanf("%s", lastName);
       printf("\nStudent's House Name: ");
       scanf("%u", &house); // don't know exactly how to get our houses array working and the houseName consolidated so we can use that value to identify a student
       Student* temp = (Student*)malloc(sizeof(Student));
       temp->first = strdup(firstName);
       temp->last = strdup(lastName);
       temp->house = house;
       /* Note: following code works but doesn't print the exact thing we want.*/
       found = search(temp, temp->first, temp->last);
       if( found == NULL )
					printf("\"%s\" not found\n", firstName);
				else
					printStudent( found );
     }
     else if (strcmp(input, "points") == 0)
     {
       scanf("%s", firstName);
       scanf("%s", lastName);
       scanf("%s", houseName);
       scanf("%d", &number);
     } else if (strcmp(input, "score") == 0)
     {
       printf("call score()\n");
     }

  }

  printf("call quit()\n");

  return 0;
}
