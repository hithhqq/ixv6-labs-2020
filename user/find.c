#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
 
// 格式化路径名，只保留最后一部分（文件或目录名），并根据需要填充空格
char* fmtname(char *path)
{
  //static char buf[DIRSIZ+1]; // 静态缓冲区用于返回结果，DIRSIZ 是定义在 fs.h 中的目录项名的最大长度
  char *p;
 
  // 从字符串末尾向前查找第一个斜杠（'/'），定位到路径的最后一部分的起始位置
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++; // 跳过斜杠，指向路径的最后一部分（文件或目录名）
 
  // 如果路径的最后一部分长度超过 DIRSIZ，直接返回该部分
 // if(strlen(p) >= DIRSIZ)
    return p;
  // 否则，将路径的最后一部分复制到 buf 中，并在其后填充空格，直到达到 DIRSIZ 的长度
  //memmove(buf, p, strlen(p));
  //memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  //return buf;
}
 
// 列出给定路径下的所有文件和目录
void find(char *path,char *file)
{
    char *file2 = file;
   // printf("file2:%s",file2);
  char buf[512], *p; // 缓冲区用于构建完整的文件路径
  int fd; // 文件描述符
  struct dirent de; // 目录项结构
  struct stat st; // 文件状态结构
 
  // 尝试打开给定路径
  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }
 
  // 获取文件或目录的状态信息
  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
 
  // 根据文件类型处理
  switch(st.type){
  case T_FILE: // 单个文件
        //printf("T_FILE\n");
        //printf("file2: %s,  path: %s\n",file2,fmtname(path));
    // 打印文件信息：格式化的文件名，类型，inode编号，大小
    //printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    if (strcmp(file2,fmtname(path))==0){
        //printf("jinlailema?\n");
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/'; // 在路径末尾添加斜杠，为接下来添加文件名做准备
        memmove(p, file, DIRSIZ); // 添加文件名到路径
        p[DIRSIZ] = 0; // 确保字符串以 null 结尾
        printf("%s\n",path);
         //printf("---------------\n");
        break;
    }
    // printf("---------------end of t_file\n");
 
    break;
 
  case T_DIR: // 目录
   // printf("T_DIR: \n");
    // 检查路径长度，避免缓冲区溢出
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    // 构建新的路径
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/'; // 在路径末尾添加斜杠，为接下来添加文件名做准备
    
    // 读取目录项
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue; // 跳过当前目录和父目录的处理
      if(de.inum == 0) // 跳过空目录项
        continue;
      memmove(p, de.name, DIRSIZ); // 添加文件名到路径
      p[DIRSIZ] = 0; // 确保字符串以 null 结尾
      // 获取并打印文件或目录的信息
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      //printf("p: %s\n",p);
      //printf("buf: %s\n",buf);
      //printf("file1: %s\n",fmtname(buf));
      //printf("file2: %s\n",file2);
      find(buf,file2);
      // 打印信息：格式化的文件名，类型，inode编号，大小
      //printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    }
    //printf("---------------end of t_fir\n");
    break;
  }
  close(fd); // 完成后关闭文件描述符
}
 
int main(int argc, char *argv[])
{
  //int i;
 
  // 如果没有指定路径参数，使用当前目录
  if(argc < 3){
    
    exit(0);
  }
  // 否则，对每个给定的路径参数调用 ls 函数
  
    find(argv[1],argv[2]);
  exit(0);
}