//
// Created by Yongqiang Dou on 6/5/2019.
//

#include "SuperBlock.h"
#include "iNode.h"
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;
using std::ceil;
//为了更加直观操作，采用short去存位图，占用空间稍微大一些，但也不是很大
void SuperBlock::init()
{
    this->blockSize = 5120;//块大小,字节
    this->inode_num = 10240;//i节点数目
    this->inode_remain = 10240;//i节点剩余数目
    this->block_num = 1024 * 100;//磁盘块数
    this->block_remain = 1024 * 100; //磁盘块剩余数
    this->inode_table = this->blockSize*1;
    this->inodemap_pos = ceil(double(this->inode_table + inode_num*sizeof(iNode)) / blockSize) * blockSize;//空闲iNode位图偏移位置
    this->bitmap_pos = ceil(double(inodemap_pos + inode_num*sizeof(short))/blockSize)*blockSize;//空闲块位图偏移位置
    this->first_data_block = ceil(double(bitmap_pos + block_num*sizeof(short)) / blockSize) * blockSize;//第一个数据块的位置
    this->first_data_block_no = first_data_block/blockSize;//第一个数据块的号码
    this->reservedblocks = first_data_block_no;
   // this->blockSize_bit = 10;//块大小占用位数?
    this->maxBytes = 1024*MAX_DIRECT_INODE+0;//文件最大大小 Bytes 需要再加上间接块的大小
    this->block_remain -= first_data_block_no;//去掉保留块
    this->diskSize  = blockSize * block_num;
    //printInfo();
}

void SuperBlock::printInfo()
{
    cout << "i节点数目: " << inode_num << endl;
    cout << "i节点剩余数目: " << inode_remain << endl;
    cout << "磁盘块数: " << block_num << endl;
    cout << "磁盘块剩余数目: " << block_remain << endl;
    cout << "iNode表的存放偏移位置: " << inode_table << endl;
    cout << "iNode节点位图空闲位图偏移位置: " << inodemap_pos << endl;
    cout << "空闲块位图偏移位置: " << bitmap_pos << endl;
    cout << "块大小: " << blockSize << endl;
//    cout << "块大小占用位数: " << blockSize_bit << endl;
    cout << "文件最大大小: " << maxBytes << endl;
    cout << "第一个数据块偏移位置: " << first_data_block << endl;
    cout << "第一个数据块号: " << first_data_block_no << endl;
}