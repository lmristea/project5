#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Student.h"

#define DECEASED 4

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
int getScore(Student* root);


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

void printStudent(const Student* student, FILE* file)
{
  char fullName[1024];
  sprintf(fullName, "%s %s", student->first, student->last);
  fprintf(file, "%-25s Points: %d\t Year: %d House: %s\n", fullName, student->points, student->year, HOUSE_NAMES[student->house]);
}

/*
 * Function: printInOrder, takes a pointer to a student,
 * Returns:  Nothing. Prints the tree from left subtree -> root -> right subtree.
 */
void printInOrder(Student* root)
{
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
void printPreOrder(Student* root, FILE* file)
{
  if (root != NULL) {
     printStudent(root, file);
     printPreOrder(root->left, file);
     printPreOrder(root->right, file);
  }
}
/*
 * Function: printPostOrder, takes a pointer to a student,
 * Returns:  Nothing. Prints the tree from left subtree -> right subtree -> root.
 */
void printPostOrder(Student* root)
{
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
int compareStudent(Student* student, char* first, char* last)
{
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

int getHouse(char* house)
{
  for(int i = GRYFFINDOR; i <= SLYTHERIN; ++i) {
    if(strcmp(house, HOUSE_NAMES[i]) == 0) {
      return i;
    }
  }
  return -1;
}

void load(char fileName[], Student* houses[])
{
  FILE* file = fopen(fileName, "r");
  char firstName[1024];
  char lastName[1024];
  char houseName[1024];
  int points;
  int year;
  House house;
  while(fscanf(file, "%s %s %d %d %s", firstName, lastName, &points, &year, houseName) == 5)
  {
      house = getHouse(houseName);

       if(house == -1)
       {
         printf("Invalid house.\n");
       } else if(year < 1 || year > 7)
       {
         printf("Invalid year.\n");
       } else
       {
        Student* node = createStudent(firstName, lastName, points, year, house);
        houses[house] = insert(houses[house], node);
       }
  }
}

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
    printf("Add failed. Student named %s %s already present in roster.\n", root->first, root->last);
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
  Student* temp = *root;
  if(temp == NULL) {
    return temp;
  }
  int difference = compareStudent(temp, first, last);
  if(difference == 0)
  {
    if (temp->left == NULL)
    {
      *root = temp->right;
    }
    else if(temp->right == NULL)
    {
      *root = temp->left;
    }
    else
    {
      if (temp->right->left == NULL)
      {
        *root = temp->right;
        temp->right->left = temp->left;
      }
      else
      {
        Student* parent = temp->right;
        Student* current = temp->right->left;
        while(current->left != NULL)
        {
          parent = current;
          current = current->left;
        }
        *root = current;
        parent->left = current->right;
        current->left = temp->left;
        current->right = temp->right;
      }
    }
    temp->left = NULL;
    temp->right = NULL;
    return temp;
  }
  else if(difference > 0) {
    return delete(&temp->left, first, last);
  } else
    return delete(&temp->right, first, last);
}

/*
 * Function: clearStudent, frees a student node.
*/

void clearStudent(Student* root)
{
    if (root != NULL) {
        clearStudent(root->left);
        clearStudent(root->right);
        free(root->first);
        free(root->last);
        free(root);
    }
}

/*
 * Function: getScore: counts up the total points in each house.
 */
int getScore(Student* root)
  {
    if (root == NULL)
    {
      return 0;
    }
    else
    {
      return root->points + getScore(root->left) + getScore(root->right);
    }
  }

/*
 * Function: clear, frees a tree.
*/

void clear(Student* houses[])
{
    for(int i = 0; i < HOUSES; ++i) {
        clearStudent(houses[i]);
        clearStudent(houses[DECEASED]);
        houses[i] = NULL;
        houses[DECEASED] = NULL;
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
       printf("load <filename>\n");
       printf("Adds the contents of a file to the current roster\n\n");
       printf("save <filename>\n");
       printf("Saves the current roster to a file\n\n");
       printf("clear\n");
       printf("Clear the current roster\n\n");
       printf("inorder\n");
       printf("Print out an inorder traversal of the roster for each house\n\n");
       printf("preorder\n");
       printf("Print out a preorder traversal of the roster for each house\n\n");
       printf("postorder\n");
       printf("Print out a postorder traversal of the roster for each house\n\n");
       printf("add <firstname> <lastname> <points> <year> <house>\n");
       printf("Adds a student to the roster\n\n");
       printf("kill <firstname> <lastname> <house>\n");
       printf("Moves a student to the deceased list\n\n");
       printf("find <firstname> <lastname> <house>\n");
       printf("Searches for a student in a house\n\n");
       printf("points <firstname> <lastname> <house> <points>\n");
       printf("Changes the points a student has earned by the specified amount\n\n");
       printf("score\n");
       printf("Lists the point totals for all four houses\n\n");
       printf("quit\n");
       printf("Quits the program\n\n");
     }
     else if (strcmp(input, "load") == 0)
     {
       //move these into the load function
      scanf("%s", fileName);
      if(fileName == NULL){
        printf("Load failed. Invalid file: %s.\n", fileName);
      } else {
        printf("Successfully loaded data from file %s.\n", fileName);
        load(fileName, houses);
      }
     }
     else if (strcmp(input, "save") == 0)
     {
      scanf("%s", fileName);
      if (fileName == NULL)
      {
        printf("Save failed. Invalid file: %s\n", fileName);
      }
      else
      {
        printf("Successfully saved data to file %s.\n", fileName);
        save(fileName, houses);
      }

     }
     else if (strcmp(input, "clear") == 0)
     {
       printf("All data cleared.\n");
       clear(houses);
     }
     else if (strcmp(input, "inorder") == 0)
     {
       printf("Inorder print-out of roster:\n");
        /* If you add a bunch of students and try to print them, this works but returns a segmentation fault at the end. */
        for(int i = 0; i < HOUSES; ++i){
          printf("\n%s House\n\n", HOUSE_NAMES[i]);
          printInOrder(houses[i]);
        }
        printf("\nDeceased\n");
        printInOrder(houses[DECEASED]);
     }
     else if (strcmp(input, "preorder") == 0)
     {
       printf("Preorder print-out of roster:\n");
       for(int i = 0; i < HOUSES; ++i){
          printf("\n%s House\n\n", HOUSE_NAMES[i]);
          printPreOrder(houses[i], stdout);
        }
        printf("\nDeceased\n");
        printPreOrder(houses[DECEASED], stdout);
     }
     else if (strcmp(input, "postorder") == 0)
     {
       printf("Postorder print-out of roster:\n");
       for(int i = 0; i < HOUSES; ++i){
          printf("\n%s House\n\n", HOUSE_NAMES[i]);
          printPostOrder(houses[i]);
        }
        printf("\nDeceased\n");
        printPostOrder(houses[DECEASED]);
     }
     else if (strcmp(input, "add") == 0)
     {
       scanf("%s", firstName);
       scanf("%s", lastName);
       scanf("%d", &points);
       scanf("%d", &year);
       scanf("%s", houseName);
       house = getHouse(houseName);

       if(year < 1 || year > 7)
       {
         printf("Add failed. Invalid year: %d\n", year);
       } else if(house == -1 )
       {
         printf("Add failed. Invalid house: %s\n", houseName);
       } else
       {
         if (search(houses[house],firstName, lastName) == NULL)
        {
          Student* node = createStudent(firstName, lastName, points, year, house);
          houses[house] = insert(houses[house], node);
          printf("Added %s %s to the roster. \n", firstName, lastName);
        }
        else
        {
          printf("Add failed. Student named %s %s already present in roster.\n", firstName, lastName);
        }
       }
     }
     else if (strcmp(input, "kill") == 0)
     {
      scanf("%s", firstName);
      scanf("%s", lastName);
      scanf("%s", houseName);
      house = getHouse(houseName);
      if(house == -1 ){
        printf("Kill failed. Invalid house: %s\n", houseName);
      } else {
       Student* node = delete(&houses[house],firstName, lastName);
       if (node == NULL)
       {
         printf("Kill failed. %s %s was not found in %s House\n", firstName, lastName, houseName);
       }
       else
       {
         houses[DECEASED] = insert(houses[DECEASED], node);
         printf("Moved %s %s to list of deceased students.\n", firstName, lastName);
       }
      }
     }
     else if (strcmp(input, "find") == 0)
     {
       scanf("%s", firstName);
       scanf("%s", lastName);
       scanf("%s", houseName);
       house = getHouse(houseName);
        if(house == -1 ){
        printf("Kill failed. Invalid house: %s\n", houseName);
        }
       found = search(houses[house], firstName, lastName);
       if( found == NULL )
					printf("Find failed. %s %s was not found in %s House\n", firstName, lastName, houseName);
				else
					printStudent(found, stdout);
     }
     else if (strcmp(input, "points") == 0)
     {
       scanf("%s", firstName);
       scanf("%s", lastName);
       scanf("%s", houseName);
       scanf("%d", &number);

       house = getHouse(houseName);
       if(house == -1 ){
        printf("Point change failed. Invalid house: %s\n", houseName);
       }
       found = search(houses[house], firstName, lastName);
       if( found == NULL )
       {
         printf("Point change failed. %s %s was not found in %s House\n", firstName, lastName, houseName);
       }
       else
       {
         int currentPoints = found->points;
         currentPoints += number;
         found->points = currentPoints;
         printf("Points for %s %s changed to %d.\n", firstName, lastName, currentPoints);
       }

     } else if (strcmp(input, "score") == 0)
     {
       printf("Point totals:\n\n");
       for(int i = 0; i < HOUSES; ++i)
       {
          printf("%s House:\t%d\n", HOUSE_NAMES[i], getScore(houses[i]));
        }
     }
     else if (strcmp(input, "quit") == 0) {
       clear(houses);
       printf("All data cleared.\n");
       return 0;
     }
     else
     {
       printf("Unknown command: %s\n", input);
     }
  }
  return 0;
}
