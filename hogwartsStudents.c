#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Student.h"

#define HOUSE_COUNT 5

Student* createStudent(char* first, char* last, int points, int year, House house);
Student* insert(Student* root, Student* node);
Student* search(Student* root, char* first, char* last);
Student* delete(Student** root, char* first, char* last);
int compareStudent(Student* student, char* first, char* last);
void printStudent(const Student* student, FILE* file);
void quit(Student* root);
void clearStudent(Student* root);
void clear(Student* houses[]);
void kill(char* first, char* last, House house);


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

void printStudent(const Student* student, FILE* file) {
  char fullName[1024];
  sprintf(fullName, "%s %s", student->first, student->last);
  fprintf(file, "%-25s Points: %d\t Year: %d\t House: %s\n", fullName, student->points, student->year, HOUSE_NAMES[student->house]);
}

/*
 * Function: printInOrder, takes a pointer to a student,
 * Returns:  Nothing. Prints the tree from left subtree -> root -> right subtree.
 */
void printInOrder(Student* root) {
  if (root != NULL) {
    printInOrder(root->left);
    printStudent(root, stdout);
    printInOrder(root->right);
  }
}

/*
 * Function: printPreOrder, takes a pointer to a student,
 * Returns:  Nothing. Prints the tree from root -> left subtree -> right subtree.
 */
void printPreOrder(Student* root, FILE* file) {
  if (root != NULL) {
     printStudent(root, file);
     printPreOrder(root->left, stdout);
     printPreOrder(root->right, stdout);
  }
}
/*
 * Function: printPostOrder, takes a pointer to a student,
 * Returns:  Nothing. Prints the tree from left subtree -> right subtree -> root.
 */
