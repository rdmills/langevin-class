all: test_suite

### Single executable
test_suite:	test_suite.cpp langevin.o ou.o langevin_sde.o mckean_vlasov.o sde.o solver.o euler_maruyama.o boundary_conditions.o 
	g++ -O -o test_suite $^

### Instructions for building the classes						
%.o:	%.cpp %.hpp
	g++ -g -c $<
