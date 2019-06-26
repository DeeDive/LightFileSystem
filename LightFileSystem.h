//
// Created by Yongqiang Dou on 6/5/2019.
//

#ifndef LIGHTFILESYSTEM_LIGHTFILESYSTEM_H
#define LIGHTFILESYSTEM_LIGHTFILESYSTEM_H

#include <bits/stdc++.h>
#include "SuperBlock.h"
#include "iNode.h"
#include "dir.h"
using namespace std;
class LightFileSystem {
    static const string diskfile;
private:
    FILE * fileDisk;
    SuperBlock superBlk;
    iNode rootInode;
    short inodeMap[10240];
    short blkmap[102400];
    Dir rootDir;
    Dir * curr_dir;
    unsigned curr_dir_blk_no;
    unsigned curr_dir_ino;
    unsigned root_block_pos;
public:
    LightFileSystem();
    ~LightFileSystem();
    string cmdParseAndRun(string cmd);
    void splitString(const string& s,vector<string> &v,const string& c);

    template<typename T> void seekAndGet(unsigned long pos, T &item);//定位指针并读取
    template<typename T> void seekAndSave(unsigned long pos, T &item);//定位指针并存储
    int alloc_inode(unsigned long size, iNode &node,bool isDir);//申请iNode节点,文件大小size单位为Byte
    int alloc_blocks(int num, vector<unsigned int> &list); //申请blocks，返回list里面是block 块号
    int free_inode(iNode &inode);
    int free_blocks(vector<int> &blocks_list);
    int readBlockIds(iNode inode, vector<int> &blocks_list);
    unsigned long long getiNodePos(size_t i);
    unsigned long long getBlockPos(size_t i);
    int write_iNodeMap();
    int write_blkmap();
    int write_inode(iNode &node);
    int read_inode(size_t no, iNode &node);
    int write_dir(size_t blockNo, Dir &dir);
    int read_dir(size_t blockNo, Dir &dir);
    int findFileName(string name); //在当前目录下查找文件名，存在返回1，不存在返回0

    //command - string is output
    string cmd_help();

    string cmd_cd(vector<string> &path);
    string cmd_dir();
    string cmd_mkdir(vector<string> &path);
    string cmd_touch(vector<string> &pathToFile); //extra implemented
    string cmd_import(string &src,string &des);
    string cmd_export(string &src,string &des);
    string cmd_more(vector<string> &path);
    string cmd_cp(string &src,string &des);
    string cmd_rm(bool isRecursive,vector<string> &pathToFile);  //rm -r

    //have been already integrated into function cmd_rm()
    string cmd_rm_file(vector<string> &pathToFile);
    string cmd_rm_dir(vector<string> &path);
    string cmd_attrib(); //command dir/ls

    string cmd_find();
    string cmd_xcopy();
    //string cmd_exit();  //automatically exit

    //in the future  - to be implemented
    string cmd_mv();
    //not implemented - only display string yet
    void run();
};


#endif //LIGHTFILESYSTEM_LIGHTFILESYSTEM_H
