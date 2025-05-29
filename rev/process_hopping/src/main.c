#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int cnt;
pid_t p_buf[0x20];
int chk[0x20] = {61, 9,   8,  125, 83, 38, 20, 21, 37, 62, 40,
                 95, 117, 81, 7,   49, 86, 39, 73, 11, 45, 6,
                 48, 63,  19, 24,  12, 43, 80, 21, 77, 82};
int i_check(pid_t k) {
  if (k == p_buf[2]) {
    return 0;
  }
  if (k == p_buf[0]) {
    return 21;
  }
  if (k == p_buf[0x10]) {
    return 1;
  }
  if (k == p_buf[3]) {
    return 23;
  }
  if (k == p_buf[8]) {
    return 11;
  }
  if (k == p_buf[5]) {
    return 2;
  }
  if (k == p_buf[6]) {
    return 5;
  }
  if (k == p_buf[7]) {
    return 10;
  }
  if (k == p_buf[0x11]) {
    return 3;
  }
  if (k == p_buf[0x19]) {
    return 22;
  }
  if (k == p_buf[0xf]) {
    return 24;
  }
  if (k == p_buf[0x14]) {
    return 9;
  }
  if (k == p_buf[0xe]) {
    return 17;
  }
  if (k == p_buf[0x15]) {
    return 4;
  }
  if (k == p_buf[1]) {
    return 30;
  }
  if (k == p_buf[0xa]) {
    return 18;
  }
  if (k == p_buf[4]) {
    return 20;
  }
  if (k == p_buf[0x1c]) {
    return 19;
  }
  if (k == p_buf[0x1b]) {
    return 8;
  }
  if (k == p_buf[0xb]) {
    return 25;
  }
  if (k == p_buf[0xd]) {
    return 31;
  }
  if (k == p_buf[9]) {
    return 6;
  }
  if (k == p_buf[0x18]) {
    return 7;
  }
  if (k == p_buf[0x16]) {
    return 12;
  }
  if (k == p_buf[0x13]) {
    return 29;
  }
  if (k == p_buf[0xc]) {
    return 26;
  }
  if (k == p_buf[0x1f]) {
    return 15;
  }
  if (k == p_buf[0x1a]) {
    return 16;
  }
  if (k == p_buf[0x17]) {
    return 13;
  }
  if (k == p_buf[0x1d]) {
    return 28;
  }
  if (k == p_buf[0x1e]) {
    return 27;
  }
  if (k == p_buf[0x12]) {
    return 14;
  }
  return 0;
}

char p_check(pid_t k) {
  if (k == p_buf[0]) {
    return 'a';
  }
  if (k == p_buf[0x10]) {
    return 'b';
  }
  if (k == p_buf[2]) {
    return 'A';
  }
  if (k == p_buf[3]) {
    return 'a';
  }
  if (k == p_buf[8]) {
    return 'T';
  }
  if (k == p_buf[5]) {
    return 'K';
  }
  if (k == p_buf[6]) {
    return 'N';
  }
  if (k == p_buf[7]) {
    return 'a';
  }
  if (k == p_buf[0x11]) {
    return 'K';
  }
  if (k == p_buf[0x19]) {
    return 'l';
  }
  if (k == p_buf[0xf]) {
    return 'a';
  }
  if (k == p_buf[0x14]) {
    return 'o';
  }
  if (k == p_buf[0x15]) {
    return 'a';
  }
  if (k == p_buf[1]) {
    return '0';
  }
  if (k == p_buf[0xa]) {
    return '1';
  }
  if (k == p_buf[4]) {
    return 't';
  }
  if (k == p_buf[0x1c]) {
    return 'M';
  }
  if (k == p_buf[0x1b]) {
    return '5';
  }
  if (k == p_buf[0xb]) {
    return 'r';
  }
  if (k == p_buf[0xd]) {
    return 'I';
  }
  if (k == p_buf[9]) {
    return 'u';
  }
  if (k == p_buf[0xe]) {
    return 'x';
  }
  if (k == p_buf[0x18]) {
    return 'n';
  }
  if (k == p_buf[0x16]) {
    return 'a';
  }
  if (k == p_buf[0x13]) {
    return 'B';
  }
  if (k == p_buf[0xc]) {
    return '8';
  }
  if (k == p_buf[0x1f]) {
    return 'O';
  }
  if (k == p_buf[0x1a]) {
    return 'M';
  }
  if (k == p_buf[0x17]) {
    return 'C';
  }
  if (k == p_buf[0x1d]) {
    return '9';
  }
  if (k == p_buf[0x1e]) {
    return 'q';
  }
  if (k == p_buf[0x12]) {
    return 'a';
  }
  return 'p';
}

int main() {
  char buf[0x20];
  printf("FLAG> ");
  fflush(stdout);
  scanf("%31s", buf);
  int status;
  int cnt = 0;
a:
  pid_t pid = fork();
  if (pid == 0) {
    cnt++;
    if (cnt >= 0x20) {
      exit(0);
    }
    goto a;
  } else {
    p_buf[cnt] = pid;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 99) {
      exit(99);
    }
    char t = p_check(pid);
    int i = i_check(pid);
    if ((int)(buf[i] ^ t) != chk[cnt ^ 0x1f]) {
      printf("\nWrong...\n");
      exit(99);
    } else {
      if (cnt == 0) {
        goto b;
      }
      exit(0);
    }
  }
b:
  if (status == 0) {
    printf("\nCorrect!\n");
  }
  return 0;
}
