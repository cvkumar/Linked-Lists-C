 /*****************************************************************
     * Caleb V. Kumar                                               *
     * Box:  Science                                                 *
     * Supplemental Problem #5 for CSC 161                            *
     * Assignment for Tuesday, 5/6/14                              *
     *****************************************************************/

    /* ***************************************************************
     * Academic honesty certification:                               *
     *   Written/online sources used:                                *
     *     CSC161lab: Files
     CSC161: Program statefile.c
     *   Help obtained                                               *
     *     I consulted Professor Walker regarding making a schematic
       memory diagram and how to approach the "stringreverse" problem on 
       question1.
     *   My signature below confirms that the above list of sources  *
     *   is complete AND that I have not talked to anyone else       *
     *   [e.g., CSC 161 students] about the solution to this problem *
     *                                                               *
     *   Signature:                                                  *
     *****************************************************************/












/* A program shell  to maintain a linked list of names */

/* library for standard I/O */
#include <stdio.h>

/* library for memory allocation */
#include <stdlib.h>

#include <string.h>
/* Maximum length of names */
#define strMax 20

struct node
{ char data [strMax];
  struct node * next;
};

/* function prototypes, listed in alphabetical order */

void addName(struct node ** firstPtr);
/* pre-condition:  firstPtr points to the pointer
                   designating the head of a list
  post-condition:  a name is read and
                   inserted into the list at a designated place
*/

void print(struct node * first);
/* pre-condition:  first designates the first node of a list 
  post-condition:  The items on the list are printed from first to last
                   the list itself is unchanged
*/

void addNamesFromFile (struct node ** first);
/* pre-condition:  first designates the first node of a list 
  post-condition:  the program asks the user for a file name
                   names from individual lines of the file are inserted
                   at the beginning of the original list
*/

void removeDuplicates (struct node * first);
/* pre-condition:  first designates the first node of a list 
  post-condition:  each name on the list appears only once (no duplicate names)
                   when duplicates occur on the original list,
                      only the first occurence remains after processing
*/

void duplicate (struct node * firstPtr);
/* pre-condition:  first designates the first node of a list 
  post-condition:  each node is duplicated, with the new node inserted
                   after the original node
*/

int main (void) {
  /* program to coordinate the menu options and calls the requested function */

  struct node * first = NULL;   /* pointer to the first list item */
  char option[strMax];          /* user response to menu selection */

  printf ("Program to Maintain a List of Names\n");

  while (1) {
    /* print menu options */
    printf ("Options available\n");
    printf ("I - Insert a name (from the keyboard) into the list\n");
    printf ("P - Print the names on the list\n");
    printf ("F - Read a sequence of names from a file onto the list\n");
    printf ("R - Remove duplicate names (leaving only the first occurence)\n");
    printf ("D - Duplicate each node\n");
    printf ("Q - Quit\n");

    /* determine user selection */
    printf ("Enter desired option: ");
    scanf ("%s", option);
    
    switch (option[0])
      { case 'I':
        case 'i': 
          addName(&first);
          break;
        case 'P':
        case 'p': 
          print(first);
          break;
        case 'F':
        case 'f': 
          addNamesFromFile(&first);
          break;
        case 'R':
        case 'r': 
          removeDuplicates(first);
          break;
        case 'D': 
        case 'd': 
          duplicate(first);
          break;
        case 'Q':
        case 'q':
          printf ("Program terminated\n");
          return 0;
          break;
        default: printf ("Invalid Option - Try Again!\n");
          continue;
      }
  }
}
        
void addName(struct node ** firstPtr) {
/* pre-condition:  firstPtr points to the pointer designating the head of a list
  post-condition:  a name is read and
                   inserted into the list at a designated place
*/

  char oldName [strMax];
  struct node * newNode = (struct node *)malloc(sizeof(struct node));
  struct node * listPtr;
  struct node * prevPtr;

   printf ("Enter name to be inserted into list: ");
   scanf ("%s", newNode->data);

   if (*firstPtr == NULL) {
     /* insert name's node at start of list */
     newNode->next = *firstPtr;
     *firstPtr = newNode;
   }
  
   else {
     printf ("Enter old name which new name should preceed, \n");
     printf ("or enter ? if new name should be placed last\n");
     scanf ("%s", oldName);

     if (strcmp (oldName, (*firstPtr)->data) == 0) {
       /* insert name's node at start of list */
       newNode->next = *firstPtr;
       *firstPtr = newNode;
     }
     else {
       /* insert name's node after start of the list */
       
       /* start at beginning of list */
       listPtr = (*firstPtr)->next;  /* the current node to search */
       prevPtr = *firstPtr;          /* the node behind listPtr */
       
       while (listPtr && (strcmp (oldName, listPtr->data) != 0)) {
         prevPtr = listPtr;
         listPtr = prevPtr->next;
       }

       newNode->next = prevPtr->next;
       prevPtr->next = newNode;
     }
   }
   printf ("%s inserted into the list\n\n", newNode->data);
}

