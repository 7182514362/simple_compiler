### not complete, bugs exist

### c like language, supported decl/stmt/expr/type
* int, void, pointer type
* vaiable, function, array declaration
* if, else, while, return statments

### example
* rvlang/example.c
```
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
```
* ast dump
```
TranslationUnitDecl 0x55981cbd6e60
  ArrayDecl 0x55981cbd6f80 'li' int
  FunctionDecl 0x55981cbf08a0 'fib' int
    ParamDecl 0x55981cbefe40 'n' int
    CompoundStmt 0x55981cbf0830
      IfStmt 0x55981cbf00f0
        BinaryExpr 0x55981cbeffe0 '=='
          DeclRefExpr 0x55981cbefed0 'n' 0x55981cbefe40
          Constant 0x55981cbeff90 '1'
        CompoundStmt 0x55981cbf0080
          ReturnStmt 0x55981cbefe00
            Constant 0x55981cbeff40 '1'
      ReturnStmt 0x55981cbf07f0
        BinaryExpr 0x55981cbf0790 '+'
          CallExpr 0x55981cbf0310
            DeclRefExpr 0x55981cbf0140 'fib' 0x55981cbf08a0
            BinaryExpr 0x55981cbf0270 '-'
              DeclRefExpr 0x55981cbf01b0 'n' 0x55981cbefe40
              Constant 0x55981cbf0220 '1'
          CallExpr 0x55981cbf0730
            DeclRefExpr 0x55981cbf0370 'fib' 0x55981cbf08a0
            BinaryExpr 0x55981cbf06b0 '-'
              DeclRefExpr 0x55981cbf03e0 'n' 0x55981cbefe40
              Constant 0x55981cbf0450 '2'
  FunctionDecl 0x55981cbf1460 'factorial' void
    ParamDecl 0x55981cbf0a10 'n' int
    ParamDecl 0x55981cbf0aa0 'b' (int)*
    CompoundStmt 0x55981cbf13f0
      DeclStmt 0x55981cbf09d0
        VarDecl 0x55981cbf0b70 'v' int
        Constant 0x55981cbf0b20 '1'
      WhileStmt 0x55981cbf11e0
        BinaryExpr 0x55981cbf0cd0 '!='
          DeclRefExpr 0x55981cbf0c10 'n' 0x55981cbf0a10
          Constant 0x55981cbf0c80 '0'
        CompoundStmt 0x55981cbf1170
          BinaryExpr 0x55981cbf0ee0 '='
            DeclRefExpr 0x55981cbf0d30 'v' 0x55981cbf0b70
            BinaryExpr 0x55981cbf0e80 '*'
              DeclRefExpr 0x55981cbf0da0 'v' 0x55981cbf0b70
              DeclRefExpr 0x55981cbf0e10 'n' 0x55981cbf0a10
          BinaryExpr 0x55981cbf10f0 '='
            DeclRefExpr 0x55981cbf0f60 'n' 0x55981cbf0a10
            BinaryExpr 0x55981cbf1090 '-'
              DeclRefExpr 0x55981cbf0fd0 'n' 0x55981cbf0a10
              Constant 0x55981cbf1040 '1'
      BinaryExpr 0x55981cbf1360 '='
        UnaryExpr 0x55981cbf12a0 '*'
          DeclRefExpr 0x55981cbf1230 'b' 0x55981cbf0aa0
        DeclRefExpr 0x55981cbf12f0 'v' 0x55981cbf0b70
  FunctionDecl 0x55981cbf27a0 'main' int
    CompoundStmt 0x55981cbf2730
      DeclStmt 0x55981cbf1530
        VarDecl 0x55981cbf1570 'v' int
      DeclStmt 0x55981cbf1610
        VarDecl 0x55981cbf1760 'success' int
        ArraySubscriptExpr 0x55981cbf1710
          DeclRefExpr 0x55981cbf1650 'li' 0x55981cbd6f80
          Constant 0x55981cbf16c0 '1'
      IfStmt 0x55981cbf25d0
        UnaryExpr 0x55981cbf1840 '!'
          DeclRefExpr 0x55981cbf17d0 'success' 0x55981cbf1760
        CompoundStmt 0x55981cbf1ab0
          CallExpr 0x55981cbf1a30
            DeclRefExpr 0x55981cbf1890 'factorial' 0x55981cbf1460
            Constant 0x55981cbf1900 '5'
            UnaryExpr 0x55981cbf19c0 '&'
              DeclRefExpr 0x55981cbf1950 'v' 0x55981cbf1570
        CompoundStmt 0x55981cbf2560
          BinaryExpr 0x55981cbf24e0 '='
            DeclRefExpr 0x55981cbf1b20 'v' 0x55981cbf1570
            CallExpr 0x55981cbf2480
              DeclRefExpr 0x55981cbf23a0 'fib' 0x55981cbf08a0
              Constant 0x55981cbf2410 '5'
      ReturnStmt 0x55981cbf26c0
        DeclRefExpr 0x55981cbf2650 'v' 0x55981cbf1570
```

