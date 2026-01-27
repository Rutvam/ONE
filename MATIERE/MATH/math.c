int opperateur(int a, int b, char op){
    if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else if (op == '*') {
        return a * b;
    } else if (op == '#') {
        return pow(a, b);
    }
}