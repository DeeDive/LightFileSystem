//
// Created by Yongqiang Dou on 6/5/2019.
//
//colored text

#define green cout<<"\33[32m"
#define bold cout<<"\33[1m"
#define regular cout<<"\33[0m"
#define yellow cout<<"\33[33m"
#define magenta cout<<"\33[35m"

#include "LightFileSystem.h"

#include "comm.h"
#include "comm.c"
#include <cstdio>
const string LightFileSystem::diskfile = "disk.bin";

LightFileSystem::LightFileSystem(){
    fileDisk = fopen(diskfile.c_str(), "r+");
    if(!fileDisk)//首次运行，文件不存在
    {
        fileDisk = fopen(diskfile.c_str(),"w+");
        //superblock
        superBlk.init();
        //seekAndSave<SuperBlock>(ios::beg, superBlk);
        //fill the disk with char '1'
        char ch = '9';
        for(unsigned long long i = 0;i<superBlk.diskSize;++i)
            fwrite(&ch,sizeof(char),1,fileDisk); //写入内容使得文件达到目标大小
        fclose(fileDisk);
        fileDisk = fopen(diskfile.c_str(),"r+");
        fwrite(&superBlk,sizeof(SuperBlock),1,fileDisk);
        fflush(fileDisk);
        //inode_map(bitmap)
//        inodeMap = new short[superBlk.inode_num];
//        blkmap = new short[superBlk.block_num];
        //0 -- free ;  1 -- used
        memset(inodeMap,0,sizeof(short)*superBlk.inode_num);
        fseek(fileDisk,superBlk.inodemap_pos,SEEK_SET);
        fwrite(inodeMap,sizeof(short)*superBlk.inode_num,1,fileDisk);
        //block bitmap
        memset(blkmap,0,sizeof(short)*superBlk.block_num);
        for(size_t i = 0;i<superBlk.first_data_block_no;++i)
            blkmap[i]=1;
        fseek(fileDisk,superBlk.bitmap_pos,SEEK_SET);
        fwrite(blkmap,sizeof(short)*superBlk.block_num,1,fileDisk);
        //root directory
        root_block_pos = superBlk.first_data_block;
        if(-1==alloc_inode(sizeof(rootDir),rootInode,true))
            exit(EXIT_FAILURE);
        //write_inode(rootInode); alloc inode已经做了
        rootDir.entry[0].i_node = rootInode.ino;
        rootDir.entry[1].i_node = rootInode.ino;
        rootDir.entry[0].isValid  = rootDir.entry[1].isValid = true;
        write_dir(rootInode.dir_block[0],rootDir);
        assert(rootInode.ino==0);

        assert(rootInode.dir_block[0]==superBlk.first_data_block_no);
        //rootInode.dir_block[0];
        curr_dir = &rootDir;
        curr_dir_blk_no = rootInode.dir_block[0];
        curr_dir_ino = 0;
        fclose(fileDisk);
        fileDisk = fopen(diskfile.c_str(),"r+"); //打开一个可以读写的
    }
    else
    {
        fseek(fileDisk,0,SEEK_SET);
        fread(&superBlk, sizeof(SuperBlock),1,fileDisk);
//        inodeMap = new short[superBlk.inode_num];
//        blkmap = new short[superBlk.block_num];
        fseek(fileDisk,superBlk.inodemap_pos,SEEK_SET);
        fread(inodeMap,sizeof(short)*superBlk.inode_num,1,fileDisk);
        fseek(fileDisk,superBlk.bitmap_pos,SEEK_SET);
        fread(blkmap,sizeof(short)*superBlk.block_num,1,fileDisk);
        fseek(fileDisk,superBlk.inode_table,SEEK_SET);
        fread(&rootInode,sizeof(iNode),1,fileDisk);

        root_block_pos = superBlk.first_data_block;
        read_dir(superBlk.first_data_block_no,rootDir);
        curr_dir = &rootDir;
        curr_dir_blk_no = rootInode.dir_block[0];
        curr_dir_ino=rootInode.ino;
    }
}
LightFileSystem::~LightFileSystem()
{
}
void LightFileSystem::splitString(const string& s,vector<string> &v,const string& c)
{//modified ver
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;

    if(pos2==pos1) //ignore first blank
        pos2 = s.find(c, ++pos1);

    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
    //return v;
}

