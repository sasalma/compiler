/* more complex conditionals */

int fun(int testFormal){
  char localCH;
  int localInt;
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



/*extern void println(int x);

void main(void) {
    int x, y;

    x = 12;
    y = 21;
    
    if (x > 0) {y = x + 2*y; x = x + 1; } else { y = 3*x - 2; }


    println(x);
}*/