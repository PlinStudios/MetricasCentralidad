#include "Graph.hpp"
#include <vector>
#include <unordered_map>
#include <cmath>
#include <stdexcept>
#include "InverseMatrix.hpp"
#pragma once

using namespace std;
#include <queue>
#include <unordered_map>
#include <limits>
#include <iostream>


template<typename V, typename E>
class ALGraph : public Graph<V,E>{

    private:
    std::list<Vertex<V,E>*> vertexList;
    std::list<Edge<V,E>*> edgeList;

    public:
    // Métodos de acceso

    
    E INF = numeric_limits<E>::max();  //infinito

    //Un arreglo con los dos puntos extremos de e
    std::array<Vertex<V,E>*,2> endVertices(Edge<V,E> *e) override{
        return {e->start, e->end};
    }
    //El vértice opuesto de v en la arista e
    Vertex<V,E> *opposite(Vertex<V,E> *v, Edge<V,E> *e) override{
        if (v==e->start)
            return e->end;
        else if (v==e->end)
            return e->start;
        else
            return nullptr;
    }
    //true iff v y w son adyacentes
    virtual bool areAdjacent(Vertex<V,E> *v, Vertex<V,E> *w) override{
        for (Edge<V,E>* e : v->edges)
        {
            if (opposite(v,e) == w)
                return true;
        }
        return false;
        
    }
    //Reemplaza el elemento en el vértice con x
    virtual void replace(Vertex<V,E> *v, V x) override{
        v->element = x;
    }
    //Reemplaza el elemento en la arista con x
    virtual void replace(Edge<V,E> *e, E x) override{
        e->element = x;
    }


    // Métodos de actualización

    //Inserta un vértice almacenando el elemento o
    virtual Vertex<V,E> *insertVertex(V o) override{
        Vertex<V,E> *v = new Vertex<V,E>(o);
        auto it = vertexList.insert(vertexList.end(),v);
        v->it = it;
        v->rank=0;
        return v;
    }
    //Inserta una arista (v,w) almacenando el elemento o
    virtual Edge<V,E> *insertEdge(Vertex<V,E> *v, Vertex<V,E> *w, E o) override{
        Edge<V,E> *e = new Edge<V,E>(v,w,o);
        auto it = edgeList.insert(edgeList.end(),e);
        e->it = it;

        //referencia a la arista en los vertices
        auto vit = v->edges.insert(v->edges.end(), e);
        auto wit = w->edges.insert(w->edges.end(), e);

        e->startit=vit;
        e->endit=wit;

        return e;
    }
    //Elimina el vértice (y sus aristas incidentes)
    virtual void removeVertex(Vertex<V,E> *v) override{
        //elimina aristas
        while (!v->edges.empty())
        {
            removeEdge(v->edges.front());
        }

        vertexList.erase(v->it);
        delete v;
    }
    //Elimina la arista e
    virtual void removeEdge(Edge<V,E> *e) override{
        edgeList.erase(e->it);

        //elimina del listado en los vertices
        if (e->start == e->end)
        {
            //si es self-loop no borra dos veces
            e->start->edges.erase(e->startit);
        }
        else
        {
            e->start->edges.erase(e->startit);
            e->end->edges.erase(e->endit);
        }

        delete e;
    }


    // Métodos iteradores

    //Aristas incidentes a un vértice v
    virtual std::list<Edge<V,E>*> incidentEdges(Vertex<V,E> *v) override{
        return v->edges;
    }
    //Todos los vértices en el grafo
    virtual std::list<Vertex<V,E>*> vertices() override{
        return vertexList;
    }
    //Todas las aristas en el grafo
    virtual std::list<Edge<V,E>*> edges() override{
        return edgeList;
    }

    ~ALGraph()
    {
        while (!edgeList.empty())
        {
            removeEdge(edgeList.front());
        }

        while (!vertexList.empty())
        {
            Vertex<V,E>* v = vertexList.front();
            vertexList.pop_front();
            delete v;
        }
    }

    float laplacianEnergy(Vertex<V,E> *vertex = nullptr){
        float energy=0;
        for (auto v: this->vertexList){
            float sum=0;
            if (v!=vertex){
                for (auto ed : this->incidentEdges(v)){
                    if (ed->start!=vertex && ed->end!=vertex){
                        sum+=ed->element;
                        energy+=ed->element*ed->element;
                    }
                }
            }
        energy+=sum*sum;
        }
        //std::cout << energy << std::endl;
        return energy;
    }

    float laplacianCentrality(Vertex<V,E> *v){
        float lapTotal= this->laplacianEnergy();
        float lapNoVertex= laplacianEnergy(v);
        float lapVertex= (float) (lapTotal - lapNoVertex)/lapTotal;
        //std::cout << lapTotal << " <-> " << lapNoVertex << std::endl;
        return lapVertex;
    }

