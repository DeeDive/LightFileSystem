//
// Created by Yongqiang Dou on 6/6/2019.
//

#include <bits/stdc++.h>
using namespace std;

#include "SuperBlock.h"
#include "iNode.h"
#include "dir.h"
int main()
{
    Dir d;

    fstream fs("disk.bin",ios::in|ios::out|ios::binary);
    if(!fs)
    {
        fs.open("tmp.txt",ios::out|ios::binary);
        int magicnum=2929292;
        fs.write((char*)&magicnum,sizeof(magicnum));
        cout<<fs.tellp()<<endl;
        magicnum/=100000;
        fs.write((char*)&magicnum,sizeof(magicnum));
        fs.close();
    }
    else
    {
        SuperBlock spblk;
        iNode node;
        fs.read((char*)&spblk,sizeof(spblk));
        //spblk.printInfo();
        short * inodeMap;
        inodeMap = new short[spblk.inode_num];
        fs.seekg(spblk.inodemap_pos,ios::beg);
        fs.read((char*)inodeMap,sizeof(short)*spblk.inode_num);
        printf("end");
//        fs.seekg(spblk.inode_table,ios::beg);
//        fs.read((char*)&node,sizeof(node));
//        fs.seekg(239*spblk.blockSize,ios::beg);
//        fs.read((char*)&d,sizeof(Dir));
        ;
       // node.printInfo();
    }
    return 0;
}