CFLAGS=-std=c++11
LDFLAGS=-lboost_regex
O=out
S=src
CXX=clang++

files=$O/vick-comp-javafx.o   \
      $O/regex.o              \

all: ${files}

$O/%.o: $S/%.cc $S/%.hh
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS}

$O/%.o: $S/%.cc
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS}

clean:
	[ ! -d $O ] || rm -R $O

tags:
	etags `find $S -name '*.cc'`