void print(struct node * first){
/* pre-condition:  first designates the first node of a list 
  post-condition:  The items on the list are printed from first to last
                   the list itself is unchanged
*/    
  struct node * listElt = first;
  printf ("The names on the list are:\n\n");

  while (listElt) {
    printf ("%s\n", listElt->data);
    listElt = listElt->next;
  }

  printf ("\nEnd of List\n\n");
}

void addNamesFromFile (struct node ** first){
  /* pre-condition:  first designates the first node of a list 
     post-condition:  the program asks the user for a file name
     names from individual lines of the file are inserted
     at the beginning of the original list
  */
  //TESTFILE
 /*
  FILE * file  = fopen("datak.dat", "w");

  fprintf(file, "%s\n", "caleb");
  fprintf(file, "%s\n", "kumar");
  fprintf(file, "%s\n", "brown");
  fprintf(file, "%s\n", "ameer");
  fprintf(file, "%s\n", "tyler");
  fprintf(file, "%s\n", "dk");
  return 0;
*/


  //ask for the filename the user wants to use and store it
  char fileName [50];
  char oldName[strMax];
  struct node * newNode = (struct node *)malloc(sizeof(struct node));
  
  printf ("Function to insert names from a file to the end of the list\n");
  printf ("  Enter file name:  ");
  scanf ("%s",fileName);
  
  FILE * file2  = fopen(fileName, "r"); //open that file

  //fgets(oldName, strMax, file2);

  //check every line in the file until the file is done whilst storing
  //the strings in "oldName"
  while(fgets(oldName, strMax, file2))
    {  
      strcpy (newNode->data, oldName); //copy the string into the newNode
      newNode->next = *first; //newnode points to previous first list item
      *first = newNode; // set the new front of the list
      //make "newNode" NULL and reallocate space for use in another node
      newNode = NULL;
      newNode = (struct node *)malloc(sizeof(struct node));
    }
}

void removeDuplicates (struct node * first) {
  /* pre-condition:  first designates the first node of a list 
     post-condition:  each name on the list appears only once (no duplicate names)
     when duplicates occur on the original list,
     only the first occurence remains after processing
  */
  //declarations for nodes
  struct node * listPtr; 
  struct node * firstPtr;
  struct node * temp;
  struct node * prevPtr;

  firstPtr = first;

  //If the list is empty, simply end procedure
  if (first == NULL)
    {
      printf("list is Null\n");
      return;
    }
  //otherwise remove the duplicates each node
  else
    { 
      //stop when "firstPtr" is last item in list
      while(firstPtr->next !=NULL)
        {
          //set these in order to compared 1st and 2nd list items
          prevPtr = firstPtr;
          listPtr = firstPtr->next;
          //stop when compared "firstptr" to all items in list
          while (listPtr != NULL) 
            {
              //when comparing the last node with the second to last item,
              //if they are equal simply free last node and end function 
              //otherwise just end function
              if(firstPtr->next->next == NULL)
                {
                  if (strcmp(firstPtr->data, listPtr->data) == 0)
                    {
                      temp = listPtr;
                      free(temp);
                      return;
                    }
                  else 
                    {
                      return;
                    }
                }
              //when data are matched, have the previous pointer point
              //to the node after the duplicate
              else if (strcmp(firstPtr->data, listPtr->data) == 0)
                {
                  //temp = listPtr; //when desiring efficient memory allocation
                  prevPtr->next = listPtr->next; 
                  listPtr = listPtr->next;
                  //free(temp);
                }
              //otherwise simply continue through the list
              else 
                {
                  prevPtr = listPtr;
                  listPtr = listPtr->next;
                }
            } // end inner while loop
          firstPtr = firstPtr->next;
        } // end outer while loop        
    } // end else statement
  return;
} // end function

void duplicate (struct node * firstPtr)
/* pre-condition:  first designates the first node of a list 
   post-condition:  each node is duplicated, with the new node inserted
   after the original node
*/
{
  //declarations
  struct node * newNode = (struct node *)malloc(sizeof(struct node));
  struct node * listPtr; 
  struct node * prevPtr;
  struct node * temp;
  listPtr = firstPtr;

  //If the first node is NULL then end procedure
  if (firstPtr == NULL)
    {
      printf("list is Null\n");
      return;
    }
  //otherwise duplicate the nodes
  else
    {
      while (listPtr != NULL) //stop at end of list
        {
          //copy data to "newNode"
          strncpy(newNode->data, listPtr->data, strMax);
          //place duplicate node in list by having previous node point to it
          //and then point the duplicate node point to next node appropratiely
          prevPtr = listPtr;
          listPtr = listPtr->next;
          prevPtr->next = newNode;
          newNode->next = listPtr;
          //empty "newNode" and then malloc to allow for reusage
          newNode = NULL;
          newNode = (struct node *)malloc(sizeof(struct node));
        }
    }

}

