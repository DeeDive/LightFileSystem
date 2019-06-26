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
    cout << "i�ڵ��: " << ino << endl;
    cout << "�ļ���С����λ�ֽ�: " << i_size << endl;
    cout << "�ļ�����ʱ��: " << i_time << endl;
    cout << "�ļ�����޸�ʱ��: " << i_mtime << endl;
    cout << "�ļ����һ�η���ʱ��: " << i_atime << endl;
    cout << "�ļ���ռ����: " << i_blocks << endl;
    cout << "�����û�: " << i_uid << endl;
    cout << "�����û���: " << i_gid << endl;
    cout << "���ü���: " << i_count << endl;
    cout << "��ýڵ㽨�����ӵ��ļ���(Ӳ������): " << i_nlink << endl;
}