    float degreeCentrality(Vertex<V,E> *v){
        int degree=this->incidentEdges(v).size();
        int total=this->vertices().size();
        return (float)degree/(total-1);
    }


    void getPageRank(Vertex<V,E> *v){
        int n= this->vertices().size();
        float d=0.1;
        auto vecinos= this->incidentEdges(v);
        float sum=0;
        for (auto veci : vecinos){
            sum+= (float) opposite(v, veci)->rank/this->incidentEdges(opposite(v, veci)).size();
        }
        //std::cout << sum << std::endl;
        v->rank= (float) (1-d)/n + d*sum;

    }


    void updateRank(){
        auto vertices= this->vertices();
        for (int i=0; i<25; i++){
            int cont=0;
            for (auto v: vertices){
                float aux= pageRank(v);
                this->getPageRank(v);
                float dif = abs(pageRank(v) - aux);
                if (dif<0.0001){
                    cont++;
                }
            }
            if (cont==vertices.size()){
                return;
            }
        }
    }

    float pageRank(Vertex<V,E> *v){
        return v->rank;
    }

    float closenessCentrality(Vertex<V,E> *v){
        float sum=0;
        unordered_map<Vertex<V, E>*, E> dist= shortestPath(v);
         for (Vertex<V, E>* u : vertexList) {
            if (dist[u]== INF){
                return 0;
            }
            sum+=dist[u];
         }
        float close= (float) (this->vertices().size() - 1 ) / sum;
        return close;
    }


    float harmonicCentrality(Vertex<V,E> *v){
        float sum=0;
        unordered_map<Vertex<V, E>*, E> dist= shortestPath(v);
        for (Vertex<V, E>* u : vertexList) {
            if (dist[u]== INF || dist[u]== 0){
                sum+=0;
            }
                else{
                sum+= (float) 1/dist[u];
            }
         }
        return sum / (vertices().size() - 1);  //normaliza la métrica
    }

