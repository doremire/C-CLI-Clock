#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

const char *numbers[10][7] = {
    {" █████ ",
     "██   ██",
     "██   ██",
     "██   ██",
     " █████ ",
     "       ",
     "       "},
    {"   ██  ",
     "   ██  ",
     "   ██  ",
     "   ██  ",
     "   ██  ",
     "       ",
     "       "},
    {" █████ ",
     "     ██",
     " █████ ",
     "██     ",
     " █████ ",
     "       ",
     "       "},
    {" █████ ",
     "     ██",
     " █████ ",
     "     ██",
     " █████ ",
     "       ",
     "       "},
    {"██   ██",
     "██   ██",
     " █████ ",
     "     ██",
     "     ██",
     "       ",
     "       "},
    {" █████ ",
     "██     ",
     " █████ ",
     "     ██",
     " █████ ",
     "       ",
     "       "},
    {" █████ ",
     "██     ",
     " █████ ",
     "██   ██",
     " █████ ",
     "       ",
     "       "},
    {" █████ ",
     "     ██",
     "     ██",
     "     ██",
     "     ██",
     "       ",
     "       "},
    {" █████ ",
     "██   ██",
     " █████ ",
     "██   ██",
     " █████ ",
     "       ",
     "       "},
    {" █████ ",
     "██   ██",
     " ██████",
     "     ██",
     " █████ ",
     "       ",
     "       "}};

const char *colon[7] = {
    "     ",
    "  ██ ",
    "     ",
    "  ██ ",
    "     ",
    "     ",
    "     "};

void printCentered(const char *str) {
  struct winsize ws;
  ioctl(0, TIOCGWINSZ, &ws);

  int padding = (ws.ws_col - 56) / 2;

  printf("%*s\x1b[1m%s\x1b[0m\n", padding, "", str);
}


int main(int argc, char *argv[]) {
  int selectedColor = 0;
  char *additionalText = "ようこそ / Welcome!!";

  if (argc > 1) {
    if (strcmp(argv[1], "-h") == 0) {
      printf("Usage: %s \n[-c 1-7]\n[-t \"text\"]\n", argv[0]);
      return 0;
    }

    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
        selectedColor = atoi(argv[i + 1]);
      } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
        additionalText = argv[i + 1];
      }
    }
  }

  while (1) {
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    int hour = tm_info->tm_hour;
    int minute = tm_info->tm_min;
    int second = tm_info->tm_sec;

    system("clear");
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    for (int i = 0; i < ws.ws_row / 2 - 5; i++) {
      printf("\n");
    }

    char line[80];
    for (int i = 0; i < 7; i++) {
      sprintf(line, "%s%s %s %s%s %s %s%s", numbers[hour / 10][i],
              numbers[hour % 10][i], colon[i], numbers[minute / 10][i],
              numbers[minute % 10][i], colon[i], numbers[second / 10][i],
              numbers[second % 10][i]);

      if (selectedColor > 0 && selectedColor <= 8) {
        printf("\x1b[%dm", 30 + selectedColor);
      }
      printCentered(line);
      if (selectedColor > 0 && selectedColor <= 8) {
        printf("\x1b[0m");
      }
    }

    // 時刻の下に文字を表示する部分
    int textPadding = (ws.ws_col - strlen(additionalText) + 1) / 2;
    printf("%*s\x1b[1m%s\x1b[0m\n", textPadding, "", additionalText);

    sleep(1);
  }

  return 0;
}