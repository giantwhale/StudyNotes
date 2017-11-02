all: 
	python setup.py build_ext -i
.phony: all

test:
	python run_test.py
.phony: test

clean:
	rm -rf build
	rm -f *so
	rm -f pyfunc.cpp
.phony: clean
