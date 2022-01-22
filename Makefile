langevin.o : langevin.cpp langevin.hpp
	g++ -c -O langevin.cpp

line1d.o : line1d.cpp line1d.hpp
	g++ -c -O line1d.cpp

mckean_vlasov.o : mckean_vlasov.cpp langevin.hpp line1d.hpp
	g++ -c -O mckean_vlasov.cpp langevin.cpp line1d.cpp

mckean_vlasov : mckean_vlasov.o langevin.o line1d.o
	g++ -O -o mckean_vlasov langevin.o line1d.o mckean_vlasov.o