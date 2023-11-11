CXX = g++
CXXFLAGS = -I./src -I/path/to/openssl/includes

LDFLAGS = -L/path/to/openssl/lib  # Path to OpenSSL libraries
LDLIBS = -lssl -lcrypto  # Link against OpenSSL libraries

all: food_coin_program

# Compile all .cpp files into .o files
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link all .o files into the final executable
food_coin_program: src/block.o src/wallet.o src/transaction.o src/blockchain.o src/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm *.o food_coin_program

# all: block main

# block: ./src/block.cpp
# 	g++ -I/src -c ./src/block.cpp

# main: main.cpp ./src/block.o
# 	g++ -I/src ./src/block.o main.cpp -o food_coin_program

# clean:
# 	rm *.o food_coin_program