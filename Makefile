langevin.o : langevin.cpp langevin.hpp
	g++ -c -O langevin.cpp

line1d.o : line1d.cpp line1d.hpp
	g++ -c -O line1d.cpp

sde_test_suite : sde_test_suite.cpp langevin.hpp line1d.hpp
	g++ -c -O sde_test_suite.cpp langevin.cpp line1d.cpp

sde_test_suite : sde_test_suite.o langevin.o line1d.o
	g++ -O -o sde_test_suite langevin.o line1d.o sde_test_suite.o