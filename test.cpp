//------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <fstream>
//------------------------------------------------------------------------
#ifdef CASE_C
inline   // if activate this line, a program works
#endif
void func2(int a[81]) {
  int n[6][9][9] = {};
  for (int i = 0; i < 9; i++) {
    int i1 = a[i];
    int i2 = a[i + 9];
    n[0][i1][i2]++;
    n[0][i2][i1]++;
  }
  std::string s1[3];
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 6; i++) {
      s1[j][i] = '0' + n[j][0][i];
    }
  }
}
//------------------------------------------------------------------------
void
func(void){
#ifndef CASE_B
  std::ifstream ifs("test.dat");//with this, the program aborts with SIGILL
#endif
  int a[81];
  func2(a);
}
//------------------------------------------------------------------------
int
main(void) {
  func();
}
//------------------------------------------------------------------------
