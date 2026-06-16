#include <vector>

template<typename E>
class Vertex{
    E element;
};

template<typename E>
class Edge{
    Vertex start;
    Vertex end;

    E element;
};

//ADT Grafo
template<typename E>
class Graph{

    public:
    // Métodos de acceso
    Vertex* endVertices(Edge e); //Un arreglo con los dos puntos extremos de e
    Vertex opposite(Vertex v, Edge e); //El vértice opuesto de v en la arista e
    bool areAdjacent(Vertex v, Vertex w); //true iff v y w son adyacentes
    void replace(Vertex v, E x); //Reemplaza el elemento en el vértice con x
    void replace(Edge e, E x); //Reemplaza el elemento en la arista con 

    // Métodos de actualización
    Vertex insertVertex(E o); //Inserta un vértice almacenando el elemento o
    Edge insertEdge(Vertex v, Vertex w, E o); //Inserta una arista (v,w) almacenando el elemento o
    void removeVertex(Vertex v); //Elimina el vértice (y sus aristas incidentes)
    void removeEdge(Edge e); //Elimina la arista e

    // Métodos iteradores
    std::vector<Edge> incidentEdges(Vertex v); //Aristas incidentes a un vértice v
    std::vector<Vertex> vertices(); //Todos los vértices en el grafo
    std::vector<Edge> edges(); //Todas las aristas en el grafo

};