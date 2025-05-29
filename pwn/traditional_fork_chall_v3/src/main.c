// gcc -o ../dist/traditional_fork_chall_v3 ./main.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

long long readline_n(char *buf, int n) {
  char tmp[1];
  long long cnt = 0;
  for (int i = 0; i < n; i++) {
    ssize_t r = read(STDIN_FILENO, tmp, 1);
    if (r == 0) {
      exit(99);
    } else if (r < 0) {
      exit(1);
    }
    if (tmp[0] == '\n') {
      break;
    }
    buf[i] = tmp[0];
    cnt += 1;
  }
  return cnt;
}

void func() {
  char buf[0x100];
  readline_n(buf, 0x200);
  return;
}

int main() {
  while (1) {
    int status;
    pid_t pid = fork();
    if (pid < 0) {
      perror("fork failed");
      exit(1);
    }

    if (pid == 0) {
      func();
      exit(0);
    } else {
      waitpid(pid, &status, 0);
      if (WIFEXITED(status) && WEXITSTATUS(status) == 99) {
        exit(0);
      }
    }
  }
  return 0;
}
