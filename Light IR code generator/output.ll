define dso_local i32 @main() #0 {
  %1 = alloca i32
  %2 = alloca i32
  %3 = alloca i32
  %4 = add i32 0, 0
  store i32 %4, i32* %1
  %5 = add i32 0, 1
  store i32 %5, i32* %2
  br label %L0
L0:
  %6 = load i32, i32* %2
  %7 = add i32 0, 9527
  %8 = icmp slt i32 %6, %7
  br i1 %8, label %L1, label %L2
L1:
  %9 = load i32, i32* %2
  store i32 %9, i32* %3
  br label %L3
L3:
  %10 = load i32, i32* %3
  %11 = add i32 0, 0
  %12 = icmp sgt i32 %10, %11
  br i1 %12, label %L4, label %L5
L4:
  %13 = load i32, i32* %3
  %14 = add i32 0, 2
  %15 = sub i32 %13, %14
  store i32 %15, i32* %3
  br label %L3
L5:
  %16 = load i32, i32* %3
  %17 = add i32 0, 0
  %18 = icmp eq i32 %16, %17
  br i1 %18, label %L6, label %L7
L6:
  %19 = load i32, i32* %1
  %20 = add i32 0, 1
  %21 = add i32 %19, %20
  store i32 %21, i32* %1
  br label %L7
L7:
  %22 = load i32, i32* %2
  %23 = add i32 0, 1
  %24 = add i32 %22, %23
  store i32 %24, i32* %2
  br label %L0
L2:
  %25 = load i32, i32* %1
  ret i32 %25
}
