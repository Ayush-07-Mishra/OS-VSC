#include<stdio.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void Zombie(){
    int pid = fork();

    if(pid > 0){
        printf("Chld is created and pid : %d %d\n",pid,getpid());
        sleep(2);
        printf("waiting for child\n");
        wait(NULL); // cleaning up 
    }else if(pid == 0){
        printf("child is exiting\n");
        exit(0); // zombie
    }else{
        printf("INVAILD FORK");
    }
}

void orphan(){

    int pid = fork();

    if(pid > 0){
        printf("child is created and Pid : %d\n",pid);
        sleep(0);
        printf("waiting for child\n");
        exit(0); // orphan
    }else if(pid == 0){
        sleep(2);
        printf("Child is now Orphan\n");
        sleep(2);
    }else{
        printf("INVAILD FORK");
    }
}

void Kill(){
    int pid = fork();
    
    if(pid > 0){
        printf("child is created and Pid : %d\n",pid);
        sleep(2);
        printf("kill the child\n");
        kill(pid,SIGKILL);
        sleep(2);
        printf("killed\n");
    }else if(pid == 0){
        printf("child is working\n");
    }else{
        printf("invaild fork");
    }
}

int main(){
    Zombie();
    orphan();
    Kill();
}