    float averagePathLength(){
        float sum=0;
        for (Vertex<V, E>* v : vertexList) {
            unordered_map<Vertex<V, E>*, E> dist= shortestPath(v);
            for (Vertex<V, E>* u : vertexList) {
                if (dist[u]== INF){
                    sum+=0;
                }
                else{
                    sum+= dist[u];
                }
            }
        }
        return (float) sum / ((vertices().size() - 1)*vertices().size()); 
    }


// código basado en implementación de geeksforgeeks
unordered_map<Vertex<V, E>*, E> shortestPath(Vertex<V, E>* src) {
    // Priority queue que guarda pares de: <distancia actual, puntero al vertice>
    // greater es para que los menores elementos se procesen primero
    using PQ_Element = pair<E, Vertex<V, E>*>;
    priority_queue<PQ_Element, vector<PQ_Element>, greater<PQ_Element>> pq;

    // distancia entre nuestro punto de partida (src) y los otros vectores
    unordered_map<Vertex<V, E>*, E> dist;

    // se inicializa la distancia como infinito
    for (auto v : this->vertexList) {
        dist[v] = INF;
    }

    // se inserta el src con distancia 0
    pq.push(make_pair(static_cast<E>(0), src));
    dist[src] = static_cast<E>(0);

    while (!pq.empty()) {
        // se saca vertice con menor distancis
        Vertex<V, E>* u = pq.top().second;  //segundo elemento del par, es decir el vértice
        E dist_u = pq.top().first;  //primer elemento del par, la distancia
        pq.pop();

        // saltamos si ya hay distanica menor
        if (dist_u > dist[u]) {
            continue;
        }

        // recorremos todos los vertices conectados a u
        for (Edge<V, E>* e : u->edges) {
            Vertex<V, E>* v = opposite(u, e);
            E weight = e->element;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    } 

    return dist;
}



    void updateCFC_Centrality(){
        auto vertices_list = vertices();
        int graph_size = vertices_list.size();
        std::vector<std::vector<int>> matriz_laplaciana(graph_size, std::vector<int>(graph_size, 0));
        std::unordered_map<Vertex<V, E>*, int> indexMap;
        int index = 0;
        for (auto v : vertices_list) {
            indexMap[v] = index++;
        }
        for (auto v : vertices_list) {
            int row = indexMap[v];
            for (auto e : incidentEdges(v)) {
                auto w = opposite(v, e);
                if (w == nullptr) continue;
                int col = indexMap[w];
                // para un grafo no dirigido, procesar cada arista una sola vez
                if (row < col) {
                    int weight = e->element;
                    matriz_laplaciana[row][row] += weight;
                    matriz_laplaciana[col][col] += weight;
                    matriz_laplaciana[row][col] -= weight;
                    matriz_laplaciana[col][row] -= weight;
                }
            }
        }

        std::vector<std::vector<double>> augM(graph_size, std::vector<double>(2 * graph_size, 0.0));

        for (int a = 0; a < graph_size; ++a) {
            for (int b = 0; b < graph_size; ++b) {
                matriz_laplaciana[a][b]++;
                augM[a][b] = static_cast<double>(matriz_laplaciana[a][b]);
            }
            augM[a][graph_size + a] = 1.0;
        }

        for (int col = 0; col < graph_size; ++col) {
            int maxRow = col;
            double maxVal = std::fabs(augM[col][col]);
            for (int row = col + 1; row < graph_size; ++row) {
                double val = std::fabs(augM[row][col]);
                if (val > maxVal) {
                    maxVal = val;
                    maxRow = row;
                }
            }

            if (maxVal < 1e-12) {
                throw std::invalid_argument("La matriz es singular (no tiene inversa).");
            }

            if (maxRow != col) {
                std::swap(augM[col], augM[maxRow]);
            }

            double pivot = augM[col][col];
            for (int j = col; j < 2 * graph_size; ++j) {
                augM[col][j] /= pivot;
            }

            for (int row = 0; row < graph_size; ++row) {
                if (row == col) continue;
                double factor = augM[row][col];
                for (int j = col; j < 2 * graph_size; ++j) {
                    augM[row][j] -= factor * augM[col][j];
                }
            }
        }

        std::vector<std::vector<double>> matriz_c(graph_size, std::vector<double>(graph_size, 0.0));
        for (int i = 0; i < graph_size; ++i) {
            for (int j = 0; j < graph_size; ++j) {
                matriz_c[i][j] = augM[i][graph_size + j];
            }
        }

        double traza = 0.0;
        for (int a = 0; a < graph_size; ++a) {
            traza += matriz_c[a][a];
        }

        int pos = 0;
        for (auto v : vertices_list) {
            double aux_cent = graph_size * matriz_c[pos][pos] + traza - 2.0 / graph_size;
            v->cfc_centrality = 1.0 / aux_cent;
            pos++;
        }
    }

//codigo basado en implementación de geeksforgeeks
float betweennessCentrality(Vertex<V, E>* target) {
    float bet = 0.0f;

    for (Vertex<V, E>* src : this->vertexList) {
        for (Vertex<V, E>* dest : this->vertexList) {
            // se nos pide qie no sean iguales
            if (src == dest || src == target || dest == target) {
                continue;
            }

             // Priority queue que guarda pares de: <distancia actual, puntero al vertice>
            // greater es para que los menores elementos se procesen primero
            using PQ_Element = pair<E, Vertex<V, E>*>;
            priority_queue<PQ_Element, vector<PQ_Element>, greater<PQ_Element>> pq;

            // distancia entre nuestro punto de partida (src) y los otros vectores
            unordered_map<Vertex<V, E>*, E> dist;
            //cantidad de caminos
            unordered_map<Vertex<V, E>*, int> num_paths;
            //caminos que pasan por nuestro vertice a calcular
            unordered_map<Vertex<V, E>*, int> paths_through_target;

            // Inicializamos valores
            for (auto vertex : this->vertexList) {
                dist[vertex] = INF;
                num_paths[vertex] = 0;
                paths_through_target[vertex] = 0;
            }

            // se inicializa src
            pq.push(std::make_pair(static_cast<E>(0), src));
            dist[src] = static_cast<E>(0);
            num_paths[src] = 1;

            while (!pq.empty()) {
                // se saca el vertice a menor distancia
                Vertex<V, E>* u = pq.top().second;  //segundo elemento del par, es decir el vértice
                E dist_u = pq.top().first;  //primer elemento del par, la distancia
                pq.pop();
                

                // saltamos si ya hay distancia menor
                if (dist_u > dist[u]) {
                    continue;
                }

                // recorremos todos los vértices conectados a u
                for (Edge<V, E>* e : u->edges) {
                    Vertex<V, E>* neighbor = opposite(u, e);
                    E weight = e->element;

                    // si encontramos camino mas corto
                    if (dist[neighbor] > dist[u] + weight) {
                        dist[neighbor] = dist[u] + weight;
                        pq.push(std::make_pair(dist[neighbor], neighbor));
                        
                        // se "hereda" la canitdad de caminos que nos llevan a u
                        num_paths[neighbor] = num_paths[u];
                        
                        // si u es nuestro target aumentamos el coontador
                        if (u == target) {
                            paths_through_target[neighbor] = num_paths[u];
                        } else { //si al llegar a u ya pasamos por target
                            paths_through_target[neighbor] = paths_through_target[u];
                        }
                    } 
                    // si encontramos camino que también es el más corto
                    else if (dist[neighbor] == dist[u] + weight) {
                        // sumamos caminos alternos
                        num_paths[neighbor] += num_paths[u];
                        
                        if (u == target) {
                            paths_through_target[neighbor] += num_paths[u];
                        } else {
                            paths_through_target[neighbor] += paths_through_target[u];
                        }
                    }
                }
            }

            if (num_paths[dest] > 0) {
                bet += (float)paths_through_target[dest] / num_paths[dest];
            }
        }
    }

    return bet; 
}


};