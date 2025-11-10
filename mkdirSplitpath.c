#include "types.h"
#include <string.h>
#include <stdlib.h>
// #include<stdio.h>



//make directory
void mkdir(char pathName[]){

    // TO BE IMPLEMENTED

     // base and dir name
    char baseName[64];  // needs less room
    char dirName[128];

    // check if the path name given is empty 

    if (pathName == NULL || strlen(pathName) == 0 || strcmp(pathName, "/") == 0) {
        printf("MKDIR ERROR: no path provided\n");
        return;
    }

   
    struct NODE* Dirparent = splitPath(pathName, baseName, dirName);

    if (!Dirparent) {
        return;
    }

        // create a new directory node
    struct NODE* Dir = (struct NODE*)malloc(sizeof(struct NODE));

    // checking if we already have it
    for (struct NODE *child = Dirparent->childPtr; child; child = child->siblingPtr) {
        if (strcmp(child->name, baseName) == 0) {
            printf("MKDIR ERROR: directory %s already exists\n", pathName);
            return;
}
    }
    

    if (!Dir) {
        printf("MKDIR ERROR: memory allocation failed\n");
        return;
    }

// copy down directory name
    strcpy(Dir->name, baseName);
    Dir->fileType = 'D'; // mark as directory

    Dir->childPtr = NULL; // empty directory
    Dir->parentPtr = Dirparent; // parsent linking (folder will be inside root)

    Dir->siblingPtr = NULL; 



    // check for existing child from parent
    if (Dirparent->childPtr == NULL) {
        Dirparent->childPtr = Dir;
    } else {
        struct NODE* sibling_two = Dirparent->childPtr;
        while (sibling_two->siblingPtr != NULL) {
            sibling_two = sibling_two->siblingPtr;
        }
        sibling_two->siblingPtr = Dir;
    }

    printf("MKDIR SUCCESS: node %s successfully created\n", pathName);
}



//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED SOLUTION EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // YOUR CODE HERE
    //

 extern struct NODE* root;
 extern struct NODE* cwd;

//    // find where the last / was so we can do the splitting 
//     // subtracts using addresses 
//     char *last= strrchr(pathName,'/');
//     int size = last- pathName;

    // check for differnt path cases and check if theres a realtive path that exist
   
    // if it's empty
    if(!pathName||strlen(pathName) == 0){
        strcpy(dirName," ");
        strcpy(baseName," ");
        return NULL;

    }
    // reutrn to CWD if / is missing /RELATIVE PATH
    // last occrance for string 
    if(!strrchr(pathName,'/')){
        strcpy(dirName,"");
        strcpy(baseName,pathName);
        return cwd;
    }
    
    // root
    if (strcmp(pathName, "/") == 0) {
        strcpy(dirName,"/");
        strcpy(baseName,"");

        return root;

    }


    // find where the last / was so we can do the splitting 
    // subtracts using addresses 
    char *last= strrchr(pathName,'/');
    int size = last- pathName;
    
    if(size > 0)
    {
        strncpy(dirName, pathName, size);
        dirName[size] = '\0';
    }
    else
    {
        strcpy(dirName,"/");
    }
    strcpy(baseName, last + 1);



    // new node 
    struct NODE* currentDir;
    // figure out if it's a part of the CWD or root
    if(pathName[0] == '/'&& pathName!=NULL){
        currentDir = root;
    }
    else {
        //cwd
        currentDir = cwd;
    }
    
    // make a copy of dirname
    char newDir[128];
    strcpy(newDir, dirName);

    // token
    char *token = strtok(newDir,"/");

    // traverse the directory path

    while (token != NULL){

        struct NODE *child = currentDir->childPtr;
        // 67??? ;)
        // can't use bool vlaue here so we can use int
        int exist = 6;

        while (child != NULL){
            if(strcmp(child->name, token) == 0){
                currentDir = child;
                exist = 7;
                break;
            }
            child = child->siblingPtr;
        }


        if(exist!=7){
            printf("ERROR: directory %s does not exist\n", token);
            return NULL;
        }

        // move to next dir name

        token = strtok(NULL,"/");
    }

    return currentDir;
}