CXX= g++
CXXFLAGS= -Wall -g

OBJS= pool.o utils.o

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

pool: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS)

# pool: pool.o
# 	$(CXX) $(CXXFLAGS) -o pool pool.o
#
# pool.o: pool.cpp
# 		$(CXX) $(CXXFLAGS) -c pool.cpp


# pool.o utils.o: utils.h
