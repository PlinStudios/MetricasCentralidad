echo ConstruccionIMDB,DegreeCentralityIMDB,BetweennessCentralityIMDB,ClosenessCentralityIMDB,PageRankIMDB,AverageShortestPathIMDB,LaplacianCentralityIMDB,HarmonicCentralityIMDB,ConstruccionNetScience,DegreeCentralityNetScience,BetweennessCentralityNetScience,ClosenessCentralityNetScience,PageRankNetScience,AverageShortestPathNetScience,LaplacianCentralityNetScience,HarmonicCentralityNetScience > time.csv

g++ main.cpp -o CentralityMetrics

@echo off
for /L %%x in (1,1,20) do (
CentralityMetrics 50 > nul
)