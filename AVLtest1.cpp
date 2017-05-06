#include "AVLtree.h"
#include <iostream>
#include <functional>
#include <cassert>

template <typename T> class compareInt {
public:
  bool operator()(T *a, T *b) { return *a < *b; }
};

void test1() {
  std::cout << "test1:" << std::endl;
  AVLtree<int, int, compareInt<int> > *tree =
      new AVLtree<int, int, compareInt<int> >();
  assert((*tree).isEmpty());
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  (*tree).insert(&(a[2]), NULL);
  (*tree).insert(&(a[3]), NULL);
  (*tree).insert(&(a[1]), NULL);
  (*tree).print();
  (*tree).remove(&(a[1]));
  (*tree).print();
  (*tree).insert(&(a[1]), NULL);
  (*tree).insert(&(a[9]), NULL);
  (*tree).insert(&(a[9]), NULL);
  (*tree).insert(&(a[4]), NULL);
  (*tree).insert(&(a[3]), NULL);
  (*tree).insert(&(a[8]), NULL);
  (*tree).insert(&(a[7]), NULL);
  (*tree).insert(&(a[0]), NULL);
  (*tree).insert(&(a[5]), NULL);
  (*tree).insert(&(a[6]), NULL);
  (*tree).print();
  (*tree).remove(&(a[0]));
  (*tree).print();
  (*tree).remove(&(a[1]));
  (*tree).print();
  (*tree).remove(&(a[2]));
  (*tree).print();
  (*tree).remove(&(a[3]));
  (*tree).print();
  (*tree).remove(&(a[4]));
  (*tree).print();
  (*tree).remove(&(a[5]));
  (*tree).print();
  (*tree).remove(&(a[6]));
  (*tree).print();
  (*tree).remove(&(a[7]));
  (*tree).print();
  (*tree).remove(&(a[8]));
  (*tree).remove(&(a[9]));
  delete tree;
  std::cout << "end of test1" << std::endl;
}

void test2() {
  std::cout << "test2:" << std::endl;
  AVLtree<int, int, compareInt<int> > *tree =
      new AVLtree<int, int, compareInt<int> >();
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  (*tree).print();
  (*tree).insert(&(a[1]), NULL);
  (*tree).print();
  (*tree).remove(&(a[1]));
  (*tree).print();
  (*tree).insert(&(a[1]), NULL);
  (*tree).print();
  (*tree).insert(&(a[2]), NULL);
  (*tree).print();
  (*tree).remove(&(a[2]));
  (*tree).print();
  (*tree).insert(&(a[2]), NULL);
  (*tree).print();
  (*tree).insert(&(a[0]), NULL);
  (*tree).print();
  (*tree).remove(&(a[0]));
  (*tree).remove(&(a[1]));
  (*tree).remove(&(a[2]));
  (*tree).remove(&(a[3]));
  (*tree).remove(&(a[4]));
  (*tree).remove(&(a[5]));
  (*tree).remove(&(a[6]));
  (*tree).remove(&(a[7]));
  (*tree).remove(&(a[8]));
  (*tree).remove(&(a[9]));
  delete tree;
  std::cout << "end of test2" << std::endl;
}

void test3() {
  std::cout << "test3:" << std::endl;
  AVLtree<int, int, compareInt<int> > *tree =
      new AVLtree<int, int, compareInt<int> >();
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  (*tree).print();
  (*tree).insert(&(a[2]), NULL);
  (*tree).print();
  (*tree).insert(&(a[4]), NULL);
  (*tree).print();
  (*tree).insert(&(a[5]), NULL);
  (*tree).print();
  (*tree).insert(&(a[3]), NULL);
  (*tree).print();
  (*tree).insert(&(a[1]), NULL);
  (*tree).print();
  (*tree).remove(&(a[1]));
  (*tree).print();
  (*tree).remove(&(a[5]));
  (*tree).print();
  (*tree).remove(&(a[3]));
  (*tree).print();
  (*tree).remove(&(a[0]));
  (*tree).remove(&(a[1]));
  (*tree).remove(&(a[2]));
  (*tree).remove(&(a[3]));
  (*tree).remove(&(a[4]));
  (*tree).remove(&(a[5]));
  (*tree).remove(&(a[6]));
  (*tree).remove(&(a[7]));
  (*tree).remove(&(a[8]));
  (*tree).remove(&(a[9]));
  delete tree;
  std::cout << "end of test3" << std::endl;
}

void test4() {
  std::cout << "test4:" << std::endl;
  AVLtree<int, int, compareInt<int> > *tree =
      new AVLtree<int, int, compareInt<int> >();
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  (*tree).print();
  (*tree).insert(&(a[5]), NULL);
  (*tree).insert(&(a[2]), NULL);
  (*tree).insert(&(a[8]), NULL);
  (*tree).insert(&(a[7]), NULL);
  (*tree).print();
  (*tree).remove(&(a[8]));
  (*tree).print();
  (*tree).remove(&(a[7]));
  (*tree).print();
  (*tree).remove(&(a[5]));
  (*tree).print();
  (*tree).remove(&(a[2]));
  delete tree;
  std::cout << "end of test4" << std::endl;
}

