#include "datasets/Load_IMDB.cpp"
#include "datasets/Load_NetScience.cpp"
#include "AdyacencyList.cpp"
#include "metrics.cpp"

int main(){
    ALGraph<std::string,int> *grafo = new ALGraph<std::string,int>();


    // 1. Insertar vértices
auto vA = grafo->insertVertex("A");
auto vB = grafo->insertVertex("B");
auto vC = grafo->insertVertex("C");
auto vD = grafo->insertVertex("D");

grafo->insertEdge(vB, vA, 1); // B conecta con A
grafo->insertEdge(vA, vC, 1); // A conecta con C
grafo->insertEdge(vC, vD, 1); // C conecta con D
  

    

   auto ed = grafo->edges();

    for (auto edge : ed){  
        std::cout << edge->start->element << " <-> " << edge->end->element << " | " << edge->element << std::endl;
    }
    

      //std::cout << grafo-> laplacianEnergy() << std::endl;
      std::list<Vertex<std::string,int>*> vert =  grafo->vertices();
      //std::cout << grafo-> laplacianCentrality(*std::begin(vert)) << std::endl;
      std::cout << degreeCentrality(grafo,*std::begin(vert)) << std::endl;

      //grafo->updateRank();

      //std::cout << grafo-> pageRank(*std::begin(vert)) << std::endl;

    //std::cout << grafo-> closenessCentrality(*std::begin(vert)) << std::endl;
    //std::cout << grafo-> harmonicCentrality(*std::begin(vert)) << std::endl;
   // std::cout << grafo-> averagePathLength() << std::endl;
   std::cout << betweennessCentrality(grafo,*std::begin(vert)) << std::endl;
}
