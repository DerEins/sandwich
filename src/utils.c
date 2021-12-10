int modulo(int x, int n) {
  if (x < 0) {
    return n + (x % n);
  } else
    return x % n;
}
