#include "Graph.hpp"

template<typename E>
class ALGraph : public Graph<E>{

    private:
    std::list<Vertex<E>*> vertexList;
    std::list<Edge<E>*> edgeList;


    public:
    // Métodos de acceso

    //Un arreglo con los dos puntos extremos de e
    std::array<Vertex<E>*,2> endVertices(Edge<E> *e) override{
        return {e->start, e->end};
    }
    //El vértice opuesto de v en la arista e
    Vertex<E> *opposite(Vertex<E> *v, Edge<E> *e) override{
        if (v==e->start)
            return e->end;
        else if (v==e->end)
            return e->start;
        else
            return nullptr;
    }
    //true iff v y w son adyacentes
    virtual bool areAdjacent(Vertex<E> *v, Vertex<E> *w) override{
        for (Edge<E>* e : v->edges)
        {
            if (opposite(v,e) == w)
                return true;
        }
        return false;
        
    }
    //Reemplaza el elemento en el vértice con x
    virtual void replace(Vertex<E> *v, E x) override{
        v->element = x;
    }
    //Reemplaza el elemento en la arista con x
    virtual void replace(Edge<E> *e, E x) override{
        e->element = x;
    }


    // Métodos de actualización

    //Inserta un vértice almacenando el elemento o
    virtual Vertex<E> *insertVertex(E o) override{
        Vertex<E> *v = new Vertex<E>(o);
        auto it = vertexList.insert(vertexList.end(),v);
        v->it = it;
        return v;
    }
    //Inserta una arista (v,w) almacenando el elemento o
    virtual Edge<E> *insertEdge(Vertex<E> *v, Vertex<E> *w, E o) override{
        Edge<E> *e = new Edge<E>(v,w,o);
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
    virtual void removeVertex(Vertex<E> *v) override{
        //elimina aristas
        while (!v->edges.empty())
        {
            removeEdge(v->edges.front());
        }

        vertexList.erase(v->it);
        delete v;
    }
    //Elimina la arista e
    virtual void removeEdge(Edge<E> *e) override{
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
    virtual std::list<Edge<E>*> incidentEdges(Vertex<E> *v) override{
        return v->edges;
    }
    //Todos los vértices en el grafo
    virtual std::list<Vertex<E>*> vertices() override{
        return vertexList;
    }
    //Todas las aristas en el grafo
    virtual std::list<Edge<E>*> edges() override{
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
            Vertex<E>* v = vertexList.front();
            vertexList.pop_front();
            delete v;
        }
    }

};