string LightFileSystem::cmdParseAndRun(string cmd)
{
    string ret;
    vector<string> vec; //splited parameters
    splitString(cmd,vec," ");

    for(auto ele:vec)
        cout<<"vec: "<<ele<<endl;
    cout<<"size = "<<vec[0].size()<<endl;
    if(vec[0]=="cd"){
        if(vec.size()>2)
            return "Invalid Argument";
        else if(vec.size()==1) //no operation
            return "";
        vector<string> path;
        if(vec[1][0]=='/')//绝对路径
            path.push_back("/");
        splitString(vec[1],path,"/");
//        for(auto ele:path)
//            cout<<ele<<endl;
        ret = cmd_cd(path);
    }
    else if(vec[0]=="dir"||vec[0]=="ls")
    {// no extra arguments
        cout<<"dir";
        ret = cmd_dir();
    }
    else if(vec[0]=="mkdir")
    {
        if(vec.size()>2)
            return "Invalid Argument";
        else if(vec.size()==1) //no operation
            return "";
        vector<string> path;
        if(vec[1][0]=='/')//绝对路径
            path.push_back("/");
        splitString(vec[1],path,"/");
//        for(auto ele:path)
//            cout<<ele<<endl;
        ret = cmd_mkdir(path);
    }
    else if(vec[0]=="touch")
    {
        vector<string> path;
        if(vec[1][0]=='/')//绝对路径
            path.push_back("/");
        splitString(vec[1],path,"/");
        ret = cmd_touch(path);
    }
    else if(vec[0]=="import")
    {
        ret = cmd_import(vec[1],vec[2]);
    }
    else if(vec[0]=="export")
    {
        ret =cmd_export(vec[1],vec[2]);
    }
    else if(vec[0]=="cp")
    {
        ret =cmd_cp(vec[1],vec[2]);
    }else if(vec[0]=="help"||vec[0]=="h")
    {
        ret = cmd_help();
    }
    else if(vec[0]=="more")
    {
        vector<string> path;
        if(vec[1][0]=='/')//绝对路径
            path.push_back("/");
        splitString(vec[1],path,"/");
        ret = cmd_more(path);
    }
    else if(vec[0]=="rm")
    {
        if(vec[1]=="-r"){
            vector<string> path;
            if(vec[2][0]=='/')//绝对路径
                path.push_back("/");
            splitString(vec[2],path,"/");
            ret = cmd_rm(true,path);
        }
        else
        {
            vector<string> path;
            if(vec[1][0]=='/')//绝对路径
                path.push_back("/");
            splitString(vec[1],path,"/");
            ret = cmd_rm(false,path);
        }
    }
    else if(vec[0]=="find")
    {
        ;
    }
    return ret;
}


int LightFileSystem::alloc_blocks(int num, vector<unsigned int> &list)
{//not implemented indirect blocks
    if(num>superBlk.block_remain)
        return -1;
    //   fileDisk.seekg(superBlk.bitmap_pos, ios::beg);//挪动到位图位置
//    short blkmap[superBlk.block_num];
//    fileDisk.seekp(superBlk.bitmap_pos,ios::beg);
//    fileDisk.read((char *)&blkmap,sizeof(blkmap));
    int cnt=0;
    for(size_t i =0;i<superBlk.block_num&&cnt<num;++i)
        if(blkmap[i]==0)
        {
            blkmap[i]=1;
            ++cnt;
            list.push_back(i);
        }
    fseek(fileDisk,superBlk.bitmap_pos, SEEK_SET);//挪动到位图位置
    fwrite(blkmap,sizeof(short)*superBlk.block_num,1,fileDisk);
    return 1;
}

