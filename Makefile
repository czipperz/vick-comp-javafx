CFLAGS=-std=c++11 -lboost_regex
O=out
S=src
CXX=g++

files=$O/vick-comp-javafx.o   \

all: ${files}
	${CXX} -o test $^ ${CFLAGS}

$O/%.o: $S/%.cc $S/%.hh
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS}

$O/%.o: $S/%.cc
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS}
