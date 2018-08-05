g++ server/main.cpp -o Server -lpthread
g++ client/client.cpp -o Client -lpthread
gnome-terminal -- ./Server 4003
gnome-terminal -- ./Client localhost 4003
gnome-terminal -- ./Client localhost 4003

