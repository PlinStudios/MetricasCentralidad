#include "datasets/Load_IMDB.cpp"
#include "AdyacencyList.cpp"

int main(){
    ALGraph<int> *grafo = new ALGraph<int>();
    LoadIMDB(grafo,10000);

    auto ed = grafo->edges();

    for (auto edge : ed){
        std::cout << edge->element;
    }
}