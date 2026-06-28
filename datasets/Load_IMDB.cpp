#include "../Graph.hpp"
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

void LoadIMDB(Graph<std::string,int> *target, int max_vertice=INT_MAX){
    //abre archivo
    std::ifstream file("datasets/imdb_edgelist.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    //map para relacionar string a vertex
    std::unordered_map<std::string, Vertex<std::string,int>*> vertices;
    
    std::string line;
    //pasa linea que describe parametros
    std::getline(file, line);

    int count=0;
    bool willBeAdded = true;
    while (std::getline(file, line))
    {
        //lee edges
        std::stringstream ss(line);

        std::string from;
        std::string to;
        std::string strengthStr;

        std::getline(ss, from, ',');
        std::getline(ss, to, ',');
        std::getline(ss, strengthStr, ',');

        int strength = std::stoi(strengthStr);

        //std::cout << '\r' << count << " - " << from << ',' << to << ',' << strength << "\033[K";
        //crea o obtiene vertex
        willBeAdded = true;
        Vertex<std::string,int>* Vfrom;
        auto Ifrom = vertices.find(from);
        if (Ifrom == vertices.end()){
            //si no existe lo crea
            if (count >=max_vertice){
                willBeAdded = false;
            } else {
                Vfrom = target->insertVertex(from);
                vertices[from] = Vfrom;
                count++;
            }
        }else
            Vfrom = vertices[from];

        Vertex<std::string,int>* Vto;
        auto Ito = vertices.find(to);
        if (Ito == vertices.end()){
            //si no existe lo crea
            if(count >= max_vertice){
                willBeAdded = false;
            } else {
                Vto = target->insertVertex(to);
                vertices[to] = Vto;
                count++;
            }
        }else
            Vto = vertices[to];

        //crea edge
        if(willBeAdded) target->insertEdge(Vfrom,Vto,strength);
    }

    //std::cout << "\r\033[K";
}