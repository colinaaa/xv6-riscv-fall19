#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid;
  char buf;
  int ps[2];

  if (argc != 1) {
    fprintf(2, "Usage: pingpong\n");
    exit();
  }
  pipe(ps);

  if (fork() == 0) {
    // child
    pid = getpid();

    read(ps[1], &buf, 1);
    close(ps[1]);
    printf("%d: received ping\n", pid);

    write(ps[0], &buf, 1);
    close(ps[0]);
    exit();
  }

  // parent
  pid = getpid();
  write(ps[1], "a", 1);
  close(ps[1]);

  read(ps[0], &buf, 1);
  close(ps[0]);
  printf("%d: received pong\n", pid);
  exit();
}
