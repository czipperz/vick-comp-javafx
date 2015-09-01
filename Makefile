CFLAGS=-std=c++11
LDFLAGS=-lboost_regex
O=out
S=src
CXX=clang++

files=$O/vick-comp-javafx.o   \

all: ${files}
	${CXX} -o $B $^ ${CFLAGS} ${LDFLAGS}

$O/%.o: $S/%.cc $S/%.hh
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS}

$O/%.o: $S/%.cc
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS}
