#include "datasets/Load_IMDB.cpp"
#include "datasets/Load_NetScience.cpp"
#include "AdyacencyList.cpp"
#include <chrono>
#include <iostream>

int main(){
    bool printBool = false;
    // Experimento 1, Tiempo construccion
    auto inicio = std::chrono::high_resolution_clock::now();
    ALGraph<std::string,int> *grafo = new ALGraph<std::string,int>();
    LoadIMDB(grafo,50);
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Tiempo de construccion Grafo 1 (IMDB): " << duracion << " us\n";
    inicio =std::chrono::high_resolution_clock::now();
    ALGraph<std::string,float> *grafo2 = new ALGraph<std::string,float>();
    LoadNetScience(grafo2,50);
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Tiempo de construccion Grafo 2 (NetScience): " << duracion << " us\n";

    //Experimento 2, Tiempo en calcular Degree Centrality
    inicio =std::chrono::high_resolution_clock::now();
    for(auto v: grafo->vertices()){
        auto aux = grafo->degreeCentrality(v);
        if (printBool)std::cout<< v->element << ": " << aux <<", ";
    }
    std::cout<<"\n\n";
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Degree Centrality Grafo 1 (IMDB): " << duracion << " us\n";
    
    inicio =std::chrono::high_resolution_clock::now();
    for(auto v: grafo2->vertices()){
        auto aux = grafo2->degreeCentrality(v);
        if (printBool) std::cout<< v->element << ": " << aux<<", ";
    }
    std::cout<<"\n\n";
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Degree Centrality Grafo 2 (NetScience): " << duracion << " us\n";


    //Experimento 3, Tiempo en calcular Betweenness Centrality
    inicio =std::chrono::high_resolution_clock::now();
    for(auto v: grafo->vertices()){
        auto aux = grafo->betweennessCentrality(v);
        if (printBool)std::cout<< v->element << ": " << aux <<", ";
    }
    std::cout<<"\n\n";
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Betweenness Centrality Grafo 1 (IMDB): " << duracion << " us\n";

    inicio =std::chrono::high_resolution_clock::now();
    for(auto v: grafo2->vertices()){
        auto aux = grafo2->betweennessCentrality(v);
        if (printBool) std::cout<< v->element << ": " << aux<<", ";
    }
    std::cout<<"\n\n";
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Betweenness Centrality Grafo 2 (NetScience): " << duracion << " us\n";



    //Experimento 4, Tiempo en calcular Closeness Centrality
    inicio =std::chrono::high_resolution_clock::now();
    for(auto v: grafo->vertices()){
        auto aux = grafo->closenessCentrality(v);
        if (printBool)std::cout<< v->element << ": " << aux <<", ";
    }
    std::cout<<"\n\n";
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Closeness Centrality Grafo 1 (IMDB): " << duracion << " us\n";

    inicio =std::chrono::high_resolution_clock::now();
    for(auto v: grafo2->vertices()){
        auto aux = grafo2->closenessCentrality(v);
        if (printBool) std::cout<< v->element << ": " << aux<<", ";
    }
    std::cout<<"\n\n";
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Closeness Centrality Grafo 2 (NetScience): " << duracion << " us\n";



    //Experimento 5, Tiempo en calcular PageRank
    inicio =std::chrono::high_resolution_clock::now();
    grafo->updateRank();
    for(auto v: grafo->vertices()){
        auto aux = grafo->pageRank(v);
        if (printBool)std::cout<< v->element << ": " << aux <<", ";
    }
    std::cout<<"\n\n";
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "PageRank Grafo 1 (IMDB): " << duracion << " us\n";

    inicio =std::chrono::high_resolution_clock::now();
    grafo2->updateRank();
    for(auto v: grafo2->vertices()){
        auto aux = grafo2->pageRank(v);
        if (printBool) std::cout<< v->element << ": " << aux<<", ";
    }
    std::cout<<"\n\n";
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "PageRank Grafo 2 (NetScience): " << duracion << " us\n";



    //Experimento 6, Tiempo en calcular Average Shortest Path
    inicio =std::chrono::high_resolution_clock::now();
    auto aux2 = grafo->averagePathLength();
    if (printBool)std::cout<< "AveragePathLength" << ": " << aux2 <<", ";
    std::cout<<"\n\n";
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Avg Shortest Path Grafo 1 (IMDB): " << duracion << " us\n";

    inicio =std::chrono::high_resolution_clock::now();
    aux2 = grafo2->averagePathLength();
    if (printBool)std::cout<< "AveragePathLength" << ": " << aux2 <<", ";
    std::cout<<"\n\n";
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Avg Shortest Path Grafo 2 (NetScience): " << duracion << " us\n";



    //Experimento 7, Tiempo en calcular Laplacian Centrality
    inicio =std::chrono::high_resolution_clock::now();
    for(auto v: grafo->vertices()){
        auto aux = grafo->laplacianCentrality(v);
        if (printBool)std::cout<< v->element << ": " << aux <<", ";
    }
    std::cout<<"\n\n";
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Laplacian Centrality Grafo 1 (IMDB): " << duracion << " us\n";

    inicio =std::chrono::high_resolution_clock::now();
    for(auto v: grafo2->vertices()){
        auto aux = grafo2->laplacianCentrality(v);
        if (printBool) std::cout<< v->element << ": " << aux<<", ";
    }
    std::cout<<"\n\n";
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Laplacian Centrality Grafo 2 (NetScience): " << duracion << " us\n";

/*
   auto ed = grafo->edges();
    //ALGraph<std::string,int> *grafo = new ALGraph<std::string,int>();
    ALGraph<std::string,float> *grafo = new ALGraph<std::string,float>();
    //LoadIMDB(grafo,300);
    LoadNetScience(grafo);

   /*auto ed = grafo->edges();

    for (auto edge : ed){  
        std::cout << edge->start->element << " <-> " << edge->end->element << " | " << edge->element << std::endl;
    }*/
    
    /*
    std::list<Vertex<std::string,int>*> vert =  grafo->vertices();

    std::cout << "Cantidad de vertices:" <<vert.size() << std::endl;
      std::cout << "Energía laplaciana: " << grafo-> laplacianEnergy() << std::endl;
      std::cout << "Laplacian centrality: " << grafo-> laplacianCentrality(*std::begin(vert)) << std::endl;
      std::cout << "Degree centrality: "<< grafo-> degreeCentrality(*std::begin(vert)) << std::endl;

     grafo->updateRank();
      std::cout << "PageRank: " << grafo-> pageRank(*std::begin(vert)) << std::endl;

    //std::cout << grafo-> closenessCentrality(*std::begin(vert)) << std::endl;
    //std::cout << grafo-> harmonicCentrality(*std::begin(vert)) << std::endl;
   // std::cout << grafo-> averagePathLength() << std::endl;
   int i = 0;
   //grafo2->updateCFC_Centrality();
    std::cout << "Closeness centrality: " << grafo-> closenessCentrality(*std::begin(vert)) << std::endl;
    std::cout << "Harmonic centrality: " << grafo-> harmonicCentrality(*std::begin(vert)) << std::endl;
    std::cout << "Average path length: " << grafo-> averagePathLength() << std::endl;
   //std::cout << "Betweenness centrality: " << grafo-> betweennessCentrality(*std::begin(vert)) << std::endl;
   */
}
