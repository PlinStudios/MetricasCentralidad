#include "datasets/Load_IMDB.cpp"
#include "datasets/Load_NetScience.cpp"
#include "AdyacencyList.cpp"
#include "metrics.cpp"
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
    float degCent = degreeCentrality<std::string,int>(grafo,*std::begin(vert));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Betweenness Centrality
    inicio = std::chrono::high_resolution_clock::now();
    float betCent = betweennessCentrality(grafo,*std::begin(vert));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Closeness Centrality
    inicio = std::chrono::high_resolution_clock::now();
    float closCent = closenessCentrality(grafo,*std::begin(vert));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Page Rank
    inicio = std::chrono::high_resolution_clock::now();
    updateRank(grafo);
    float prank = pageRank(*std::begin(vert));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Average Shortest Path
    inicio = std::chrono::high_resolution_clock::now();
    float avg = averagePathLength(grafo);
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Laplacian Centrality
    inicio = std::chrono::high_resolution_clock::now();
    float lapCen = laplacianCentrality(grafo,*std::begin(vert));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Harmonic Centrality
    inicio = std::chrono::high_resolution_clock::now();
    float harCen = harmonicCentrality(grafo,*std::begin(vert));
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
    degCent = degreeCentrality(grafo2,*std::begin(vert2));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Betweenness Centrality
    inicio = std::chrono::high_resolution_clock::now();
        betCent = betweennessCentrality(grafo2,*std::begin(vert2));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Closeness Centrality
    inicio = std::chrono::high_resolution_clock::now();
        closCent = closenessCentrality(grafo2,*std::begin(vert2));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Page Rank
    inicio = std::chrono::high_resolution_clock::now();
    updateRank(grafo2);
        prank = pageRank(*std::begin(vert2));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Average Shortest Path
    inicio = std::chrono::high_resolution_clock::now();
        avg = averagePathLength(grafo2);
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Laplacian Centrality
    inicio = std::chrono::high_resolution_clock::now();
        lapCen = laplacianCentrality(grafo2,*std::begin(vert2));
    fin = std::chrono::high_resolution_clock::now();
    duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    outtime << duracion << ',';

    //Harmonic Centrality
    inicio = std::chrono::high_resolution_clock::now();
        harCen = harmonicCentrality(grafo2,*std::begin(vert2));
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
