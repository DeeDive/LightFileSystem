//
// Created by Yongqiang Dou on 6/5/2019.
//

#ifndef LIGHTFILESYSTEM_INODE_H
#define LIGHTFILESYSTEM_INODE_H

#include <vector>
using std::vector;
#define MAX_DIRECT_INODE 12

class iNode {
public:
    unsigned int ino;//i节点号
    bool isDir;
    unsigned short i_mode;//文件模式16位，前4位表示文件类型，后12位表示权限
    unsigned long i_size;//文件大小，单位字节
    unsigned long i_time;//文件创建时间
    unsigned long i_mtime;//文件最后修改时间
    unsigned long i_atime;//文件最后一次访问时间
    unsigned long i_blocks;//文件所占块数
    unsigned short i_uid;//所属用户
    unsigned short i_gid;//所属用户组
    int dir_block[MAX_DIRECT_INODE+3]; /* direct & indirect block */
    unsigned short i_count;//引用计数
    unsigned short i_nlink;//与该节点建立链接的文件数(硬链接数)
    iNode(){}

    iNode(unsigned int no, unsigned long size, unsigned long block, vector<unsigned int> zone,bool isDir);

    ~iNode(){}

    void printInfo();
};


#endif //LIGHTFILESYSTEM_INODE_H
