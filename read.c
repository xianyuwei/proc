/*************************************************************************
    > File Name: read.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年08月17日 星期五 06时31分25秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){
#if 0
    int fd, size;
    int i = 0;
    char s[] = "Linux Programmer!\n", buffer[80];
    char str[8];
    fd = open("/proc/ethercat/gfar_log", O_RDWR);
    
    read(fd, str, 7);
    printf("---------------------:%s\n", str);
    
    close(fd);
#else
    int user_time = 0, gfar_time = 0, gen_time = 0;
    int result_user_gen = 0, result_user_gfar = 0, result_gen_gfar = 0,
        sum_user_gen = 0, sum_user_gfar = 0, sum_gen_gfar = 0,
        count = 0;
    FILE * gfar_file = NULL, * user_file = NULL, * gen_file = NULL;
    char gfar_file_str[8], user_file_str[80], gen_file_str[8];

    user_file = fopen ("/proc/ethercat/igh_ec_performance_log" , "r");


    if (user_file == NULL) {
            printf("open user_time file error!\n");
            return -1;
    }

    while (fgets(user_file_str, sizeof(user_file_str), user_file) != NULL) {
        printf("---------------------:%s\n", user_file_str);
    }
    fclose (user_file);

#endif
}



