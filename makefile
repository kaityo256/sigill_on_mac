all: a.out b.out c.out

a.out: test.cpp
	 g++ -march=native -O3 $< -o $@

b.out: test.cpp
	 g++ -march=native -O3 -DCASE_B $< -o $@

c.out: test.cpp
	 g++ -march=native -O3 -DCASE_C $< -o $@

clean:
	rm -f a.out b.out c.out