//申请iNode节点,size单位为Byte
int LightFileSystem::alloc_inode(unsigned long size, iNode &node,bool isDir)
{
    //最大大小超过限制，iNode节点不足时
    if (size>superBlk.maxBytes || superBlk.inode_remain == 0)
        return -1;
    unsigned int blocks_needed = ceil((double)size / superBlk.blockSize);//需要存储内容的块数
    if(size==0)
        blocks_needed=1;
    int block_node_num = superBlk.blockSize / sizeof(unsigned int);//每块可存的iNode的id的数目
    if (blocks_needed <= MAX_DIRECT_INODE){
        //可以在直接块中放下
    }
    else if (blocks_needed <= (MAX_DIRECT_INODE + block_node_num)){
        //加上一个一次间接块
        blocks_needed += 1;
    }
    else if (blocks_needed <= (MAX_DIRECT_INODE + block_node_num + block_node_num*block_node_num)){
        //加上一个二次间接块
        blocks_needed += 1 +1  + block_node_num;
    }
    else if (blocks_needed <= (MAX_DIRECT_INODE + block_node_num + block_node_num*block_node_num + block_node_num*block_node_num*block_node_num)){
        //加上一个三次间接块
        blocks_needed += 1+1+1 + 2 * block_node_num + block_node_num*block_node_num;
    }
    if (blocks_needed > superBlk.block_remain){
        //超过剩余量
        return -1;
    }

//    fileDisk.seekp(superBlk.inodemap_pos,ios::beg);
//    short inodeMap[superBlk.inode_num];
//    fileDisk.read((char*)&inodeMap,superBlk.inode_num*sizeof(short));
    for(size_t i =0 ;i<superBlk.inode_num;++i)
    {
        if(inodeMap[i]==0)//找到空闲块
        {
            inodeMap[i]=1;
            vector<unsigned> blocks_list;
            if(alloc_blocks(blocks_needed,blocks_list)==-1)
                return -1;
            node = iNode(i,size,blocks_needed,blocks_list,isDir);
            unsigned long long pos = getiNodePos(i);
            fseek(fileDisk,pos,SEEK_SET);
            fwrite(&node,sizeof(iNode),1,fileDisk);
            break;
        }
    }
    //写回inodemap
    fseek(fileDisk,superBlk.inodemap_pos,SEEK_SET);
    fwrite(inodeMap,superBlk.inode_num*sizeof(short),1,fileDisk);
    //更新相应的超级块信息
    superBlk.inode_remain--;
    superBlk.block_remain -= blocks_needed;
    seekAndSave<SuperBlock>(0, superBlk);
    return 1;
}
//读取对应iNode的内容块，不包含间接块
int LightFileSystem::readBlockIds(iNode inode, vector<int> &blocks_list)
{
    for(size_t i =0;i<min(inode.i_blocks,(unsigned long)(MAX_DIRECT_INODE));++i)
        blocks_list.push_back(inode.dir_block[i]);
    if(inode.i_blocks==MAX_DIRECT_INODE+1)
    {
        ;
    }
    else if(inode.i_blocks==MAX_DIRECT_INODE+2)
    {
        ;
    }
    else if(inode.i_blocks==MAX_DIRECT_INODE+3)
    {
        ;
    }
    return 1;
}
int LightFileSystem::free_inode(iNode & inode)
{
    if(inode.isDir)
    {
        Dir free_dir;
        read_dir(inode.dir_block[0],free_dir);
        for(size_t i = 2;i<MAX_DIRENTRY;++i) //不能把..删除掉，.也不用删了
        {
            if(free_dir.entry[i].isValid){
                iNode node;
                read_inode(free_dir.entry[i].i_node,node);
                free_inode(node);
            }
        }
    }
    else
    {
        vector<int> blocks_list;
        readBlockIds(inode,blocks_list);
        inodeMap[inode.ino]=0;
        free_blocks(blocks_list);
        write_iNodeMap();
    }

    return 1;
}
int LightFileSystem::free_blocks(vector<int> &blocks_list)
{
    for(auto ele:blocks_list)
        blkmap[ele]=0;
    write_blkmap();
    return 1;
}
unsigned long long LightFileSystem::getiNodePos(size_t i)
{
    return superBlk.inode_table+i*sizeof(iNode);
}
int LightFileSystem::write_iNodeMap()
{
    fseek(fileDisk,superBlk.inodemap_pos,SEEK_SET);
    fwrite(inodeMap,superBlk.inode_num*sizeof(short),1,fileDisk);
    return 1;
}
int LightFileSystem::write_blkmap()
{
    fseek(fileDisk,superBlk.bitmap_pos,SEEK_SET);//挪动到位图位置
    fwrite(blkmap,sizeof(short)*superBlk.block_num,1,fileDisk);
    return 1;
}
unsigned long long LightFileSystem::getBlockPos(size_t i)
{//给的是真实的直接blockno
    //return superBlk.first_data_block+(i-superBlk.reservedblocks)*sizeof(superBlk.blockSize);
    assert(superBlk.first_data_block+(i-superBlk.reservedblocks)*superBlk.blockSize==i*superBlk.blockSize);
    return  superBlk.first_data_block+(i-superBlk.reservedblocks)*superBlk.blockSize;
}
int LightFileSystem::write_dir(size_t blockNo, Dir &dir)
{
    fseek(fileDisk,getBlockPos(blockNo),SEEK_SET);
    fwrite(&dir,sizeof(Dir),1,fileDisk);
    return 1;
}
int LightFileSystem::read_dir(size_t blockNo, Dir& dir)
{
    fseek(fileDisk,getBlockPos(blockNo),SEEK_SET);
    fread(&dir,sizeof(Dir),1,fileDisk);
    //seekAndGet<Dir>(getBlockPos(blockNo),dir);
    return 1;
}
int LightFileSystem::findFileName(string name)//在当前目录下查找名字
{
    for(size_t i =0;i<MAX_DIRENTRY;++i)
        if(curr_dir->entry[i].isValid&&strcmp(curr_dir->entry[i].name,name.c_str())==0)
            return true;
    return false;
}

