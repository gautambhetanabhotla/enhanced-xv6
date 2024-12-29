#include "user/user.h"
#include "kernel/syscall.h"

char* syscallnames[] = {
  "??", 
  "fork", 
  "exit", 
  "wait", 
  "pipe", 
  "read", 
  "kill", 
  "exec", 
  "fstat", 
  "chdir", 
  "dup", 
  "getpid", 
  "sbrk", 
  "sleep", 
  "uptime", 
  "open", 
  "write", 
  "mknod", 
  "unlink", 
  "link", 
  "mkdir", 
  "close", 
  "getsyscount"
};

int
main(int argc, char *argv[])
{
  if(argc < 3)
  {
    printf("Usage: syscount <syscall number> <program to execute>\n");
    exit(1);
  }
  int syscall_no = atoi(argv[1]);
  if(syscall_no < 0 || syscall_no > NUM_SYSCALLS)
  {
    printf("Invalid syscall number\n");
    exit(1);
  }
  int rc = fork();
  if(rc > 0)
  {
    int pid = wait(0);
    printf("PID %d called %s %d times.\n", pid, syscallnames[syscall_no], getsyscount(syscall_no));
  }
  else if(rc == 0)
  {
    // printf("IN child\n");
    close(1);
    exec(argv[2], argv + 2);
    exit(0);
  }
  else
  {
    printf("fork failed\n");
    exit(1);
  }
  exit(0);
}