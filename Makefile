CXX = g++
CXXFLAGS = -std=c++11
RM=rm -v

SRCS=exp.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: exp

exp: $(OBJS)
	$(CXX) $(CXXFLAGS) -o exp $(OBJS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) exp