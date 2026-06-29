#include "datasets/Load_IMDB.cpp"
#include "datasets/Load_NetScience.cpp"
#include "AdyacencyList.cpp"
#include <chrono>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]){
    int expsize = INT_MAX;
    if (argc>1){
        expsize = stoi(argv[1]);
    }
    std::ofstream outtime("time.csv", std::ios::app);

    ///IMDB
    //Tiempo construccion
    auto inicio = std::chrono::high_resolution_clock::now();
    ALGraph<std::string,int> *grafo = new ALGraph<std::string,int>();
    LoadIMDB(grafo,expsize);
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Tiempo de construccion Grafo 1 (IMDB): " << duracion << " us\n";
    outtime << duracion << ',';

    std::list<Vertex<std::string,int>*> vert =  grafo->vertices();

    //Degree Centrality
    inicio = std::chrono::high_resolution_clock::now();
    float degCent = grafo-> degreeCentrality(*std::begin(vert));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Betweenness Centrality
    inicio = std::chrono::high_resolution_clock::now();
    float betCent = grafo-> betweennessCentrality(*std::begin(vert));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Closeness Centrality
    inicio = std::chrono::high_resolution_clock::now();
    float closCent = grafo-> closenessCentrality(*std::begin(vert));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Page Rank
    inicio = std::chrono::high_resolution_clock::now();
    grafo->updateRank();
    float prank = grafo-> pageRank(*std::begin(vert));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Average Shortest Path
    inicio = std::chrono::high_resolution_clock::now();
    float avg = grafo-> averagePathLength();
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Laplacian Centrality
    inicio = std::chrono::high_resolution_clock::now();
    float lapCen = grafo-> laplacianCentrality(*std::begin(vert));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Harmonic Centrality
    inicio = std::chrono::high_resolution_clock::now();
    float harCen = grafo-> harmonicCentrality(*std::begin(vert));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    std::cout << "Degree Centrality: "<< degCent << std::endl;
    std::cout << "Betweenness Centrality: " << betCent << std::endl;
    std::cout << "Closeness Centrality: " << closCent << std::endl;
    std::cout << "PageRank: " << prank << std::endl;
    std::cout << "Average Shortest Path: " << avg << std::endl;
    std::cout << "Laplacian Centrality: " << lapCen << std::endl;
    std::cout << "Harmonic Centrality: " << harCen << std::endl;

    delete grafo;

    ///NetScience
    //Construccion
    inicio =std::chrono::high_resolution_clock::now();
    ALGraph<std::string,float> *grafo2 = new ALGraph<std::string,float>();
    LoadNetScience(grafo2,expsize);
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Tiempo de construccion Grafo 2 (NetScience): " << duracion << " us\n";
    outtime << duracion << ',';

    std::list<Vertex<std::string,float>*> vert2 =  grafo2->vertices();

    //Degree Centrality
    inicio = std::chrono::high_resolution_clock::now();
    degCent = grafo2-> degreeCentrality(*std::begin(vert2));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Betweenness Centrality
    inicio = std::chrono::high_resolution_clock::now();
        betCent = grafo2-> betweennessCentrality(*std::begin(vert2));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Closeness Centrality
    inicio = std::chrono::high_resolution_clock::now();
        closCent = grafo2-> closenessCentrality(*std::begin(vert2));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Page Rank
    inicio = std::chrono::high_resolution_clock::now();
    grafo2->updateRank();
        prank = grafo2-> pageRank(*std::begin(vert2));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Average Shortest Path
    inicio = std::chrono::high_resolution_clock::now();
        avg = grafo2-> averagePathLength();
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Laplacian Centrality
    inicio = std::chrono::high_resolution_clock::now();
        lapCen = grafo2-> laplacianCentrality(*std::begin(vert2));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Harmonic Centrality
    inicio = std::chrono::high_resolution_clock::now();
        harCen = grafo2-> harmonicCentrality(*std::begin(vert2));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << '\n';

    std::cout << "Degree Centrality: "<< degCent << std::endl;
    std::cout << "Betweenness Centrality: " << betCent << std::endl;
    std::cout << "Closeness Centrality: " << closCent << std::endl;
    std::cout << "PageRank: " << prank << std::endl;
    std::cout << "Average Shortest Path: " << avg << std::endl;
    std::cout << "Laplacian Centrality: " << lapCen << std::endl;
    std::cout << "Harmonic Centrality: " << harCen << std::endl;
}
