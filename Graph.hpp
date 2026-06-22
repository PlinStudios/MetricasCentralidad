#include <array>
#include <list>

template<typename E>
class Edge;

template<typename E>
class Vertex{
    public:
    E element;

    std::list<Edge<E>*> edges;

    std::list<Vertex<E>*>::iterator it;

    Vertex(E o) : element(o) {}
};

template<typename E>
class Edge{
    public:
    Vertex<E> *start;
    Vertex<E> *end;

    E element;

    std::list<Edge<E>*>::iterator startit;
    std::list<Edge<E>*>::iterator endit;

    std::list<Edge<E>*>::iterator it;

    Edge(Vertex<E>* s, Vertex<E>* e, E o)
    : start(s), end(e), element(o) {}
};

//ADT Grafo
template<typename E>
class Graph{

    public:
    // Métodos de acceso
    virtual std::array<Vertex<E>*,2> endVertices(Edge<E> *e)=0; //Un arreglo con los dos puntos extremos de e
    virtual Vertex<E> *opposite(Vertex<E> *v, Edge<E> *e)=0; //El vértice opuesto de v en la arista e
    virtual bool areAdjacent(Vertex<E> *v, Vertex<E> *w)=0; //true iff v y w son adyacentes
    virtual void replace(Vertex<E> *v, E x)=0; //Reemplaza el elemento en el vértice con x
    virtual void replace(Edge<E> *e, E x)=0; //Reemplaza el elemento en la arista con x

    // Métodos de actualización
    virtual Vertex<E> *insertVertex(E o)=0; //Inserta un vértice almacenando el elemento o
    virtual Edge<E> *insertEdge(Vertex<E> *v, Vertex<E> *w, E o)=0; //Inserta una arista (v,w) almacenando el elemento o
    virtual void removeVertex(Vertex<E> *v)=0; //Elimina el vértice (y sus aristas incidentes)
    virtual void removeEdge(Edge<E> *e)=0; //Elimina la arista e

    // Métodos iteradores
    virtual std::list<Edge<E>*> incidentEdges(Vertex<E> *v)=0; //Aristas incidentes a un vértice v
    virtual std::list<Vertex<E>*> vertices()=0; //Todos los vértices en el grafo
    virtual std::list<Edge<E>*> edges()=0; //Todas las aristas en el grafo

    virtual ~Graph() = default;
};