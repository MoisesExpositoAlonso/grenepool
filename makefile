CXX= g++
CXXFLAGS= -Wall -g -pedantic
OBJS= pool.o
# OBJS= pool.o utils.o
# LIB= -Lhtslib -lhts -lpthread -lz -lm

.c.o:
	$(CXX) -c $(CXXFLAGS) $< -o $@

pool: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS)

# pool: pool.o
# 	$(CXX) $(CXXFLAGS) -o pool pool.o
#
# pool.o: pool.cpp
# 		$(CXX) $(CXXFLAGS) -c pool.cpp


# pool.o utils.o: utils.h