int LightFileSystem::read_inode(size_t no, iNode &node)
{
    seekAndGet<iNode>(getiNodePos(no),node);
    return 1;
}

int LightFileSystem::write_inode(iNode &node)
{
    //检查范围
    if (node.ino<1 || node.ino>superBlk.inode_num){
        return -1;
    }
    node.i_mtime = time(nullptr);//修改时间
    node.i_atime = node.i_mtime;//访问时间
    seekAndSave<iNode>(superBlk.inode_table + node.ino*sizeof(iNode), node);
    return 1;
}
template<typename T>
void LightFileSystem::seekAndGet(unsigned long pos, T &item)//定位指针并读取
{
    fseek(fileDisk,pos,SEEK_SET);
    fread(&item,sizeof(T),1,fileDisk);
}
template<typename T>
void LightFileSystem::seekAndSave(unsigned long pos, T& item){
    fseek(fileDisk,pos,SEEK_SET);
    fwrite(&item, sizeof(T),1,fileDisk);
    fflush(fileDisk);//写回文件
}
string LightFileSystem::cmd_more(vector<string> &path)
{
    if(path.size()==0)
        return "";
    vector<string> d;
    for(size_t i =0;i<path.size()-1;++i)
    {
        d.push_back(path[i]);
    }
    cmd_cd(d);
    size_t i;
    for(i = 0;i<MAX_DIRENTRY;++i)
    {
        if(curr_dir->entry[i].isValid&&strcmp(curr_dir->entry[i].name,path[path.size()-1].c_str())==0)
        {
            string fileContent;
            iNode node;
            read_inode(curr_dir->entry[i].i_node,node);
            vector<int> blocks_list;
            readBlockIds(node,blocks_list);
            char content [superBlk.blockSize];
            unsigned long size = node.i_size;
            unsigned long  read_size = 0;
            for (auto block_id : blocks_list){
                if (size > superBlk.blockSize){
                    read_size = superBlk.blockSize;
                    size -= superBlk.blockSize;
                }
                else{
                    read_size = size;
                    size = 0;
                }
                unsigned long pos = block_id*superBlk.blockSize;
                fseek(fileDisk,pos, SEEK_SET);
                fread(content, read_size,1,fileDisk);
                string t(content, content + read_size);
                fileContent+=t;
            }
            return fileContent;
        }
    }
}