void test5() {
  std::cout << "test5:" << std::endl;
  AVLtree<int, int, compareInt<int> > *tree =
      new AVLtree<int, int, compareInt<int> >();
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  tree->insert(&(a[5]), NULL);
  tree->remove(&(a[5]));
  tree->insert(&(a[5]), NULL);
  tree->insert(&(a[2]), NULL);
  tree->remove(&(a[2]));
  tree->remove(&(a[5]));
  tree->insert(&(a[5]), NULL);
  tree->insert(&(a[2]), NULL);
  tree->remove(&(a[5]));
  delete tree;
  std::cout << "end of test5" << std::endl;
}

void test6() {
  std::cout << "test6:" << std::endl;
  AVLtree<int, int, compareInt<int> > *tree =
      new AVLtree<int, int, compareInt<int> >();
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  tree->insert(&(a[5]), NULL);
  delete tree;
  std::cout << "end of test6" << std::endl;
}

void test7() {
  std::cout << "test7:" << std::endl;
  AVLtree<int, int, compareInt<int> > *tree =
      new AVLtree<int, int, compareInt<int> >();
  assert((*tree).isEmpty());
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  (*tree).insert(&(a[2]), NULL);
  (*tree).insert(&(a[3]), NULL);
  (*tree).insert(&(a[1]), NULL);
  (*tree).print();
  (*tree).remove(&(a[1]));
  (*tree).print();
  (*tree).insert(&(a[1]), NULL);
  (*tree).insert(&(a[9]), NULL);
  (*tree).insert(&(a[9]), NULL);
  (*tree).insert(&(a[4]), NULL);
  (*tree).insert(&(a[3]), NULL);
  (*tree).insert(&(a[8]), NULL);
  (*tree).insert(&(a[7]), NULL);
  (*tree).insert(&(a[0]), NULL);
  (*tree).insert(&(a[5]), NULL);
  (*tree).insert(&(a[6]), NULL);
  (*tree).print();
  delete tree;
  std::cout << "end of test7" << std::endl;
}

void test8() {
  std::cout << "test8:" << std::endl;
  AVLtree<int, int, compareInt<int> > *tree =
      new AVLtree<int, int, compareInt<int> >();
  assert((*tree).isEmpty());
  delete tree;
  std::cout << "end of test8" << std::endl;
}

void test9() {
  std::cout << "test9:" << std::endl;
  AVLtree<int, int, compareInt<int> > *tree =
      new AVLtree<int, int, compareInt<int> >();
  assert((*tree).isEmpty());
  int a[100];
  for (int i = 0; i < 100; ++i) {
    a[i] = i;
  }
  for (int i = 3; i < 100; i += 3) {
    tree->insert(&a[i], NULL);
  }
  for (int i = 2; i < 100; i += 2) {
    tree->insert(&a[i], NULL);
  }
  int b[5000];
  for (int i = 0; i < 5000; ++i) {
    b[i] = i;
  }
  for (int i = 2; i < 5000; i += 2) {
    tree->insert(&b[i], NULL);
  }
  for (int i = 2; i < 5000; i += 2) {
    tree->remove(&b[i]);
  }
  for (int i = 2; i < 5000; i += 2) {
    tree->insert(&b[i], NULL);
  }
  delete tree;
  std::cout << "end of test9" << std::endl;
}

void test10() {
  std::cout << "test10:" << std::endl;
  AVLtree<int, int, compareInt<int> > *tree =
      new AVLtree<int, int, compareInt<int> >();
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  tree->insert(&a[0],NULL);
  tree->insert(&a[1],NULL);
  tree->insert(&a[2],NULL);
  tree->insert(&a[3],NULL);
  tree->insert(&a[4],NULL);
  tree->insert(&a[5],NULL);
  tree->insert(&a[6],NULL);
  tree->insert(&a[7],NULL);
  tree->insert(&a[8],NULL);
  tree->remove(&a[3]);
  tree->remove(&a[4]);
  tree->remove(&a[5]);
  tree->remove(&a[6]);
  delete tree;
  std::cout << "end of test10" << std::endl;
}

void test11() {
  std::cout << "test11:" << std::endl;
  AVLtree<int, int, compareInt<int> > *tree =
      new AVLtree<int, int, compareInt<int> >();
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  tree->insert(&a[0],NULL);
  tree->insert(&a[1],NULL);
  tree->insert(&a[2],NULL);
  tree->insert(&a[3],NULL);
  tree->insert(&a[4],NULL);
  tree->remove(&a[2]);
  delete tree;
  std::cout << "end of test11" << std::endl;
}

void test12() {
  std::cout << "test12:" << std::endl;
  AVLtree<int, int, compareInt<int> > *tree1 =
      new AVLtree<int, int, compareInt<int> >();
  AVLtree<int, int, compareInt<int> > *tree2 =
      new AVLtree<int, int, compareInt<int> >();
  AVLtree<int, int, compareInt<int> > *tree3 = tree1->merge(&tree2);
  delete tree1;
  delete tree2;
  delete tree3;
  std::cout << "end of test12" << std::endl;
}

