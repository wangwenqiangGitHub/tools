//=====================================================================
//
// cpu_occupy.c - 
//
// Created by wwq on 2022/06/23
// Last Modified: 2022/06/23 12:44:03
// 查看系统cpu_num cpu_used mem_used disk_used情况
//=====================================================================
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXBUFSIZE 1024
#define WAIT_SECOND 3       //暂停时间，单位为“秒”
typedef  struct occupy
{
    char		 name[20];
    unsigned int user;
    unsigned int nice;
    unsigned int system;
    unsigned int idle;
} CPU_OCCUPY;

typedef struct PACKED
{
    char name[20];
    long total;
    char name2[20];
    long free;
}MEM_OCCUPY;

float g_cpu_used;
int cpu_num;                    //定义一个全局的int类型cup_num
void  cal_occupy(CPU_OCCUPY *, CPU_OCCUPY *);
void  get_occupy(CPU_OCCUPY *);
void  get_mem_occupy(MEM_OCCUPY *);
float get_io_occupy();
void  get_disk_occupy(char ** reused);
void  getCurrentDownloadRates(long int * save_rate);

static char *handle_name = "cpu mum,cpu used,mem used,disk used\n";

int main()
{
    printf("<%s,%d> BUILD IN %s %s\n",__func__,__LINE__, __DATE__, __TIME__);

    char file_path[128] = {0};
    int ret = GetFileName(file_path,sizeof(file_path));
    if(ret < 0)
    {
        printf("<%s,%d> get filename err.\n", __func__, __LINE__);
        return -1;
    }
    int fd = open(file_path, O_RDWR|O_CREAT);
    if(fd < 2)
    {
        printf("<%s,%d> open err\n", __func__, __LINE__);
        return -1;
    }

    write(fd, handle_name, strlen(handle_name));

    while(1)
    {
        char buf[1024] = {0};
        CPU_OCCUPY ocpu, ncpu;
        MEM_OCCUPY mem;

        //获取cpu核数
        cpu_num = sysconf(_SC_NPROCESSORS_ONLN);

        //获取cpu使用率
        get_occupy(&ocpu);
        sleep(1);
        get_occupy(&ncpu);
        cal_occupy(&ocpu, &ncpu);

        //获取内存使用率
        get_mem_occupy(&mem);

        double using = ((double)(mem.total - mem.free) / mem.total) * 100;

        //获取当前磁盘的使用率
        char t[20] = "";
        char *used = t;
        get_disk_occupy(&used);
 
        sprintf(buf,"%d,%4.2f,%4.2f,%s\n",cpu_num, g_cpu_used, using, used);
        write(fd,buf,strlen(buf));
        sleep(1);
    }
 
    close(fd);
    return 0;
}

int GetFileName(char *file_path,int max_path_len)
{
    int cnt = 0;
    system("mkdir -p ./cpu_info_log \n");
    while(1)
    {
        if(cnt > 10000)
        {
            printf("<%s,%d> Too many filepath \n", __func__, __LINE__);
            return -1;
        }
        memset(file_path, 0, sizeof(max_path_len));
        sprintf(file_path, "./cpu_info_log/cpu_info_%d.csv", cnt++);
        if(0 == access(file_path, F_OK))
        {
            continue;
        } else {
            printf("<%s,%d> get filename[%s]\n", __func__, __LINE__, file_path);
            break;
        }   
    }
    return 0;
}

void  cal_occupy (CPU_OCCUPY *o, CPU_OCCUPY *n)
{
    double od, nd;
    double id, sd;
    double scale;

    od = (double) (o->user + o->nice + o->system + o->idle);   //第一次(用户+优先级+系统+空闲)的时间再赋给od
    nd = (double) (n->user + n->nice + n->system + n->idle);   //第二次(用户+优先级+系统+空闲)的时间再赋给od
    scale = 100.0 / (float)(nd - od);         //100除强制转换(nd-od)之差为float类型再赋给scale这个变量
    id = (double) (n->user - o->user);        //用户第一次和第二次的时间之差再赋给id
    sd = (double) (n->system - o->system);    //系统第一次和第二次的时间之差再赋给sd
    g_cpu_used = ((sd + id) * 100.0) / (nd - od); //((用户+系统)乖100)除(第一次和第二次的时间差)再赋给g_cpu_used
}

