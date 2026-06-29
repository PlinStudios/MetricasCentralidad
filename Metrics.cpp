#include "Graph.hpp"
#include <unordered_map>
#include <queue>
#include <cmath>

// MÉTODOS PARA CALCULAR MEDIDAS DE CENTRALIDAD


//calculamos energia laplaciana, si le entregamos un parametro es porque queremos calcuar la energia del graph sin este vertice
template<typename V, typename E>
float laplacianEnergy(Graph<V,E> *graph, Vertex<V,E> *vertex = nullptr){  //parametro opcional corresponde a vertice al que le queremos calcular laplacian centrality
    float energy=0;
    for (auto v: graph->vertices()){  //recorremos todos los vertices del graph
        float sum=0;
        if (v!=vertex){  //mientras el vertice no corresponda a nuestro parametro calculamos 
            for (auto ed : graph->incidentEdges(v)){
                if (ed->start!=vertex && ed->end!=vertex){  //mientras arista no contenga al vertice parametro calculamos
                    sum+=ed->element;
                    energy+=ed->element*ed->element;
                }
            }
        }
    energy+=sum*sum;
    }
    return energy;
}

template<typename V, typename E>
float laplacianCentrality(Graph<V,E> *graph, Vertex<V,E> *v){
    float lapTotal= laplacianEnergy(graph);  //calculamos la energia laplaciana de todo el graph
    float lapNoVertex= laplacianEnergy(graph,v);  //calculamos la energía laplaciana del graph que no contiene al vertice
    float lapVertex= (float) (lapTotal - lapNoVertex)/lapTotal;  //calculamos según fórmula
    return lapVertex;
}

// grado de un vertice dividido en la cantidad total de vertices, sirve para normalizar
template<typename V, typename E>
float degreeCentrality(Graph<V,E> *graph, Vertex<V,E> *v){
    int degree=graph->incidentEdges(v).size();
    int total=graph->vertices().size();
    return (float)degree/(total-1);
}

//cacula el pageRank de un vertice en base a sus vecinos y sus ranks
template<typename V, typename E>
void getPageRank(Graph<V,E> *graph, Vertex<V,E> *v){
    int n= graph->vertices().size();
    float d=0.85;   //dampener tradicional, sirve para que el rank no aumente infinitamente 
    float sum=0;
    for (auto veci : graph->incidentEdges(v)){  //navegamos los vecinos y sus ranks
        //calculamos según fórmula
        sum+= (float) graph->opposite(v, veci)->rank/graph->incidentEdges(graph->opposite(v, veci)).size();
    }
    //std::cout << sum << std::endl;
    v->rank= (float) (1-d)/n + d*sum;

}

//actualizamos el rank de todos los vertices del graph
template<typename V, typename E>
void updateRank(Graph<V,E> *graph){
    for (int i=0; i<45; i++){  //iteramos 45 (máximo) veces porque es el éstandar que ocupa google
        int cont=0;
        for (auto v: graph->vertices()){
            float aux= pageRank(v);
            getPageRank(graph,v);
            float dif = abs(pageRank(v) - aux);  //diferencia entre el rank antiguo y el nuevo
            if (dif<0.0001){    //si la diferencia es pequeña significa que los ranks se estabilizaron y podemos dejar de actualizar
                cont++;  
            }
        }
        if (cont==graph->vertices().size()){  //chequeamos que todos los valores de pagerank se hayan estabilizado
            return;
        }
    }
}

//retornamos pagerank de un vertice
template<typename V, typename E>
float pageRank(Vertex<V,E> *v){
    return v->rank;
}

//calculamos closeness centrality
template<typename V, typename E>
float closenessCentrality(Graph<V,E> *graph, Vertex<V,E> *v){
    E INF = numeric_limits<E>::max();  //infinito
    float sum=0;
    unordered_map<Vertex<V, E>*, E> dist= shortestPath(graph,v);  //calculamos el largo de los caminos más cortos entre nuestro vertice y el resto
        for (Vertex<V, E>* u : graph->vertices()) {
        if (dist[u]== INF){  //como estgamos trabajando con división, si dividimos por infinito sabemos inmediatamente que el resultado es 0
            return 0;
        }
        sum+=dist[u];
        }
        //calculamos según fórmula
    float close= (float) (graph->vertices().size() - 1 ) / sum;  //cantidad de vertices dividido por la suma de toods los caminos mas cortos de v
    return close;
}

