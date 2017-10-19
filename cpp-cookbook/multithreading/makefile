.phony: all clean

all: \
	bin \
	bin/00_hello_thread \
	bin/01_thread_barrier \
	bin/02_promise_n_future \
	bin/03_async 

bin:
	mkdir -p bin

bin/00_hello_thread: 00_hello_thread.cpp
	g++ -o $@ $< --std=c++11 -lpthread

bin/01_thread_barrier: 01_thread_barrier.cpp
	g++ -o $@ $< --std=c++11 -lpthread

bin/02_promise_n_future: 02_promise_n_future.cpp
	g++ -o $@ $< --std=c++11 -lpthread

bin/03_async: 03_async.cpp 
	g++ -o $@ $< --std=c++11 -lpthread
