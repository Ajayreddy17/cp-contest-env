T ?= 20
INTERFACE_PATH ?= C:/Users/thati/Cp/cp-contest-env/interface

runexe:
	g++ -I$(LIB_CPP) -w -std=gnu++20 -D LOCAL -g -Wall -Wextra -O2 $(INTERFACE_PATH)/gen.cpp -o gen
	g++ -I$(LIB_CPP) -w -std=gnu++20 -D LOCAL -g -Wall -Wextra -O2 $(INTERFACE_PATH)/sol.cpp -o sol
	g++ -I$(LIB_CPP) -w -std=gnu++20 -D LOCAL -g -Wall -Wextra -O2 $(INTERFACE_PATH)/naive.cpp -o naive

runsol:
	g++ -I$(LIB_CPP) -w -std=gnu++20 -D LOCAL -g -Wall -Wextra -O2 $(INTERFACE_PATH)/sol.cpp -o sol

b:
	$(MAKE) runexe
	bash script.sh $(T)

r:
	$(MAKE) runsol
	bash script.sh $(T)