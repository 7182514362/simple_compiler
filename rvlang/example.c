
int li[5] = {1, 2, 3, 4, 5};

int fib(int n) {
  if (n == 1) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}

void factorial(int n, int *b) {
  int v = 1;
  while (n != 0) {
    v = v * n;
    n = n - 1;
  }
  *b = v;
}

int main() {
  int v;
  int success = li[1];
  if (!success) {
    factorial(5, &v);
  } else {
    v = fib(5);
  }
  return v;
}