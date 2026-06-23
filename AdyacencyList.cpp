#include "Graph.hpp"
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

};