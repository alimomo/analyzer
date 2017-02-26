CXX = g++
CPPFLAGS = -g -Wall -std=c++11
LDFLAGS = -std=c++11

src = $(wildcard src/*.cpp)


obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)

EXE = main

analyzer: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

#src/%.d: src/%.cpp
# 	@$(CXX) $(CPPFLAGS) '$(patsubst src/%.cpp,obj/%.o,$<)' $< -MF >$@

.PHONY: clean
clean:
	rm -f $(obj) analyzer

.PHONY: cleandep
	rm -f $($dep)