//calculamos harmonic centrality
template<typename V, typename E>
float harmonicCentrality(Graph<V,E> *graph, Vertex<V,E> *v){
    E INF = numeric_limits<E>::max();  //infinito
    float sum=0;
    unordered_map<Vertex<V, E>*, E> dist= shortestPath(graph,v);  //calculamos el largo de los caminos más cortos entre nuestro vertice y el resto
    for (Vertex<V, E>* u : graph->vertices()) {
        if (dist[u]== INF || dist[u]== 0){  //si no existe camino más corto nos saltamos el vertice
            sum+=0;
        }
            else{
            sum+= (float) 1/dist[u];
        }
        }
    return sum / (graph->vertices().size() - 1);  //normaliza la métrica
}

//calcula el largo promedio del camino más corto entre dos vértices
template<typename V, typename E>
float averagePathLength(Graph<V,E> *graph){
    E INF = numeric_limits<E>::max();  //infinito
    float sum=0;
    for (Vertex<V, E>* v : graph->vertices()) {  //calculamos la distancia a otros vertices para todos los vertices
        unordered_map<Vertex<V, E>*, E> dist= shortestPath(graph,v);
        for (Vertex<V, E>* u : graph->vertices()) {
            if (dist[u]== INF){  //si el camino no existe (es de largo infinito) lo saltamos
                sum+=0;
            }
            else{
                sum+= dist[u];
            }
        }
    }
    //calculamos según fórmula
    return (float) sum / ((graph->vertices().size() - 1)*graph->vertices().size()); 
}


// código basado en implementación de geeksforgeeks de dijkstra
//https://www.geeksforgeeks.org/dsa/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/
template<typename V, typename E>
std::unordered_map<Vertex<V, E>*, E> shortestPath(Graph<V,E> *graph, Vertex<V, E>* src) {
    E INF = numeric_limits<E>::max();  //infinito
    // Priority queue que guarda pares de: <distancia actual, puntero al vertice>
    // greater es para que los menores elementos se procesen primero
    using PQ_Element = pair<E, Vertex<V, E>*>;
    priority_queue<PQ_Element, vector<PQ_Element>, greater<PQ_Element>> pq;
    // distancia entre nuestro punto de partida (src) y los otros vectores
    unordered_map<Vertex<V, E>*, E> dist;

    // se inicializa la distancia como infinito
    for (auto v : graph->vertices()) {
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
            Vertex<V, E>* v = graph->opposite(u, e);
            E weight = e->element;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    } 
    return dist;
}


//Actualiza los valores de CFCC, pero solo funciona en componentes conexas
template<typename V, typename E>
void updateCFC_Centrality(Graph<V,E> *graph){
    auto vertices_list = graph.vertices();
    int graph_size = vertices_list.size();
    std::unordered_map<Vertex<V, E>*, int> indexMap;
    int index = 0;
    //utiliza un mapa para asignar a cada vertice un indice
    for (auto v : vertices_list) {
        indexMap[v] = index++;
    }
    //crea la matriz laplaciana y la actualiza usando la lista de adyacencia de cada nodo
    std::vector<std::vector<double>> matriz_laplaciana(graph_size, std::vector<double>(graph_size, 0));
    for (auto v : vertices_list) {
        int row = indexMap[v];
        for (auto e : incidentEdges(v)) {
            auto w = graph->opposite(v, e);
            if (w == nullptr) continue;
            int col = indexMap[w];
            // para un graph no dirigido, procesar cada arista una sola vez
            if (row < col) {
                double weight = (double)e->element;
                matriz_laplaciana[row][row] += weight;
                matriz_laplaciana[col][col] += weight;
                matriz_laplaciana[row][col] -= weight;
                matriz_laplaciana[col][row] -= weight;
            }
        }
    }
    //calcula la inversa utilizando pivoteo parcial
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
            std::cout<<"La matriz es singular (no tiene inversa)."<<endl;
            return;
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
    //una vez que se tiene la matriz C, falta tan solo calcular la traza, el resto es una operacion O(1) para cada vertice
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

//codigo basado en implementación de geeksforgeeks de dijkstra
//https://www.geeksforgeeks.org/dsa/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/
template<typename V, typename E>
float betweennessCentrality(Graph<V,E> *graph, Vertex<V, E>* target) {
    E INF = numeric_limits<E>::max();  //infinito
    float bet = 0.0f;

    for (Vertex<V, E>* src : graph->vertices()) { // vertice de inicio
        for (Vertex<V, E>* dest : graph->vertices()) { //vertice destino
            
            // se nos pide que no sean iguales en la formula
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
            for (auto vertex : graph->vertices()) {
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
                    Vertex<V, E>* neighbor = graph->opposite(u, e);
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
            //calculamos según fórmula
            if (num_paths[dest] > 0) {
                bet += (float)paths_through_target[dest] / num_paths[dest];
            }
        }
    }

    return bet; 
}