* generated ir
```
; ModuleID = 'example module'
source_filename = "example module"

@li = private global [5 x i32] [i32 1, i32 2, i32 3, i32 4, i32 5]

define i32 @fib(i32 %n) {
entry:
  %n1 = alloca i32, align 4
  store i32 %n, i32* %n1, align 4
  %0 = load i32, i32* %n1, align 4
  %1 = icmp eq i32 %0, 1
  br i1 %1, label %if.then, label %merge

if.then:                                          ; preds = %entry
  ret i32 1
  br label %merge

merge:                                            ; preds = %if.then, %entry
  %2 = load i32, i32* %n1, align 4
  %3 = sub i32 %2, 1
  %4 = call i32 @fib(i32 %3)
  %5 = load i32, i32* %n1, align 4
  %6 = sub i32 %5, 2
  %7 = call i32 @fib(i32 %6)
  %8 = add i32 %4, %7
  ret i32 %8
}

define void @factorial(i32 %n, i32* %b) {
entry:
  %n1 = alloca i32, align 4
  store i32 %n, i32* %n1, align 4
  %b2 = alloca i32, align 4
  store i32* %b, i32* %b2, align 8
  %v = alloca i32, align 4
  store i32 1, i32* %v, align 4
  br label %while.cond

while.cond:                                       ; preds = %entry
  %0 = load i32, i32* %n1, align 4
  %1 = icmp ne i32 %0, 0
  br i1 %1, label %while.true, label %while.false

while.true:                                       ; preds = %while.cond
  %2 = load i32, i32* %v, align 4
  %3 = load i32, i32* %n1, align 4
  %4 = mul i32 %2, %3
  store i32 %4, i32* %v, align 4
  %5 = load i32, i32* %n1, align 4
  %6 = sub i32 %5, 1
  store i32 %6, i32* %n1, align 4

while.false:                                      ; preds = %while.cond
  %7 = load i32, i32* %v, align 4
  store i32 %7, i32* %b2, align 4
}

define i32 @main() {
entry:
  %v = alloca i32, align 4
  %success = alloca i32, align 4
  %0 = load i32, i32* getelementptr inbounds ([5 x i32], [5 x i32]* @li, i32 0, i32 1), align 4
  store i32 %0, i32* %success, align 4
  %1 = load i32, i32* %success, align 4
  %2 = icmp ne i32 %1, 0
  br i1 %2, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  call void @factorial(i32 5, i32* %v)
  br label %merge

merge:                                            ; preds = %if.else, %if.then
  ret i32* %v

if.else:                                          ; preds = %entry
  %3 = call i32 @fib(i32 5)
  store i32 %3, i32* %v, align 4
  br label %merge
}
```


### TODO
* support lvalue/rvalue semantics 
* support global and local
* support visibility
* support struct