#include<stdio.h>
#include<signal.h>
#include<sys/wait.h>
#include<stdlib.h>
#include <unistd.h>

void Zombie(){
    int pid = fork();

    if(pid > 0){
        printf("Child pid : %d\n",pid);
        sleep(2);
        wait(NULL); // cleaning up
        sleep(2);
    }
    else if(pid == 0){
        printf("child is exiting\n");
        exit(0);   // yaha zombie bana ye baacha
    }else{
        printf("Invaild fork");
    }

}

void Orphan(){
    int pid = fork();

    if(pid >0){
        printf("parent created child pid : %d\n",pid);
        sleep(2);
        exit(0); // yaha usske mummy papa bachhe ko chood gaye
    }else if(pid == 0){
        sleep(2);
        printf("meri mummy mujhe chhod kar chale gai\n");
        printf("mai aabhi anath hu\n");
        sleep(2);
    }else{
        printf("Invaild fork\n");
    }
}

void Kill(){
    int pid = fork();
    
    if(pid >0){
        printf("parent created child pid : %d\n",pid);
        sleep(2);
        printf("bacche ko marna honga aab\n");
        kill(pid,SIGKILL);    // kill
        wait(NULL);
        printf("child killed\n");

    }else if(pid == 0){
            printf("child is working");
            sleep(1);
        

    }else{
        printf("Invaild fork"); 
    }
}

int main(){
    Zombie();
    Orphan();
    Kill();
    return 0;
}