void printPostOrder(Student* root) {
  if(root != NULL) {
    printPostOrder(root->left);
    printPostOrder(root->right);
    printStudent(root, stdout);
  }
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
 * Function: getHouse, takes a string.
 * Returns:  an int, 0 if the string passed in is equal to one of the Houses,
 *           anything else will return an error if not found.
 */

int getHouse(char* house) {
  for(int i = GRYFFINDOR; i <= SLYTHERIN; ++i) {
    if(strcmp(house, HOUSE_NAMES[i]) == 0) {
      return i;
    }
  }
  return -1;
}

void load(FILE* file, Student* houses[]) {
  char firstName[1024];
  char lastName[1024];
  char houseName[1024];
  int points;
  int year;
  House house;
  /* There are 5 things to be read on each line for a student. */
  while(fscanf(file, "%s %s %d %d %s", firstName, lastName, &points, &year, houseName) == 5) {
      house = getHouse(houseName);

       if(year < 1 || year > 7){
         printf("Invalid year.\n");
       } else if(house == -1 ){
         printf("Invalid house.\n");
       } else {
        Student* node = createStudent(firstName, lastName, points, year, house);
        houses[house] = insert(houses[house], node);
       }
  }
}

/*
 * Function: insert, inserts a node into a tree.
 * Returns:  a pointer to a student.
 */

/*Save the records of all living students in the roster to <filename>.
The format of the file should match what is read in by the load command.
To match sample output, please print out the students in each house starting with Gryffindor, then Ravenclaw, then Hufflepuff, and finally Slytherin.
Each house should be printed in a preorder traversal.
That way, the file will match the structure of the trees you have generated.
*/
 void save(char filename[], Student* houses[])
 {
  FILE* file = fopen(filename, "w");
  if (file == NULL)
  {
    printf("INVALID FILE\n");
  }
  else
  {
    for(int i = 0; i < HOUSES; ++i)
    {
        printPreOrder(houses[i], file);
    }
    fclose(file);
  }

 }


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
*/
//Remove a student from a tree and return a pointer to the node containing the student or NULL if the student is not found.
Student* delete(Student** root, char* first, char* last)
{
  if(*root == NULL) {
    return NULL;
  } else {
    Student* temp = search(*root, first, last);
    clearStudent(temp);
    return temp;
  }
}

// void kill(char* first, char* last, char* house){
//   Student* temp = search()
// }

/*
 * Function: clearStudent, frees a tree.
 * Returns:  a pointer to a student.
*/

void clearStudent(Student* root){
    if (root != NULL) {
        clear(&root->left);
        clear(&root->right);
        free(root->first);
        free(root->last);
        free(root);
    }
}

/*
 * Function: clearStudent, frees a tree.
 * Returns:  a pointer to a student.
*/

void clear(Student* houses[]){
    for(int i = 0; i < HOUSES; ++i) {
        free(houses[i]);
        houses[i] = NULL;
    }
}


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
    printf("Enter command: ");
    scanf("%s", input);

     if (strcmp(input, "help") == 0)
     {
       printf("help\n");
       printf("Prints this display\n\n");
       printf("load\n");
       printf("Adds all the student records in <filename> to the roster. The file is arranged one student per line where each record has the following format\n\n");
       printf("save\n");
       printf("Save the records of all living students in the roster to <filename>\n\n");
       printf("clear\n");
       printf("Clear the rosters for the four houses and for the list of deceased students. Delete all allocated memory\n\n");
       printf("inorder\n");
       printf("Print out each house in an inorder traversal\n\n");
       printf("preorder\n");
       printf("Print out each house in a preorder traversal\n\n");
       printf("postorder\n");
       printf("Print out each house in a postorder traversal\n\n");
       printf("add\n");
       printf("Add a student with the given attributes to the roster\n\n");
       printf("kill\n");
       printf("Find the given student in the given house's roster, remove the student from the house's roster, and add the student to the list of deceased students\n\n");
       printf("find\n");
       printf("Find the given student in the given house's roster and print out his or her data\n\n");
       printf("points\n");
       printf("Find the given student in the given house's roster and add <number> points to their point total\n\n");
       printf("score\n");
       printf("Print out the current point scores for all houses. Points for deceased students are not factored into their house totals\n\n");
       printf("quit\n");
       printf("Quit the program\n\n");
     }
     else if (strcmp(input, "load") == 0)
     {
       //move these into the load function
      scanf("%s", fileName);
      FILE* file = fopen(fileName, "r");
      if(file == NULL){
        printf("File DNE.");
      } else {
        load(file, houses);
        fclose(file);
      }
     }
     else if (strcmp(input, "save") == 0)
     {
      scanf("%s", fileName);
      save(fileName, houses);
     }
     else if (strcmp(input, "clear") == 0)
     {
       printf("All data cleared.\n");
       clear(houses);
     }
     else if (strcmp(input, "inorder") == 0)
     {
        /* If you add a bunch of students and try to print them, this works but returns a segmentation fault at the end. */
        for(int i = 0; i < HOUSES; ++i){
          printf("\n%s House\n", HOUSE_NAMES[i]);
          printInOrder(houses[i]);
        }
     }
     else if (strcmp(input, "preorder") == 0)
     {
       for(int i = 0; i < HOUSES; ++i){
          printf("\n%s House\n", HOUSE_NAMES[i]);
          printPreOrder(houses[i], stdout);
        }
     }
     else if (strcmp(input, "postorder") == 0)
     {
       for(int i = 0; i < HOUSES; ++i){
          printf("\n%s House\n", HOUSE_NAMES[i]);
          printPostOrder(houses[i]);
        }
     }
     else if (strcmp(input, "add") == 0)
     {
       printf("Student's First Name: ");
       scanf("%s", firstName);
       printf("Student's Last Name: ");
       scanf("%s", lastName);
       printf("Student's Points: ");
       scanf("%d", &points);
       printf("Student's Year Number: ");
       scanf("%d", &year);
       printf("Student's House Name: ");
       scanf("%s", houseName);
       house = getHouse(houseName);

       if(year < 1 || year > 7){
         printf("Invalid year.\n");
       } else if(house == -1 ){
         printf("Invalid house.\n");
       } else {
        Student* node = createStudent(firstName, lastName, points, year, house);
        houses[house] = insert(houses[house], node);
       }
     }
     else if (strcmp(input, "kill") == 0)
     {
      printf("Student's First Name: ");
      scanf("%s", firstName);
      printf("Student's Last Name: ");
      scanf("%s", lastName);
      printf("Student's House Name: ");
      scanf("%s", houseName);
     }
     else if (strcmp(input, "find") == 0)
     {
       printf("Student's First Name: ");
       scanf("%s", firstName);
       printf("Student's Last Name: ");
       scanf("%s", lastName);
       printf("Student's House Name: ");
       scanf("%s", houseName);
       house = getHouse(houseName);
       found = search(houses[house], firstName, lastName);
       if( found == NULL )
					printf("%s not found.", firstName);
				else
					printStudent(found, stdout);
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
     else
     {
       printf("Unknown command: %s\n", input);
     }

  }

  printf("call quit()\n");

  return 0;
}
