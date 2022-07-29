# get next line 
## -Reading a line from a fd is way too tedious-
> 파일을 한 줄씩 읽는 프로그램을 구현하자.

## 1. 프로젝트 소개
-----
파일의 내용을 확인하는 프로그램은 여러 방면에서 쓰인다. 리눅스 환경에서는 cat이라는 명령어를 통해 파일의 내용을 확인할 수 있다.  
이번 프로젝트에서는 가장 간단한 형태의 파일 출력 프로그램을 만들 것이다. 이 프로그램은 파일을 한 줄씩 읽을 것이다. 아무리 긴 파일이라도 한 줄씩 읽을 수 있어야 한다.

## 2. 프로젝트 공용 규칙
-----
+ 프로젝트는 C로 작성되어야 한다.
+ *.c 파일과 *.h 파일은 norminette 규칙에 맞게 작성되어야 한다.
+ 함수는 정의되지 않은 행동과 별개로 예기치 않게 중단되어서 안 된다. segmentation fault, bus error, double free 등등을 일으키면 안 된다.
+ 메모리 누수는 일어나면 안 된다.
+ Makefile을 작성해야 하며 CC로 ```-Wall -Wxtra -Werror``` 플래그를 지정하여 컴파일 되어야 한다. Makefile은 relink 되어서는 안 된다.
  
libft와 같은 규칙이다. 아마 앞으로도 계속 만나게 될 것이다.

## 3. 프로젝트 세부 규칙
-----
+ 파일 디스크립터를 사용하는 get_next_line()이라는 함수를 반복적으로 호출해서 파일을 한 번에 한 줄씩 읽어야 한다.
+ get_next_lien() 함수는 읽은 줄을 반환해야 한다. 에러가 일어나면 NULL을 리턴한다.
+ 파일을 읽을 때와 표준 입력을 읽을 때는 같은 동작을 보여야 한다.
+ 반환하는 라인은 개행(\n)을 포함해야 한다. 단, eof의 경우는 개행을 포함하지 않는다.
+ ```-D BUFFER_SIZE=n``` 컴파일 플래그를 가지고 컴파일 될 것이다. 버퍼사이즈는 평가자에 따라 달라질 수 있다.
  
## 4. 함수
-----
|Function name|get_next_line|
|---|---|
|prototype|char *get_next_line(int fd);|
|Turn in files|get_next_line.c, get_next_line_utils.c, get_next_line.h|
|Return value|Read line: correct behavior, NULL: there is nothing else to read, or an error occurred|
|External functs.|read, malloc, free|
|Description|Write a function that returns a line read from a file descriptor|