void test13() {
  std::cout << "test13:" << std::endl;
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  AVLtree<int, int, compareInt<int> > *tree1 =
      new AVLtree<int, int, compareInt<int> >();
      tree1->insert(&a[4],NULL);
  AVLtree<int, int, compareInt<int> > *tree2 =
      new AVLtree<int, int, compareInt<int> >();
  AVLtree<int, int, compareInt<int> > *tree3 = tree1->merge(&tree2);
  tree3->print();
  delete tree3;
  std::cout << "end of test13" << std::endl;
}

void test14() {
  std::cout << "test14:" << std::endl;
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  AVLtree<int, int, compareInt<int> > *tree1 =
      new AVLtree<int, int, compareInt<int> >();
      tree1->insert(&a[4],NULL);
      tree1->insert(&a[5],NULL);
  AVLtree<int, int, compareInt<int> > *tree2 =
      new AVLtree<int, int, compareInt<int> >();
  AVLtree<int, int, compareInt<int> > *tree3 = tree1->merge(&tree2);
  tree3->print();
  delete tree3;
  std::cout << "end of test14" << std::endl;
}

void test15() {
  std::cout << "test15:" << std::endl;
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  AVLtree<int, int, compareInt<int> > *tree1 =
      new AVLtree<int, int, compareInt<int> >();
      tree1->insert(&a[4],NULL);
      tree1->insert(&a[5],NULL);
      tree1->insert(&a[6],NULL);
  AVLtree<int, int, compareInt<int> > *tree2 =
      new AVLtree<int, int, compareInt<int> >();
  AVLtree<int, int, compareInt<int> > *tree3 = tree1->merge(&tree2);
  tree3->print();
  delete tree3;
  std::cout << "end of test15" << std::endl;
}

void test16() {
  std::cout << "test16:" << std::endl;
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  AVLtree<int, int, compareInt<int> > *tree1 =
      new AVLtree<int, int, compareInt<int> >();
      tree1->insert(&a[4],NULL);
      tree1->insert(&a[5],NULL);
      tree1->insert(&a[6],NULL);
      tree1->insert(&a[7],NULL);
      tree1->insert(&a[8],NULL);
  AVLtree<int, int, compareInt<int> > *tree2 =
      new AVLtree<int, int, compareInt<int> >();
  AVLtree<int, int, compareInt<int> > *tree3 = tree1->merge(&tree2);
  tree3->print();
  delete tree3;
  std::cout << "end of test16" << std::endl;
}

void test17() {
  std::cout << "test17:" << std::endl;
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  AVLtree<int, int, compareInt<int> > *tree1 =
      new AVLtree<int, int, compareInt<int> >();
      tree1->insert(&a[4],NULL);
      tree1->insert(&a[5],NULL);
      tree1->insert(&a[6],NULL);
      tree1->insert(&a[7],NULL);
      tree1->insert(&a[8],NULL);
  AVLtree<int, int, compareInt<int> > *tree2 =
      new AVLtree<int, int, compareInt<int> >();
      tree2->insert(&a[1],NULL);
  AVLtree<int, int, compareInt<int> > *tree3 = tree1->merge(&tree2);
  tree3->print();
  delete tree3;
  std::cout << "end of test17" << std::endl;
}

void test18() {
  std::cout << "test18:" << std::endl;
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  AVLtree<int, int, compareInt<int> > *tree1 =
      new AVLtree<int, int, compareInt<int> >();
      tree1->insert(&a[4],NULL);
      tree1->insert(&a[5],NULL);
      tree1->insert(&a[6],NULL);
      tree1->insert(&a[7],NULL);
      tree1->insert(&a[8],NULL);
  AVLtree<int, int, compareInt<int> > *tree2 =
      new AVLtree<int, int, compareInt<int> >();
      tree2->insert(&a[1],NULL);
      tree2->insert(&a[2],NULL);
      tree2->insert(&a[3],NULL);
  AVLtree<int, int, compareInt<int> > *tree3 = tree1->merge(&tree2);
  tree3->print();
  delete tree3;
  std::cout << "end of test18" << std::endl;
}

void test19() {
  std::cout << "test19:" << std::endl;
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  AVLtree<int, int, compareInt<int> > *tree1 =
      new AVLtree<int, int, compareInt<int> >();
  AVLtree<int, int, compareInt<int> > *tree2 =
      new AVLtree<int, int, compareInt<int> >();
      tree2->insert(&a[1],NULL);
  AVLtree<int, int, compareInt<int> > *tree3 = tree1->merge(&tree2);
  tree3->print();
  delete tree3;
  std::cout << "end of test19" << std::endl;
}

int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();
  test11();
  test12();
  test13();
  test14();
  test15();
  test16();
  test17();
  test18();
  test19();
  return 0;
}
