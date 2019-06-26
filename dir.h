//
// Created by Yongqiang Dou on 6/5/2019.
//

#ifndef LIGHTFILESYSTEM_DIR_H
#define LIGHTFILESYSTEM_DIR_H
#define MAX_FILENAME_LEN 255
#define MAX_DIRENTRY 18

#include <cstring>
class DirEntry {
public:
    char name[MAX_FILENAME_LEN];
    int i_node;
    bool isValid;
    DirEntry():isValid(0){}
};
class Dir{
public:
    int num_in_use;
    DirEntry entry[MAX_DIRENTRY];
    Dir():num_in_use(2){
        strcpy(entry[0].name,".");
        strcpy(entry[1].name,"..");
        entry[0].isValid=true;
        entry[1].isValid=true;
    }
};

#endif //LIGHTFILESYSTEM_DIR_H
