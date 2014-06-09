FLAG=-DDEBUG -g
all:server client
server:CRecvFile.o CMySocket.o CServerTask.o
	g++ $(FLAG) -o server CRecvFile.o CMySocket.o CServerTask.o
client:CSendFile.o CMySocket.o
	g++ $(FLAG) -o client CSendFile.o CMySocket.o
CMySocket.o:CMySocket.cpp
	g++ $(FLAG) -c  CMySocket.cpp
CServerTask.o:CServerTask.cpp 
	g++ $(FLAG) -c CServerTask.cpp
CSendFile.o:CSendFile.cpp
	g++ $(FLAG) -c CSendFile.cpp

clean:
	rm -rf *.o client server