void  get_occupy (CPU_OCCUPY *o)
{
    FILE *fd;
    int n;
    char buff[MAXBUFSIZE];

    fd = fopen ("/proc/stat", "r");     //这里只读取stat文件的第一行及cpu总信息，如需获取每核cpu的使用情况，请分析stat文件的接下来几行。
    fgets (buff, sizeof(buff), fd);
    sscanf (buff, "%s %u %u %u %u", o->name, &o->user, &o->nice, &o->system, &o->idle);
    fclose(fd);
}

void get_mem_occupy(MEM_OCCUPY * mem)
{
    FILE * fd;
    char buff[MAXBUFSIZE];

    fd = fopen("/proc/meminfo", "r");
    fgets (buff, sizeof(buff), fd);
    sscanf (buff, "%s %ld", mem->name, &mem->total);
    fgets (buff, sizeof(buff), fd);
    sscanf (buff, "%s %ld", mem->name2, &mem->free);
}

float get_io_occupy()
{
    char cmd[] = "iostat -d -x";
    char buffer[MAXBUFSIZE];
    char a[20];
    float arr[20];
    FILE* pipe = popen(cmd, "r");

    if (!pipe)
    {
        return -1;
    }

    fgets(buffer, sizeof(buffer), pipe);
    fgets(buffer, sizeof(buffer), pipe);
    fgets(buffer, sizeof(buffer), pipe);
    fgets(buffer, sizeof(buffer), pipe);
    sscanf(buffer, "%s %f %f %f %f %f %f %f %f %f %f %f %f %f ", a, &arr[0], &arr[1], &arr[2], &arr[3], &arr[4],
           &arr[5], &arr[6], &arr[7], &arr[8], &arr[9], &arr[10], &arr[11], &arr[12]);

    //printf("%f\n",arr[12]);
    return arr[12];
    pclose(pipe);
}

void get_disk_occupy(char ** reused)
{
    char currentDirectoryPath[ MAXBUFSIZE ];

    getcwd(currentDirectoryPath, MAXBUFSIZE);

    //printf("当前目录：%s\n",currentDirectoryPath);
    char cmd[50] = "df ";
    strcat(cmd, currentDirectoryPath);

    //printf("%s\n",cmd);

    char buffer[MAXBUFSIZE];
    FILE* pipe = popen(cmd, "r");
    char fileSys[20];
    char blocks[20];
    char used[20];
    char free[20];
    char percent[10];
    char moment[20];

    if (!pipe)
    {
        return;
    }

    if (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        sscanf(buffer, "%s %s %s %s %s %s", fileSys, blocks, used, free, percent, moment);
    }

    if (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        sscanf(buffer, "%s %s %s %s %s %s", fileSys, blocks, used, free, percent, moment);
    }

    //printf("desk used:%s\n",percent);
    strcpy(*reused, percent);
    return;
}

void getCurrentDownloadRates(long int * save_rate)
{
    char intface[] = "eth0:";  //这是网络接口名，根据主机配置
    //char intface[] = "wlan0:";
    FILE * net_dev_file;
    char buffer[1024];
    size_t bytes_read;
    char * match;

    if ((net_dev_file = fopen("/proc/net/dev", "r")) == NULL)
    {
        printf("open file /proc/net/dev/ error!\n");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (i++ < 20)
    {
        if (fgets(buffer, sizeof(buffer), net_dev_file) != NULL)
        {
            if (strstr(buffer, intface) != NULL)
            {
                //printf("%d   %s\n",i,buffer);
                sscanf(buffer, "%s %ld", buffer, save_rate);
                break;
            }
        }
    }

    if (i == 20)
    {
        *save_rate = 0.01;
    }

    fclose(net_dev_file);     //关闭文件
    return;
}
