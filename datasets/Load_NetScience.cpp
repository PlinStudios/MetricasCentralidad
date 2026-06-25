#include "../Graph.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

void LoadNetScience(Graph<std::string,float> *target){
    //abre archivo
    std::ifstream file("datasets/NetScience.net");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    //salta comentarios
    std::string line = "%";
    while (line[0]=='%')
        std::getline(file, line);

    //obtiene cantidad de vertices
    std::stringstream ss(line);
    std::string verts;
    std::getline(ss, verts, ' ');
    std::getline(ss, verts, ' ');

    int vcount = std::stoi(verts);

    //vector para relacionar int a vertex
    std::vector<Vertex<std::string,float>*> vertices = std::vector<Vertex<std::string,float>*>(vcount);

    //vertices
    for (int i=0; i<vcount; i++){
        std::getline(file, line);
        //lee nombre de vertex
        std::stringstream ss(line);
        std::string n;
        std::string name;
        std::getline(ss, n, ' ');
        std::getline(ss, name);

        vertices[i] = target->insertVertex(name.substr(1,name.length()-2));

        //std::cout << '\r' << n << '/' << vcount << ' ' << vertices[i]->element << "\033[K";
    }

    //salta linea
    std::getline(file, line);
    
    //edges
    int count=0;
    int from, to;
    float weight;
    while (file >> from >> to >> weight)
    {
        //crea edge
        count++;
        //std::cout << '\r' << count << " - " << from << " <-> " << to << " | " << weight << "\033[K";
        target->insertEdge(vertices[from-1],vertices[to-1],weight);
    }

    //std::cout << "\r\033[K";
}