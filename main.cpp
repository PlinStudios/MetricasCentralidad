#include "datasets/Load_IMDB.cpp"
#include "datasets/Load_NetScience.cpp"
#include "AdyacencyList.cpp"

int main(){
    ALGraph<std::string,int> *grafo = new ALGraph<std::string,int>();
    LoadIMDB(grafo);

   auto ed = grafo->edges();

    for (auto edge : ed){  
        std::cout << edge->start->element << " <-> " << edge->end->element << " | " << edge->element << std::endl;
    }
    

      //std::cout << grafo-> laplacianEnergy() << std::endl;
      std::list<Vertex<std::string,int>*> vert =  grafo->vertices();
      std::cout << grafo-> laplacianCentrality(*std::begin(vert)) << std::endl;
}