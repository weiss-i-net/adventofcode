int fac(int n) {
  return (n == 1) ? 1 : n * fac(n - 1);
}

void swap(int& a, int& b) {
  int mem = a;
  a = b;
  b = mem;
}

void heap(int* set, int*& permu, int size, int& n) {
  if (size == 1) {
    for (int i {0}; i < n; i++) {
      //cout << set[i] << " ";
      permu[i] = set[i];
      //cout << permu[i] << " ";
    }
    //cout << permu << endl;
    permu += 5;
  }
  for (int i {0}; i < size; i++) {
    heap(set, permu, size - 1, n);
    if (size % 2 == 1) swap(set[0], set[size - 1]);
    else swap(set[i], set[size - 1]);
  }
}

int* permutations(int* set, int n) {
  int* permu {new int[n * fac(n)]};
  int* pointer = permu;
  heap(set, pointer, n, n);
  return permu;
}
