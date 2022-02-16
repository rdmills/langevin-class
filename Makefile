langevin.o : langevin.cpp langevin.hpp
	g++ -c -O langevin.cpp

sde.o : sde.cpp sde.hpp opts_phys.hpp
	g++ -c -O sde.cpp

mckean_vlasov.o : mckean_vlasov.cpp sde.hpp mckean_vlasov.hpp
	g++ -c -O mckean_vlasov.cpp

boundary_conditions.o : boundary_conditions.cpp boundary_conditions.hpp
	g++ -c -O boundary_conditions.cpp

solver.o : solver.cpp solver.hpp opts_num.hpp
	g++ -c -O solver.cpp 

euler_maruyama.o : euler_maruyama.cpp solver.hpp euler_maruyama.hpp 
	g++ -c -O euler_maruyama.cpp

test_suite.o : test_suite.cpp langevin.hpp sde.hpp mckean_vlasov.hpp boundary_conditions.hpp solver.hpp euler_maruyama.hpp opts_num.hpp opts_phys.hpp
	g++ -c -O test_suite.cpp 

test_suite : langevin.o sde.o mckean_vlasov.o boundary_conditions.o solver.o euler_maruyama.o test_suite.o
	g++ -g -o test_suite langevin.o sde.o mckean_vlasov.o boundary_conditions.o solver.o euler_maruyama.o test_suite.o