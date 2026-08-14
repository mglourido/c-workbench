
void reverse(int sizeS, char *s) {

  int pointerLeft=0;
  int pointerRight=sizeS-1;

  while(pointerLeft<pointerRight){

    char tmp=s[pointerLeft];

    s[pointerLeft]=s[pointerRight];
    s[pointerRight]=tmp;

    pointerLeft++;
    pointerRight--;
  }
}