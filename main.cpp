#include "datasets/Load_IMDB.cpp"
#include "datasets/Load_NetScience.cpp"
#include "AdyacencyList.cpp"

int main(){
    ALGraph<std::string,int> *grafo = new ALGraph<std::string,int>();
    ALGraph<std::string,float> *grafo2 = new ALGraph<std::string,float>();
    LoadIMDB(grafo);
    LoadNetScience(grafo2);
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
    std::cout << grafo-> averagePathLength() << std::endl;
}