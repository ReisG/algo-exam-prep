#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_BUFF_LEN 1000

// Input:
// Winnie, I cannot find the honey. I ate it, Piglet.
// 3263204362 1073741873 0

// Ounput (without new line):
// cat.

void parse_num(unsigned int src, unsigned int* count, unsigned int* n1, unsigned int* n2, unsigned int* n3) {
    unsigned int mask1, mask2, mask3, mask4;

    mask1 = 0b11000000000000000000000000000000;
    mask2 = 0b00111111111100000000000000000000;
    mask3 = 0b00000000000011111111110000000000;
    mask4 = 0b00000000000000000000001111111111;

    *count = (src & mask1) >> 30;
    *n3 = (src & mask2) >> 20;
    *n2 = (src & mask3) >> 10;
    *n1 = (src & mask4);
}

int main(void) {
  char str[MAX_INPUT_BUFF_LEN + 1];
  fgets(str, sizeof(str), stdin);

  unsigned int current_n;
  scanf("%u", &current_n);

  while (current_n != 0) {
    unsigned int count, n1, n2, n3;
    parse_num(current_n, &count, &n1, &n2, &n3);

    unsigned int temp[3] = {n1, n2, n3};
    for (int i = 0; i < count; i++) {
      putchar(str[temp[i]]);
    }

    scanf("%u", &current_n);
  }
  
  return 0;
}