string LightFileSystem::cmd_import(string &src,string &des)
{
    //save current dir
    Dir * curr = curr_dir;
    unsigned curr_ino = curr_dir_ino;
    unsigned curr_blk_no = curr_dir_blk_no;

    FILE * fp = fopen(src.c_str(),"r");
    if(!fp)
        return "FILE ERROR IN OPENING "+src;

    //change dir entry
    vector<string> path;
    if(des[0]=='/')//绝对路径
        path.push_back("/");
    splitString(des,path,"/");
    vector<string> d;
    for(size_t i =0;i<path.size()-1;++i)
        d.push_back(path[i]);
    cmd_cd(d);
    if(curr_dir->num_in_use == MAX_DIRENTRY)
    {
        //FULL
        return "FAILED: That dir is full";
    }
    else
    {
        if(findFileName(path[path.size()-1])==1)
            return "Already exists";
        for(size_t i = 0;i<MAX_DIRENTRY;++i)
        {
            if (curr_dir->entry[i].isValid == 0) {
                curr_dir->num_in_use++;
                curr_dir->entry[i].isValid = 1;
                strcpy(curr_dir->entry[i].name,path[path.size()-1].c_str());
                unsigned long srcFileSize = 0;
                fseek(fp, 0L, SEEK_END);
                srcFileSize = ftell(fp);
                iNode node;
                if(-1==alloc_inode(srcFileSize,node,false))
                    return "Inode allocation error";
                curr_dir->entry[i].i_node = node.ino;
                vector<int> blk_list;
                readBlockIds(node,blk_list);
                unsigned long sz = 0;
                char buf[superBlk.blockSize];
                rewind(fp);
                for(auto blk_no:blk_list)
                {
                    if(srcFileSize>superBlk.blockSize)
                    {
                        srcFileSize-=superBlk.blockSize;
                        fread(buf, sizeof(buf),1,fp);
                        fseek(fileDisk,getBlockPos(blk_no),SEEK_SET);
                        fwrite(buf, sizeof(buf),1,fileDisk);
                    }
                    else
                    {
                        fread(buf, srcFileSize,1,fp);
                        fseek(fileDisk,getBlockPos(blk_no),SEEK_SET);
                        fwrite(buf, srcFileSize,1,fileDisk);
                    }
                    fflush(fileDisk);
                }
                write_dir(curr_dir_blk_no,*curr_dir);
                fclose(fp);
                break;
            }
        }
    }
    curr_dir = curr ;
    curr_dir_ino = curr_ino;
    curr_dir_blk_no = curr_blk_no ;
    return "Succeed";
}
string LightFileSystem::cmd_export(string &src,string &des)
{
    //save current dir
    Dir * curr = curr_dir;
    unsigned curr_ino = curr_dir_ino;
    unsigned curr_blk_no = curr_dir_blk_no;

    //change dir entry
    vector<string> path;
    if(src[0]=='/')//绝对路径
        path.push_back("/");
    splitString(src,path,"/");
    vector<string> d;
    for(size_t i =0;i<path.size()-1;++i)
        d.push_back(path[i]);
    cmd_cd(d);

    if(findFileName(path[path.size()-1])==0)
        return "No Such File";
    FILE * fp = fopen(des.c_str(),"w+");
    if(!fp)
        return "FILE ERROR IN OPENING "+src;

        for(size_t i = 0;i<MAX_DIRENTRY;++i)
        {
            if (curr_dir->entry[i].isValid &&strcmp(curr_dir->entry[i].name,path[path.size()-1].c_str())==0)
            {
                iNode node;
                read_inode(curr_dir->entry[i].i_node,node);
                unsigned long srcFileSize = node.i_size;
                vector<int> blk_list;
                readBlockIds(node,blk_list);
                char buf[superBlk.blockSize];
                //rewind(fp);
                for(auto blk_no:blk_list)
                {
                    if(srcFileSize>superBlk.blockSize)
                    {
                        srcFileSize-=superBlk.blockSize;
                        fseek(fileDisk,getBlockPos(blk_no),SEEK_SET);
                        fread(buf, sizeof(buf),1,fileDisk);
                        fwrite(buf, sizeof(buf),1,fp);
                    }
                    else
                    {
                        fseek(fileDisk,getBlockPos(blk_no),SEEK_SET);
                        fread(buf, srcFileSize,1,fileDisk);
                        fwrite(buf, srcFileSize,1,fp);
                    }
                    fflush(fp);
                }
                fclose(fp);
            }
        }
    //recover current dir
    curr_dir = curr ;
    curr_dir_ino = curr_ino;
    curr_dir_blk_no = curr_blk_no ;
    return "Succeed";

}
string LightFileSystem::cmd_rm(bool isRecursive,vector<string> &path)
{
    //bool isRecursive means whether it is a dir or not

    //save current dir
    Dir * curr = curr_dir;
    unsigned curr_ino = curr_dir_ino;
    unsigned curr_blk_no = curr_dir_blk_no;

    //change dir entry
    vector<string> d;
    for(size_t i =0;i<path.size()-1;++i)
    {
        d.push_back(path[i]);
    }
    cmd_cd(d);
    size_t i;
    for(i = 0;i<MAX_DIRENTRY;++i)
    {
        if (curr_dir->entry[i].isValid &&strcmp(curr_dir->entry[i].name,path[path.size()-1].c_str())==0)
        {
            curr_dir->entry[i].isValid=0;
            iNode node;
            read_inode(curr_dir->entry[i].i_node,node);
            if(node.isDir&&isRecursive||!node.isDir){{
                free_inode(node);
                break;
            }
            } else if(node.isDir&&!isRecursive)
                return "cannot remove '"+path[path.size()-1]+"' : Is a dir rather than a file";
        }
    }
    if(i==MAX_DIRENTRY)
        return "No Such File or Directory";
    //recover current dir
    write_dir(curr_dir_blk_no,*curr_dir);
    curr_dir = curr ;
    curr_dir_ino = curr_ino;
    curr_dir_blk_no = curr_blk_no ;
    return "Succeed!";

}
string LightFileSystem::cmd_cp(string &src,string &des)
{
    //save current dir
    Dir * curr = curr_dir;
    unsigned curr_ino = curr_dir_ino;
    unsigned curr_blk_no = curr_dir_blk_no;

    //main idea
    iNode srcNode,desNode;
    vector<int> srcBlkList,desBlkList;

    //change dir entry and find inode
    vector<string> path;
    if(src[0]=='/')//绝对路径
        path.push_back("/");
    splitString(src,path,"/");
    vector<string> d;
    for(size_t i =0;i<path.size()-1;++i)
        d.push_back(path[i]);
    cmd_cd(d);
    if(findFileName(path[path.size()-1])==0)
        return "No Such File";
    for(size_t i = 0;i<MAX_DIRENTRY;++i)
    {
        if (curr_dir->entry[i].isValid &&strcmp(curr_dir->entry[i].name,path[path.size()-1].c_str())==0)
        {
            read_inode(curr_dir->entry[i].i_node,srcNode);
            readBlockIds(srcNode,srcBlkList);
            break;
        }
    }
    //change dir entry and find inode
    path.clear();
    if(des[0]=='/')//绝对路径
        path.push_back("/");
    splitString(des,path,"/");
    d.clear();
    for(size_t i =0;i<path.size()-1;++i)
        d.push_back(path[i]);
    cmd_cd(d);
    if(findFileName(path[path.size()-1])==1)
        return "Dest file already exists";
    for(size_t i = 0;i<MAX_DIRENTRY;++i)
    {
        if (curr_dir->entry[i].isValid==0)
        {
                curr_dir->num_in_use++;
                curr_dir->entry[i].isValid=1;
                strcpy(curr_dir->entry[i].name,path[path.size()-1].c_str());
                if(-1==alloc_inode(srcNode.i_size,desNode,false))
                    return "Alloc Error";
                curr_dir->entry[i].i_node = desNode.ino;
                write_dir(curr_dir_blk_no,*curr_dir);
                readBlockIds(desNode,desBlkList);
                break;
        }
    }

    char buf[superBlk.blockSize];
    unsigned long sz = srcNode.i_size;
    assert(srcBlkList.size()==desBlkList.size());
    for(size_t i =0;i<srcBlkList.size();++i )
    {
        if(sz>superBlk.blockSize)
        {
            sz-=superBlk.blockSize;
            fseek(fileDisk,getBlockPos(srcBlkList[i]),SEEK_SET);
            fread(buf,sizeof(buf),1,fileDisk);
            fseek(fileDisk,getBlockPos(desBlkList[i]),SEEK_SET);
            fwrite(buf,sizeof(buf),1,fileDisk);
        } else
        {
            fseek(fileDisk,getBlockPos(srcBlkList[i]),SEEK_SET);
            fread(buf,sz,1,fileDisk);
            fseek(fileDisk,getBlockPos(desBlkList[i]),SEEK_SET);
            fwrite(buf,sz,1,fileDisk);
        }
    }
    fflush(fileDisk);

    //recover current dir
    curr_dir = curr ;
    curr_dir_ino = curr_ino;
    curr_dir_blk_no = curr_blk_no ;
    return "Succeed!";
}
string LightFileSystem::cmd_touch(vector<string> &pathToFile)
{
    if(pathToFile.size()==0)
        return "";
    vector<string> d;
    for(size_t i =0;i<pathToFile.size()-1;++i)
    {
        d.push_back(pathToFile[i]);
    }
    cmd_cd(d);
    if(curr_dir->num_in_use == MAX_DIRENTRY)
    {
        //FULL
        return "FAILED: That dir is full";
    }
    else
    {
        if(findFileName(pathToFile[pathToFile.size()-1])==1)
            return "Already exists";
        for(size_t i = 0;i<MAX_DIRENTRY;++i)
        {
            if(curr_dir->entry[i].isValid ==0)
            {
                curr_dir->num_in_use++;
                curr_dir->entry[i].isValid=1;
                strcpy(curr_dir->entry[i].name,pathToFile[pathToFile.size()-1].c_str());
                iNode node;
                if(-1==alloc_inode(0,node,false))
                    return "Alloc Error";
                curr_dir->entry[i].i_node = node.ino;
                write_dir(curr_dir_blk_no,*curr_dir);
                return "Succeed!";
            }
        }
    }

}
string LightFileSystem::cmd_dir()
{
    string ret;
    for(size_t i =0;i<MAX_DIRENTRY;++i)
    {
        if(curr_dir->entry[i].isValid)  //区分文件和文件夹，文件夹名后面加一个/区分
        {
            ret+=string(curr_dir->entry[i].name);
            iNode nd;
            fseek(fileDisk,getiNodePos(curr_dir->entry[i].i_node),SEEK_SET);
            fread(&nd,sizeof(iNode),1,fileDisk);
            // assert(curr_dir->entry[i].i_node==0);
            //read_inode(curr_dir->entry[i].i_node,nd);
            if(nd.isDir)
                ret+='/';
            ret+='\n';
        }
    }
    return ret;
}
string LightFileSystem::cmd_mkdir(vector<string> &path) {
    //save current dir
    Dir * curr = curr_dir;
    unsigned curr_ino = curr_dir_ino;
    unsigned curr_blk_no = curr_dir_blk_no;

    if(path.size()==0)
        return "";
    vector<string> d;
    for(size_t i =0;i<path.size()-1;++i)
    {
        d.push_back(path[i]);
    }
    cmd_cd(d);
    Dir newDir;
    if(findFileName(path[path.size()-1])==1)
        return "Same name already exists";
    if(curr_dir->num_in_use==MAX_DIRENTRY)
        return "Failed: Current dir is full.";
    for(size_t i =0;i<MAX_DIRENTRY;++i)
        if(!curr_dir->entry[i].isValid)
        {
            curr_dir->num_in_use++;
            curr_dir->entry[i].isValid=1;
            strcpy(curr_dir->entry[i].name,path[path.size()-1].c_str());
            iNode node;
            alloc_inode(sizeof(Dir),node,true);
            curr_dir->entry[i].i_node = node.ino;
            newDir.entry[0].i_node=node.ino;
            newDir.entry[1].i_node=curr_dir_ino;
            write_dir(node.dir_block[0],newDir);
            write_dir(curr_dir_blk_no,*curr_dir);

            break;
        }
    //recover current dir
    curr_dir = curr ;
    curr_dir_ino = curr_ino;
    curr_dir_blk_no = curr_blk_no ;
    return "Succeed!";
}
string LightFileSystem::cmd_help()
{
    string ret;
    ret += "Welcome to LightFileSystem by Yongqiang Dou!\n\n";
    ret += "help / h\n\tshows this help message\n\n";
    ret += "ls or dir\n\tShow files and subdirectories in current dir\n\n";
    ret += "cd [DIR]\n\tChange working directory.\n\n";
    ret += "more [FILE]\n\tDisplay file content\n\n";
    ret += "rm [-r] [FILE] \n\tremove files or directories\n\n";
    ret += "cp [SRC_FILE] [DES_FILE]\n\tcopy file\n\n";
    ret += "touch [NEW_FILE]\n\tCreate a new file named NEW_FILE\n\n";
    ret += "mkdir [DIR]\n\tCreate a new dir or directories.\n\n";
    ret += "import [SRC_FILE] [DES_FILE]\n\tImport files from hard disk to LightFileSystem.\n\n";
    ret += "export [SRC_FILE] [DES_FILE]\n\tExport files from LightFileSystem to hard disk.\n\n";

    return ret;
}

