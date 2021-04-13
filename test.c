/* a sequence of procedure calls */
/*
int y;

void add(int x)
{
  y = x+y;
  return;
}

extern void println (int n);

void main(void)
{
  int i, f;

  f = 1;
  for (i = 7; i > 0; i = i-1) {
    y = i;
    add(0);
    add(1);
    add(2);
    add(-5);
    add(2);
    f = f*y;
  }
  println(f);
}
*/

/* nested function calls */
/* a1m2 test 36  problem */
/*
int add(int x, int y)
{
  return x+y;
}

extern void println (int n);

void main(void)
{
  int a, b, c, d, e;
  int i, f;

  f = 1;
  for (i = 7; i > 0; i = i-1) {
    f = f*add(add(1, add(add(2, add(add(i, 0), 1)), -5)), 1);
  }
  println(f);
}
*/


/* assignment: int --> char conversion: locals */
extern void println (int n);

void main(void)
{
  char x;
  int y;

  x = 255;
  y = x;
  println(y);
}






/* more complex conditionals */
/*
int fun(int testFormal){

  return 5;
}

extern void println(int x);

void main(void)
{
  int x, y, res1, res2, k;

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

  k= fun(10);  

  for(k=0;k<10;k=k+1){
    x = 100;
    y = 222;
  }

  k=9;
  while(k>0){
    res1 = 9090;
    k=k-1;
  }

}

*/


/*extern void println(int x);

void main(void) {
    int x, y;

    x = 12;
    y = 21;
    
    if (x > 0) {y = x + 2*y; x = x + 1; } else { y = 3*x - 2; }


    println(x);
}*/


/*
extern void println(int x);

void main(void) {
    int x, y, z, u;
    char c;
    int b[10];

    x = 12345;
    u = 98765;

    y = x;
    z = y;
    println(z);

    z = u;
    y = z;
    println(y);

    for(x=0;x<10;x=x+1){
      if(1>0)
        z = x + y;
    }
}*/
