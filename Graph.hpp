#include <array>
#include <list>
#pragma once

template<typename V, typename E>
class Edge;

template<typename V, typename E>
class Vertex{
    public:
    V element;

    std::list<Edge<V,E>*> edges;

    typename std::list<Vertex<V,E>*>::iterator it;

    Vertex(V o) : element(o) {}
};

template<typename V, typename E>
class Edge{
    public:
    Vertex<V,E> *start;
    Vertex<V,E> *end;

    E element;

    typename std::list<Edge<V,E>*>::iterator startit;
    typename std::list<Edge<V,E>*>::iterator endit;

    typename std::list<Edge<V,E>*>::iterator it;

    Edge(Vertex<V,E>* s, Vertex<V,E>* e, E o)
    : start(s), end(e), element(o) {}
};

//ADT Grafo
template<typename V, typename E>
class Graph{

    public:
    // Métodos de acceso
    virtual std::array<Vertex<V,E>*,2> endVertices(Edge<V,E> *e)=0; //Un arreglo con los dos puntos extremos de e
    virtual Vertex<V,E> *opposite(Vertex<V,E> *v, Edge<V,E> *e)=0; //El vértice opuesto de v en la arista e
    virtual bool areAdjacent(Vertex<V,E> *v, Vertex<V,E> *w)=0; //true iff v y w son adyacentes
    virtual void replace(Vertex<V,E> *v, V x)=0; //Reemplaza el elemento en el vértice con x
    virtual void replace(Edge<V,E> *e, E x)=0; //Reemplaza el elemento en la arista con x

    // Métodos de actualización
    virtual Vertex<V,E> *insertVertex(V o)=0; //Inserta un vértice almacenando el elemento o
    virtual Edge<V,E> *insertEdge(Vertex<V,E> *v, Vertex<V,E> *w, E o)=0; //Inserta una arista (v,w) almacenando el elemento o
    virtual void removeVertex(Vertex<V,E> *v)=0; //Elimina el vértice (y sus aristas incidentes)
    virtual void removeEdge(Edge<V,E> *e)=0; //Elimina la arista e

    // Métodos iteradores
    virtual std::list<Edge<V,E>*> incidentEdges(Vertex<V,E> *v)=0; //Aristas incidentes a un vértice v
    virtual std::list<Vertex<V,E>*> vertices()=0; //Todos los vértices en el grafo
    virtual std::list<Edge<V,E>*> edges()=0; //Todas las aristas en el grafo

    virtual ~Graph() = default;
};