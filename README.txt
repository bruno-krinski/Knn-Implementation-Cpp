++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ Aluno de Mestrado: Bruno Alexandre Krinski                                   +
+ Matéria: Processamento de Imagens                                            +
+ Trabalho: Implementação dos algoritmos Knn para classificação e Chain Codes  +
+           para a extração de características de uma base de número de 0 à 9  +
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ COMPILAÇÃO:                                                                  +
+ cd build                                                                     +
+ cmake ..                                                                     +
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ Execução do KNN:                                                             +
+ ./knn <caminho arquivo treino> <caminho arquivo teste> k                     +
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ Execução do extrator de características:                                     +
+ ./genFeatures arg1 arg2 arg3 arg4 arg5 arg6                                  +
+ arg1 = <caminho arquivo treino>                                              +
+ arg2 = <caminho imagens treino>                                              +
+ arg3 = <caminho arquivo validação>                                           +
+ arg4 = <caminho imagens validação>                                           +
+ arg5 = <caminho arquivo teste>                                               +
+ arg6 = <caminho imagens teste>                                               +
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ Pasta Classify: Contém os arquivos da implementação do K-Nearest-Kneibors.   +
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ Pasta GenFeatures: Contém os arquivos da implementação do algoritmo de       +
+ extração de características da base de números. O algoritmo implementado para+
+ realizar a extração de características da base foi o Chain Code.             +
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                            
