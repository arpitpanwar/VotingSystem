TEMP_TCP=TCP-IMPL/add-voter-tcp TCP-IMPL/list-candidates-tcp TCP-IMPL/server-tcp TCP-IMPL/vote-count-tcp TCP-IMPL/vote-tcp TCP-IMPL/vote-zero-tcp

EXTRA_TCP=EXTRA/add-voter-tcp EXTRA/list-candidates-tcp EXTRA/server-tcp EXTRA/vote-count-tcp EXTRA/vote-tcp EXTRA/vote-zero-tcp

TEMP_UDP=UDP-IMPL/add-voter-udp UDP-IMPL/list-candidates-udp UDP-IMPL/server-udp UDP-IMPL/vote-count-udp UDP-IMPL/vote-udp UDP-IMPL/vote-zero-udp

TEMP_RMI=RMI-IMPL/add-voter-rpc RMI-IMPL/list-candidates-rpc RMI-IMPL/server-rpc RMI-IMPL/vote-count-rpc RMI-IMPL/vote-rpc RMI-IMPL/vote-zero-rpc RMI-IMPL/votesys.h RMI-IMPL/votesys_svc.c RMI-IMPL/votesys_clnt.c RMI-IMPL/votesys_xdr.c RMI-IMPL/*.o


all: rpc_files tcp_files udp_files extra_files

clean:
	rm -rf $(TEMP_TCP)
	rm -rf $(TEMP_UDP)
	rm -rf $(TEMP_RMI)
	rm -rf $(EXTRA_TCP)

tcp_files: TCP-IMPL/server-tcp.cpp TCP-IMPL/list-candidates-tcp.cpp TCP-IMPL/add-voter-tcp.cpp TCP-IMPL/vote-count-tcp.cpp TCP-IMPL/vote-tcp.cpp TCP-IMPL/vote-zero-tcp.cpp
	g++ -std=c++11 -o TCP-IMPL/server-tcp TCP-IMPL/server-tcp.cpp
	g++ -std=c++11 -o TCP-IMPL/list-candidates-tcp TCP-IMPL/list-candidates-tcp.cpp
	g++ -std=c++11 -o TCP-IMPL/add-voter-tcp TCP-IMPL/add-voter-tcp.cpp
	g++ -std=c++11 -o TCP-IMPL/vote-count-tcp TCP-IMPL/vote-count-tcp.cpp
	g++ -std=c++11 -o TCP-IMPL/vote-tcp TCP-IMPL/vote-tcp.cpp
	g++ -std=c++11 -o TCP-IMPL/vote-zero-tcp TCP-IMPL/vote-zero-tcp.cpp

udp_files: UDP-IMPL/add-voter-udp.cpp UDP-IMPL/list-candidates-udp.cpp UDP-IMPL/server-udp.cpp UDP-IMPL/vote-count-udp.cpp UDP-IMPL/vote-udp.cpp UDP-IMPL/vote-zero-udp.cpp
	g++ -std=c++11 -o UDP-IMPL/server-udp UDP-IMPL/server-udp.cpp
	g++ -std=c++11 -o UDP-IMPL/list-candidates-udp UDP-IMPL/list-candidates-udp.cpp
	g++ -std=c++11 -o UDP-IMPL/add-voter-udp UDP-IMPL/add-voter-udp.cpp
	g++ -std=c++11 -o UDP-IMPL/vote-count-udp UDP-IMPL/vote-count-udp.cpp
	g++ -std=c++11 -o UDP-IMPL/vote-udp UDP-IMPL/vote-udp.cpp
	g++ -std=c++11 -o UDP-IMPL/vote-zero-udp UDP-IMPL/vote-zero-udp.cpp

rpc_files: RMI-IMPL/add-voter-rpc.cpp RMI-IMPL/list-candidates-rpc.cpp RMI-IMPL/server-rpc.cpp RMI-IMPL/vote-count-rpc.cpp RMI-IMPL/vote-rpc.cpp RMI-IMPL/vote-zero-rpc.cpp RMI-IMPL/votesys.x RMI-IMPL/util.cpp
	cd RMI-IMPL && rpcgen votesys.x
	cd RMI-IMPL && g++ -std=c++11 -c util.cpp
	cd RMI-IMPL && gcc -c votesys_xdr.c
	g++ -std=c++11 RMI-IMPL/vote-zero-rpc.cpp RMI-IMPL/votesys_xdr.o RMI-IMPL/util.o RMI-IMPL/votesys_clnt.c -o RMI-IMPL/vote-zero-rpc
	g++ -std=c++11 RMI-IMPL/vote-rpc.cpp RMI-IMPL/votesys_xdr.o RMI-IMPL/util.o RMI-IMPL/votesys_clnt.c -o RMI-IMPL/vote-rpc
	g++ -std=c++11 RMI-IMPL/add-voter-rpc.cpp RMI-IMPL/votesys_xdr.o RMI-IMPL/util.o RMI-IMPL/votesys_clnt.c -o RMI-IMPL/add-voter-rpc
	g++ -std=c++11 RMI-IMPL/list-candidates-rpc.cpp RMI-IMPL/votesys_xdr.o RMI-IMPL/util.o RMI-IMPL/votesys_clnt.c -o RMI-IMPL/list-candidates-rpc
	g++ -std=c++11 RMI-IMPL/vote-count-rpc.cpp RMI-IMPL/votesys_xdr.o RMI-IMPL/util.o RMI-IMPL/votesys_clnt.c -o RMI-IMPL/vote-count-rpc
	g++ -std=c++11 -lnsl -Wno-write-strings RMI-IMPL/server-rpc.cpp RMI-IMPL/votesys_svc.c RMI-IMPL/util.cpp RMI-IMPL/votesys_xdr.c -o RMI-IMPL/server-rpc
	
extra_files: EXTRA/server-tcp.cpp EXTRA/list-candidates-tcp.cpp EXTRA/add-voter-tcp.cpp EXTRA/vote-count-tcp.cpp EXTRA/vote-tcp.cpp EXTRA/vote-zero-tcp.cpp
	g++ -std=c++11 -o EXTRA/server-tcp EXTRA/server-tcp.cpp
	g++ -std=c++11 -o EXTRA/list-candidates-tcp EXTRA/list-candidates-tcp.cpp
	g++ -std=c++11 -o EXTRA/add-voter-tcp EXTRA/add-voter-tcp.cpp
	g++ -std=c++11 -o EXTRA/vote-count-tcp EXTRA/vote-count-tcp.cpp
	g++ -std=c++11 -o EXTRA/vote-tcp EXTRA/vote-tcp.cpp
	g++ -std=c++11 -o EXTRA/vote-zero-tcp EXTRA/vote-zero-tcp.cpp