string LightFileSystem::cmd_cd(vector<string> &path)
{
    if(path.size()==0)
        return "";
    if(path[0]=="/")
    { //绝对路径

        curr_dir = &rootDir;
        curr_dir_blk_no=superBlk.first_data_block_no;
        curr_dir_ino =rootInode.ino;
        for(size_t i = 1;i<path.size();++i)
        {
            size_t j;
            for(j =0 ;j<MAX_DIRENTRY;++j)
                if(curr_dir->entry[j].isValid&&strcmp(curr_dir->entry[j].name,path[i].c_str())==0)
                {
                    iNode nd;
                    read_inode(curr_dir->entry[j].i_node,nd);
                    assert(nd.isDir);
                    //这里目录只占一块，所以直接0
                    Dir tmp;
                    read_dir(nd.dir_block[0],tmp);

                    curr_dir_blk_no=nd.dir_block[0];
                    curr_dir_ino = curr_dir->entry[j].i_node;
                    //要先改变curr_dir_ino的位置，再改变curr_dir的指向
                    curr_dir = new Dir;
                    memcpy(curr_dir,&tmp,sizeof(Dir));

                    break;
                }
            if(j==MAX_DIRENTRY)
                return "PATH ERROR";
        }
    }
    else{ //相对路径
        for(size_t i = 0;i<path.size();++i)
        {
            size_t j;
            for(j =0 ;j<MAX_DIRENTRY;++j)
                if(curr_dir->entry[j].isValid&&strcmp(curr_dir->entry[j].name,path[i].c_str())==0)
                {
                    iNode nd;
                    read_inode(curr_dir->entry[j].i_node,nd);
                    assert(nd.isDir);
                    //这里目录只占一块，所以直接0
                    Dir tmp;
                    read_dir(nd.dir_block[0],tmp);
                    curr_dir_blk_no=nd.dir_block[0];
                    curr_dir_ino = curr_dir->entry[j].i_node;
                    //要先改变curr_dir_ino的位置，再改变curr_dir的指向
                    curr_dir = new Dir;
                    memcpy(curr_dir,&tmp,sizeof(Dir));
                    return "Succeed!";
                }
            if(j==MAX_DIRENTRY)
                return "PATH ERROR";
        }
    }
}
void LightFileSystem::run()
{
    int msgid = createMsgQueue();
    int onlineCli=1; //initial # clients
    char buf[MAX_TEXT] = {0};
    while(1)
    {
        printf("#client: %d\n",onlineCli);
        //check if no clients then exit;
        if(onlineCli==0)
        {
            system("rm -f server_running.lock");
            break;
        }

        printf("Receiving...\n");
        recvMsgQueue(msgid, CLIENT_TYPE, buf);
        if(strcasecmp("client exit", buf) == 0){
            onlineCli--;
            continue;
        }
        else if(strcasecmp("client start", buf) == 0){
            onlineCli++;
            continue;
        }

        printf("client command# %s\n", buf);

        //printf("Please enter# ");
        //deal with clients' commands
        string ret = cmdParseAndRun(string(buf));
        cout<<"ret: "<<ret<<" size = "<<ret.size()<<endl;
        if(ret[ret.size()-1]!='\n')
            ret+='\n';
        //fflush(stdout);
        //fgets(buf,MAX_TEXT,stdin);
        strcpy(buf,ret.c_str());
        sendMsgQueue(msgid, SERVER_TYPE, buf);
        printf("Send done, wait recv...\n");
    }
    destoryMsgQueue(msgid);
}

