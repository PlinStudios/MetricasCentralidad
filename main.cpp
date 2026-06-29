#include "datasets/Load_IMDB.cpp"
#include "datasets/Load_NetScience.cpp"
#include "AdyacencyList.cpp"
#include <chrono>
#include <iostream>

int main(){

    // Experimento 1, Tiempo construccion
    auto inicio = std::chrono::high_resolution_clock::now();
    ALGraph<std::string,int> *grafo = new ALGraph<std::string,int>();
    LoadIMDB(grafo,70);
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();
    std::cout << "Tiempo de construccion Grafo 1 (IMDB): " << duracion << " ms\n";
    inicio =std::chrono::high_resolution_clock::now();
    ALGraph<std::string,float> *grafo2 = new ALGraph<std::string,float>();
    LoadNetScience(grafo2,70);
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();
    std::cout << "Tiempo de construccion Grafo 2 (NetScience): " << duracion << " ms\n";
/*
   auto ed = grafo->edges();

    for (auto edge : ed){  
        std::cout << edge->start->element << " <-> " << edge->end->element << " | " << edge->element << std::endl;
    }
    */

      //std::cout << grafo-> laplacianEnergy() << std::endl;
      std::list<Vertex<std::string,int>*> vert =  grafo->vertices();
      //std::cout << grafo-> laplacianCentrality(*std::begin(vert)) << std::endl;
      std::cout << grafo-> degreeCentrality(*std::begin(vert)) << std::endl;

      //grafo->updateRank();

      //std::cout << grafo-> pageRank(*std::begin(vert)) << std::endl;

    //std::cout << grafo-> closenessCentrality(*std::begin(vert)) << std::endl;
    //std::cout << grafo-> harmonicCentrality(*std::begin(vert)) << std::endl;
   // std::cout << grafo-> averagePathLength() << std::endl;
   int i = 0;
   //grafo2->updateCFC_Centrality();
}
