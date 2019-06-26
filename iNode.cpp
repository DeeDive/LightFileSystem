//
// Created by Yongqiang Dou on 6/5/2019.
//

#include "iNode.h"
#include <ctime>
#include <iostream>
using std::cout;
using std::endl;
iNode::iNode(unsigned int no, unsigned long size,unsigned long block,vector<unsigned int> zone,bool isDir)
:ino(no),i_size(size),i_blocks(block),isDir(isDir){
    i_time = time(NULL);
    i_atime = i_time;
    i_mtime = i_time;
    i_count = 1;
    i_nlink = 1;
    int index = 0;
    for (auto b_no : zone){
        dir_block[index++] = b_no;
    }
    for (; index < MAX_DIRECT_INODE+3; index++){
        dir_block[index] = -1;
    }
}

void iNode::printInfo()
{
    cout << "i节点号: " << ino << endl;
    cout << "文件大小，单位字节: " << i_size << endl;
    cout << "文件创建时间: " << i_time << endl;
    cout << "文件最后修改时间: " << i_mtime << endl;
    cout << "文件最后一次访问时间: " << i_atime << endl;
    cout << "文件所占块数: " << i_blocks << endl;
    cout << "所属用户: " << i_uid << endl;
    cout << "所属用户组: " << i_gid << endl;
    cout << "引用计数: " << i_count << endl;
    cout << "与该节点建立链接的文件数(硬链接数): " << i_nlink << endl;
}