//int main()
//{
//    LightFileSystem fs;
//    cout<<fs.cmd_dir()<<endl;
//    string cmd;
//    while(getline(cin,cmd)&&cmd!="exit")
//        cout<<fs.cmdParseAndRun(cmd)<<endl;
////    vector<string> pathToFile,touchfile;
////    pathToFile.push_back("mydir");
////    //cout<<fs.cmd_mkdir(pathToFile)<<endl;
////    touchfile.push_back("test");
////    //cout<<fs.cmd_touch(touchfile);
////    cout<<fs.cmd_dir()<<endl;
////    cout<<fs.cmd_cd(pathToFile)<<endl;
////    cout<<fs.cmd_dir()<<endl;
////    pathToFile.clear();
////    pathToFile.push_back("..");
////    cout<<fs.cmd_cd(pathToFile)<<endl;
////    cout<<fs.cmd_dir()<<endl;
//
//
////    vector<string> pathToFile,touchfile;
////    pathToFile.push_back("mydir");
////    touchfile.push_back("test");
////    cout<<fs.cmd_touch(touchfile);
////    cout<<fs.cmd_dir()<<endl;
////
////    cout<<fs.cmd_mkdir(pathToFile)<<endl;
////    cout<<fs.cmd_dir()<<endl;
////    pathToFile.clear();
////    pathToFile.push_back("mydir");
////    cout<<fs.cmd_cd(pathToFile)<<endl;
////    cout<<fs.cmd_dir()<<endl;
//
//    return 0;
//}
