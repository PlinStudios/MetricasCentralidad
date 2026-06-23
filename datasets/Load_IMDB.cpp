#include "../Graph.hpp"
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

void LoadIMDB(Graph<int> *target, int max=INT_MAX){
    //abre archivo
    std::ifstream file("datasets/imdb_edgelist.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    //map para relacionar string a vertex
    std::unordered_map<std::string, Vertex<int>*> vertices;
    
    std::string line;
    //pasa linea que describe parametros
    std::getline(file, line);

    int count=0;
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

        count++;
        if (count > max) break;
        std::cout << '\r' << count << " - " << from << ',' << to << ',' << strength << "\033[K";
        //crea o obtiene vertex
        Vertex<int>* Vfrom;
        auto Ifrom = vertices.find(from);
        if (Ifrom == vertices.end()){
            //si no existe lo crea
            Vfrom = target->insertVertex(0);
            vertices[from] = Vfrom;
        }else
            Vfrom = vertices[from];

        Vertex<int>* Vto;
        auto Ito = vertices.find(to);
        if (Ito == vertices.end()){
            //si no existe lo crea
            Vto = target->insertVertex(0);
            vertices[to] = Vto;
        }else
            Vto = vertices[to];

        //crea edge
        target->insertEdge(Vfrom,Vto,strength);
    }

    std::cout << "\r\033[K";
}