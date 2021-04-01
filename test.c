


/* more complex conditionals */

int a, b, c, d, e, f, g, h, i, j;
int res;

extern void println (int n);

void main(void)
{
  int x;
  char c;
  a = 1; b = 2; c = 3; d = 4; e = 5;
  f = 6; g = 7; h = 8; i = 9; j = 10;

  if (a <= b && b <= c && c <= d && d <= e && 
      !!!(e > f || f > g || g > h || h > i || i > j))
    res = 1111;
  else
    res = 2222;
  println(res);
}


/* simple conditionals */

/*extern void println (int n);

void main(void)
{
  int x, y, res1, res2;

  if (1 > 0)
    res1 = 1111;
  else
    res1 = 2222;
  x = 1;
  y = -1;
  if (x > y)
    res2 = 3333;
  else
    res2 = 4444;
  println(res1);
  println(res2);
}*/



/*extern void println(int x);

void main(void) {
    int x, y;

    x = 12;
    y = 21;
    
    if (x > 0) {y = x + 2*y; x = x + 1; } else { y = 3*x - 2; }


    println(x);
}*/