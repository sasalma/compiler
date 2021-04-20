/*
 * regalloc-03: register allocation for many variables in a single basic block.
 *
 * In this program none of the variables is live for very long and don't
 * interfere with many other variables, so the register allocator should be
 * able to color the interference graph with little or no spilling.
 */

extern void println(int x);

void main(void) {
  int x01, x02, x03, x04, x05, x06, x07, x08, x09, x10;
  int y01, y02, y03, y04, y05, y06, y07, y08, y09, y10;
  int z01, z02, z03, z04, z05, z06, z07, z08, z09, z10;

  x01 = 1;
  x02 = x01 + 1;
  x03 = x02 + x01;
  x04 = x03 + x02;
  x05 = x04 + x03;
  x06 = x05 + x04;
  x07 = x06 + x05;
  x08 = x07 + x06;
  x09 = x08 + x07;
  x10 = x09 + x08;
  y01 = x10 + x09;
  y02 = y01 + 1;
  y03 = y02 + y01;
  y04 = y03 + y02;
  y05 = y04 + y03;
  y06 = y05 + y04;
  y07 = y06 + y05;
  y08 = y07 + y06;
  y09 = y08 + y07;
  y10 = y09 + y08;
  z01 = y10 + y09;
  z02 = z01 + 1;
  z03 = z02 + z01;
  z04 = z03 + z02;
  z05 = z04 + z03;
  z06 = z05 + z04;
  z07 = z06 + z05;
  z08 = z07 + z06;
  z09 = z08 + z07;
  z10 = z09 + z08;
  
  println(z10);
}





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
/*int add(int x, int y)
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
/*extern void println (int n);

void main(void)
{
  int x, temp4, i, temp6;
  temp4 = x - 1;

x = temp4;

temp6 = i - 1;

i = temp6;

  
  char x;
  int y;

  x = 255;
  y = x;
  println(y);
}*/






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
