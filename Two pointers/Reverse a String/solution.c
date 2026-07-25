
void reverse(int sizeS, char *s) {

  int pointerLeft=0;
  int pointerRight=sizeS-1;

  while(pointerLeft!=pointerRight){

    char temporal=s[pointerLeft];
    
    s[pointerLeft]=s[pointerRight];
    s[pointerRight]=temporal;

    pointerLeft++;
    pointerRight--;
  }
}