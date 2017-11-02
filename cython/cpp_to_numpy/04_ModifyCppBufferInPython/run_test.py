from pybuffer import BufferWrapper

x = BufferWrapper()
x.printString()

x[3] = 99
x.printString()

arr = x.get_array()
print(arr)
