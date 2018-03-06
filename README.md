
# SIGILL on MacOS X and GCC

## 概要

* 再現環境
  * macOS High Sierra 10.13.3
  * g++ (Homebrew GCC 7.2.0) 7.2.0
  * 3.3 GHz Intel Core i5

以下のコードを`g++ -march=native -O3`でコンパイル、実行するとSIGILLが出る(`a.out`)。

```test.cpp
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
```

以下は実行結果

```
$  g++ -march=native -O3 test.cpp -o a.out
$ ./a.out
zsh: illegal hardware instruction  ./a.out
```


#＃ 詳細

* コードの中に全く使われない`std::ifstream`の宣言があるが、これを削除するとSIGILLは出ない(`b.out`)。
* `main`関数から二回の関数呼び出しがあるが、最後に呼ばれる関数に`inline`指定をするとSIGILLがでない(`c.out`)。
* `-march=native`を外したり、最適化レベルを下げても発生しない。
* clang++では出ない。
* Linuxだと普通にSIGSEGVが出る
* gdbが言うには`addl   $0x1,0x60(%rsp,%rdx,4) `で止まっているらしい。普通にアクセス違反っぽいんだけど・・・

## 疑問点

* SIGSEGVが出るのはわかるけれど、なぜSIGILLが出るんだろう？
* Macのバグなの？GCCのバグなの？
