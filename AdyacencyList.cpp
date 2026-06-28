#include "Graph.hpp"
#include <vector>
#include "InverseMatrix.hpp"
#pragma once

template<typename V, typename E>
class ALGraph : public Graph<V,E>{

    private:
    std::list<Vertex<V,E>*> vertexList;
    std::list<Edge<V,E>*> edgeList;

    public:
    // Métodos de acceso

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

    int laplacianEnergy(Vertex<V,E> *vertex = nullptr){
        int energy=0;
        for (auto v: this->vertexList){
            int sum=0;
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
        int lapTotal= this->laplacianEnergy();
        int lapNoVertex= laplacianEnergy(v);
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
        int d=0.1;
        auto vecinos= this->incidentEdges(v);
        float sum=0;
        for (auto veci : vecinos){
            sum+= (float) veci->end->rank/this->incidentEdges(veci->end).size();
        }
        //std::cout << sum << std::endl;
        v->rank= (float) (1-d)/n + d*sum;

    }


    void updateRank(){
        auto vertices= this->vertices();
        for (int i=0; i<5; i++){
            for (auto v: vertices){
                this->getPageRank(v);
            }
        }
    }

    float pageRank(Vertex<V,E> *v){
        return v->rank;
    }

    void updateCFC_Centrality(){
        int graph_size = vertices().size();
        std::vector<std::vector<int>> matriz_laplaciana(graph_size, std::vector<int>(graph_size, 0.0));
        int i = 0
        int j = 0;
        for (auto v : vertices){
            j=0;
            for (auto w : vertices){
                if (areAdjacent(v,w) && matriz_laplaciana[i][j]==0.0){
                    int weight = edge->element;
                    matriz_laplaciana[i][i] += weight;
                    matriz_laplaciana[j][j] += weight;
                    matriz_laplaciana[i][j] -= weight;
                    matriz_laplaciana[j][i] -= weight;
                }
                j++;
            }
            i++;
        }
        for (int a =0; a<graph_size; a++){
            for (int b=0;b<graph_size;b++){
                matriz_laplaciana[a][b]++;
            }
        }
        vector<vector<double>> matriz_c(graph_size, vector<double>(graph_size));
        inverse(matriz_laplaciana, matriz_c);
        double traza = 0;
        for(int a=0; a<n;a++){
            traza+= matriz_c[a][a];
        }
        i=0;
        for (auto v : vertices){
            double aux_cent = graph_size*matriz_c[i][i]+traza-2/graph_size;
            v->cfc_centrality = 1/aux_cent;
            i++;
        }

    }
};