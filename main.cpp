#include "datasets/Load_IMDB.cpp"
#include "AdyacencyList.cpp"

int main(){
    ALGraph<std::string,int> *grafo = new ALGraph<std::string,int>();
    LoadIMDB(grafo,10000);

    auto ed = grafo->edges();

    for (auto edge : ed){
        std::cout << edge->start->element << ',' << edge->end->element << ',' << edge->element << std::endl;
    }
}