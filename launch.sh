g++ server/main.cpp -o Server -lpthread
g++ client/client1.cpp -o Client1 -lpthread
gnome-terminal -- ./Server 4003
gnome-terminal -- ./Client1 localhost 4003
gnome-terminal -- ./Client1 localhost 4003

