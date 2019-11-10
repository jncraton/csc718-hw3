all: results.txt

results.txt: gmon.out
	gprof linpack_bench > results.txt

gmon.out: linpack_bench
	./linpack_bench

linpack_bench: linpack_bench.cpp
	g++ -pg $< -o $@

clean:
	rm -f linpack_bench gmon.out results.txt