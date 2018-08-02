g++ server/main.cpp -o Server -lpthread
g++ client/client1.cpp -o Client1 -lpthread
g++ client/client2.cpp -o Client2 -lpthread
gnome-terminal -- ./Server 4000
gnome-terminal -- ./Client1 localhost 4000
gnome-terminal -- ./Client2 localhost 4000

