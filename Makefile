GCC:=g++
BIN:=socket_can
INC:=./include
SRC:=$(wildcard ./src/*.cpp)
OBJ:=./.obj
LIBS:= -lpthread

main:
	@test -d ./.obj || mkdir ./.obj
	$(GCC) -g $(SRC) -o $(BIN) -I$(INC) $(LIBS)

clean:
	rm -rf socket_can