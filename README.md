# MetricasCentralidad
Calcula Metricas de Centralidad en Grafos y registra tiempo usado para ello

## Uso
Obtener los dataset
- imdb_edgelist.csv : https://www.kaggle.com/datasets/aditijuneja/imdb-actors-network-dataset
- NetScience.net : https://www.kaggle.com/datasets/mateuscco/toy-network-datasets?select=NetScience.net
y mover a /datasets<br />

Compilar
´´´
g++ main.cpp -o CentralityMetrics
´´´
y ejecutar
´´´
./CentralityMetrics
´´´
<br />

## Testear Tiempos
Luego de añadir los datasets<br />
Ejecutar test.bat, genera un archivo time.csv con los tiempos usados para cada metrica a travez de varios intentos