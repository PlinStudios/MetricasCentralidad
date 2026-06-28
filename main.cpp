#include "datasets/Load_IMDB.cpp"
#include "datasets/Load_NetScience.cpp"
#include "AdyacencyList.cpp"

int main(){
    //ALGraph<std::string,int> *grafo = new ALGraph<std::string,int>();
    ALGraph<std::string,float> *grafo = new ALGraph<std::string,float>();
    //LoadIMDB(grafo,300);
    LoadNetScience(grafo);

   /*auto ed = grafo->edges();

    for (auto edge : ed){  
        std::cout << edge->start->element << " <-> " << edge->end->element << " | " << edge->element << std::endl;
    }*/
    

    std::list<Vertex<std::string,float>*> vert =  grafo->vertices();

    std::cout << "Cantidad de vertices:" <<vert.size() << std::endl;
      std::cout << "Energía laplaciana: " << grafo-> laplacianEnergy() << std::endl;
      std::cout << "Laplacian centrality: " << grafo-> laplacianCentrality(*std::begin(vert)) << std::endl;
      std::cout << "Degree centrality: "<< grafo-> degreeCentrality(*std::begin(vert)) << std::endl;

     grafo->updateRank();
      std::cout << "PageRank: " << grafo-> pageRank(*std::begin(vert)) << std::endl;

    std::cout << "Closeness centrality: " << grafo-> closenessCentrality(*std::begin(vert)) << std::endl;
    std::cout << "Harmonic centrality: " << grafo-> harmonicCentrality(*std::begin(vert)) << std::endl;
    std::cout << "Average path length: " << grafo-> averagePathLength() << std::endl;
   //std::cout << "Betweenness centrality: " << grafo-> betweennessCentrality(*std::begin(vert)) << std::endl;
}
