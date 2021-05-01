Lucas de Almeida Bandeira Macedo - 190047089
Link para repositório: https://github.com/ABMHub/TAG
Compilação: "g++ projeto2.cpp" "./a.out"

Este trabalho utiliza de duas funções para o emparelhamento, uma servindo como emparelhamento inicial, tentando respeitar a lista de preferência de cada professor, e outra para alocar todos os professores que sobraram.

Durante a execução, a primeira coisa que é feita durante o loop principal é ordenar o vetor de professores, de modo crescente em relação a habilitação, para que os professores de habilitação 1 tenham mais chances de ocuparem vagas, e os de habilitação 3 terem mais chances de sobrarem no final, para preencher as vagas restantes. Em seguida, um loop através desse vetor, iterando pela lista de preferência de cada professor, tentando alocá-los para as escolas escolhidas:

A entrada de cada professor em uma escola segue os seguintes critérios, em ordem:

1) Só poderá entrar um professor em uma escola se sua habilitação for maior ou igual a habilitacao da escola.
2) Se determinada vaga estiver vazia, e o professor foi aprovado no critério 1, ele poderá entrar na vaga
3) Em caso de disputa de vaga (um professor tentando entrar em uma vaga já ocupada), terá preferência o professor que tiver rankeado mais alto a escola em sua lista de preferência (preferência 1 = maior, preferência 4 = menor)
4) Em caso de empate no tópico 3, terá preferência o professor que tiver a menor habilitação, mas que ainda passe no critério 1 (para sobrar professores com habilitação alta no final da execução)
5) Em caso de empate no tópico 4, o professor alocado (que está atualmente ocupando a vaga disputada) será substituído se, em sua lista de prioridades, existir uma escola com vaga disponível, que passe pelo critério 1, provocando uma grande movimentação de professores e vagas. Caso não haja, não haverá troca

Após a execução de todos esses critérios, para cada escola na lista de preferência de cada professor, chegamos a um número de 63 professores alocados.

Em seguida, executaremos outro loop, que englobará apenas os professores que não foram alocados no loop anterior, alocando-os independente de sua lista de prioridade, seguindo todos os critérios acima (com exceção do 5). O loop preencherá todas as escolas vazias, atingindo 72 professores alocados.

Mas esse número não foi satisfatório, e durante análise dos grafos gerados, percebi que sobravam muitas vagas que pediam habilitação 3, e muitos professores de habilitação 3 estavam sendo alocados para escolas que pediam baixa habilitação. Então mais uma condição, entre os critérios 1 e 2, como um critério "1.5", foi adicionada no primeiro loop, sacrificando parte da preferência de alguns professores para aumentar o número de professores alocados: um professor de habilitação 3 entrará apenas em escolas de habilitação 3.

Com isso, conseguimos satisfazer 65 professores, e alocar 77.

A versão do código que atinge 72 professores alocados e 63 satisfeitos está no github (o nome do commit é "63 satisfeitos, 72 alocados, codigo comentado", f3ecdca2f47408c00d31922aae41845baa8f83c3), mas não é muito diferente da atual, com exceção do critério "1.5", definido dois parágrafos atrás, que foi uma mudança de uma linha de código.

A output do programa tem duas partes, ambas são print do grafo gerado completo, uma é antes de alocar os professores que sobraram, e a outra é depois:

// OUTPUT //

|| Emparelhamento utilizando apenas a lista de preferencia ||

P1 associado a: (nome = E3, preferencia = 4, vaga = 1)
P2 associado a:
P3 associado a: (nome = E10, preferencia = 1, vaga = 2)
P4 associado a:
P5 associado a:
P6 associado a:
P7 associado a: (nome = E10, preferencia = 1, vaga = 1)
P8 associado a:
P9 associado a: (nome = E21, preferencia = 4, vaga = 2)
P10 associado a: (nome = E7, preferencia = 2, vaga = 1)
P11 associado a:
P12 associado a:
P13 associado a: (nome = E29, preferencia = 4, vaga = 1)
P14 associado a: (nome = E31, preferencia = 4, vaga = 1)
P15 associado a: (nome = E20, preferencia = 1, vaga = 1)
P16 associado a: (nome = E20, preferencia = 1, vaga = 2)
P17 associado a:
P18 associado a:
P19 associado a: (nome = E41, preferencia = 4, vaga = 1)
P20 associado a: (nome = E43, preferencia = 4, vaga = 1)
P21 associado a:
P22 associado a:
P23 associado a:
P24 associado a:
P25 associado a:
P26 associado a:
P27 associado a: (nome = E30, preferencia = 1, vaga = 1)
P28 associado a: (nome = E28, preferencia = 1, vaga = 1)
P29 associado a: (nome = E45, preferencia = 1, vaga = 1)
P30 associado a: (nome = E45, preferencia = 1, vaga = 2)
P31 associado a:
P32 associado a: (nome = E50, preferencia = 1, vaga = 1)
P33 associado a: (nome = E33, preferencia = 3, vaga = 2)
P34 associado a: (nome = E34, preferencia = 3, vaga = 2)
P35 associado a:
P36 associado a: (nome = E50, preferencia = 2, vaga = 2)
P37 associado a: (nome = E32, preferencia = 4, vaga = 2)
P38 associado a: (nome = E38, preferencia = 3, vaga = 2)
P39 associado a: (nome = E39, preferencia = 1, vaga = 2)
P40 associado a:
P41 associado a: (nome = E40, preferencia = 1, vaga = 2)
P42 associado a:
P43 associado a:
P44 associado a: (nome = E40, preferencia = 1, vaga = 1)
P45 associado a: (nome = E11, preferencia = 3, vaga = 2)
P46 associado a: (nome = E46, preferencia = 2, vaga = 1)
P47 associado a:
P48 associado a:
P49 associado a: (nome = E6, preferencia = 2, vaga = 1)
P50 associado a:
P51 associado a:
P52 associado a:
P53 associado a: (nome = E48, preferencia = 1, vaga = 1)
P54 associado a: (nome = E47, preferencia = 1, vaga = 1)
P55 associado a: (nome = E46, preferencia = 1, vaga = 2)
P56 associado a:
P57 associado a: (nome = E44, preferencia = 1, vaga = 1)
P58 associado a: (nome = E43, preferencia = 1, vaga = 2)
P59 associado a: (nome = E42, preferencia = 1, vaga = 1)
P60 associado a: (nome = E8, preferencia = 1, vaga = 1)
P61 associado a:
P62 associado a: (nome = E39, preferencia = 1, vaga = 1)
P63 associado a: (nome = E38, preferencia = 1, vaga = 1)
P64 associado a: (nome = E37, preferencia = 1, vaga = 1)
P65 associado a: (nome = E13, preferencia = 2, vaga = 1)
P66 associado a: (nome = E35, preferencia = 1, vaga = 1)
P67 associado a: (nome = E34, preferencia = 1, vaga = 1)
P68 associado a: (nome = E33, preferencia = 1, vaga = 1)
P69 associado a: (nome = E32, preferencia = 1, vaga = 1)
P70 associado a: (nome = E12, preferencia = 2, vaga = 1)
P71 associado a: (nome = E35, preferencia = 3, vaga = 2)
P72 associado a: (nome = E1, preferencia = 2, vaga = 1)
P73 associado a: (nome = E28, preferencia = 1, vaga = 2)
P74 associado a: (nome = E27, preferencia = 1, vaga = 1)
P75 associado a: (nome = E24, preferencia = 3, vaga = 1)
P76 associado a: (nome = E25, preferencia = 1, vaga = 2)
P77 associado a: (nome = E24, preferencia = 1, vaga = 2)
P78 associado a: (nome = E23, preferencia = 1, vaga = 2)
P79 associado a: (nome = E22, preferencia = 1, vaga = 2)
P80 associado a: (nome = E21, preferencia = 1, vaga = 1)
P81 associado a:
P82 associado a: (nome = E19, preferencia = 1, vaga = 2)
P83 associado a: (nome = E27, preferencia = 2, vaga = 2)
P84 associado a:
P85 associado a: (nome = E16, preferencia = 1, vaga = 1)
P86 associado a: (nome = E15, preferencia = 1, vaga = 2)
P87 associado a: (nome = E14, preferencia = 1, vaga = 2)
P88 associado a: (nome = E37, preferencia = 3, vaga = 2)
P89 associado a:
P90 associado a: (nome = E11, preferencia = 1, vaga = 1)
P91 associado a:
P92 associado a: (nome = E9, preferencia = 1, vaga = 1)
P93 associado a:
P94 associado a:
P95 associado a: (nome = E47, preferencia = 2, vaga = 2)
P96 associado a: (nome = E5, preferencia = 1, vaga = 1)
P97 associado a: (nome = E4, preferencia = 1, vaga = 1)
P98 associado a:
P99 associado a: (nome = E2, preferencia = 1, vaga = 1)
P100 associado a:

E1 associado a: (nome = P72, preferencia = 2, vaga = 1)
E2 associado a: (nome = P99, preferencia = 1, vaga = 1)
E3 associado a: (nome = P1, preferencia = 4, vaga = 1)
E4 associado a: (nome = P97, preferencia = 1, vaga = 1)
E5 associado a: (nome = P96, preferencia = 1, vaga = 1)
E6 associado a: (nome = P49, preferencia = 2, vaga = 1)
E7 associado a: (nome = P10, preferencia = 2, vaga = 1)
E8 associado a: (nome = P60, preferencia = 1, vaga = 1)
E9 associado a: (nome = P92, preferencia = 1, vaga = 1)
E10 associado a: (nome = P7, preferencia = 1, vaga = 1) (nome = P3, preferencia = 1, vaga = 2)
E11 associado a: (nome = P90, preferencia = 1, vaga = 1) (nome = P45, preferencia = 3, vaga = 2)
E12 associado a: (nome = P70, preferencia = 2, vaga = 1)
E13 associado a: (nome = P65, preferencia = 2, vaga = 1)
E14 associado a: (nome = P87, preferencia = 1, vaga = 2)
E15 associado a: (nome = P86, preferencia = 1, vaga = 2)
E16 associado a: (nome = P85, preferencia = 1, vaga = 1)
E17 associado a:
E18 associado a:
E19 associado a: (nome = P82, preferencia = 1, vaga = 2)
E20 associado a: (nome = P15, preferencia = 1, vaga = 1) (nome = P16, preferencia = 1, vaga = 2)
E21 associado a: (nome = P80, preferencia = 1, vaga = 1) (nome = P9, preferencia = 4, vaga = 2)
E22 associado a: (nome = P79, preferencia = 1, vaga = 2)
E23 associado a: (nome = P78, preferencia = 1, vaga = 2)
E24 associado a: (nome = P75, preferencia = 3, vaga = 1) (nome = P77, preferencia = 1, vaga = 2)
E25 associado a: (nome = P76, preferencia = 1, vaga = 2)
E26 associado a:
E27 associado a: (nome = P74, preferencia = 1, vaga = 1) (nome = P83, preferencia = 2, vaga = 2)
E28 associado a: (nome = P28, preferencia = 1, vaga = 1) (nome = P73, preferencia = 1, vaga = 2)
E29 associado a: (nome = P13, preferencia = 4, vaga = 1)
E30 associado a: (nome = P27, preferencia = 1, vaga = 1)
E31 associado a: (nome = P14, preferencia = 4, vaga = 1)
E32 associado a: (nome = P69, preferencia = 1, vaga = 1) (nome = P37, preferencia = 4, vaga = 2)
E33 associado a: (nome = P68, preferencia = 1, vaga = 1) (nome = P33, preferencia = 3, vaga = 2)
E34 associado a: (nome = P67, preferencia = 1, vaga = 1) (nome = P34, preferencia = 3, vaga = 2)
E35 associado a: (nome = P66, preferencia = 1, vaga = 1) (nome = P71, preferencia = 3, vaga = 2)
E36 associado a:
E37 associado a: (nome = P64, preferencia = 1, vaga = 1) (nome = P88, preferencia = 3, vaga = 2)
E38 associado a: (nome = P63, preferencia = 1, vaga = 1) (nome = P38, preferencia = 3, vaga = 2)
E39 associado a: (nome = P62, preferencia = 1, vaga = 1) (nome = P39, preferencia = 1, vaga = 2)
E40 associado a: (nome = P44, preferencia = 1, vaga = 1) (nome = P41, preferencia = 1, vaga = 2)
E41 associado a: (nome = P19, preferencia = 4, vaga = 1)
E42 associado a: (nome = P59, preferencia = 1, vaga = 1)
E43 associado a: (nome = P20, preferencia = 4, vaga = 1) (nome = P58, preferencia = 1, vaga = 2)
E44 associado a: (nome = P57, preferencia = 1, vaga = 1)
E45 associado a: (nome = P29, preferencia = 1, vaga = 1) (nome = P30, preferencia = 1, vaga = 2)
E46 associado a: (nome = P46, preferencia = 2, vaga = 1) (nome = P55, preferencia = 1, vaga = 2)
E47 associado a: (nome = P54, preferencia = 1, vaga = 1) (nome = P95, preferencia = 2, vaga = 2)
E48 associado a: (nome = P53, preferencia = 1, vaga = 1)
E49 associado a:
E50 associado a: (nome = P32, preferencia = 1, vaga = 1) (nome = P36, preferencia = 2, vaga = 2)

Professores satisfeitos: 65
Professores alocados: 65

|| Emparelhamento alocando todos os professores que restam ||

P1 associado a: (nome = E3, preferencia = 4, vaga = 1)
P2 associado a:
P3 associado a: (nome = E10, preferencia = 1, vaga = 2)
P4 associado a:
P5 associado a: (nome = E13, preferencia = 5, vaga = 2)
P6 associado a:
P7 associado a: (nome = E10, preferencia = 1, vaga = 1)
P8 associado a:
P9 associado a: (nome = E21, preferencia = 4, vaga = 2)
P10 associado a: (nome = E7, preferencia = 2, vaga = 1)
P11 associado a: (nome = E26, preferencia = 5, vaga = 1)
P12 associado a: (nome = E29, preferencia = 5, vaga = 2)
P13 associado a: (nome = E29, preferencia = 4, vaga = 1)
P14 associado a: (nome = E31, preferencia = 4, vaga = 1)
P15 associado a: (nome = E20, preferencia = 1, vaga = 1)
P16 associado a: (nome = E20, preferencia = 1, vaga = 2)
P17 associado a: (nome = E36, preferencia = 5, vaga = 1)
P18 associado a: (nome = E41, preferencia = 5, vaga = 2)
P19 associado a: (nome = E41, preferencia = 4, vaga = 1)
P20 associado a: (nome = E43, preferencia = 4, vaga = 1)
P21 associado a: (nome = E26, preferencia = 5, vaga = 2)
P22 associado a:
P23 associado a:
P24 associado a:
P25 associado a: (nome = E18, preferencia = 5, vaga = 1)
P26 associado a:
P27 associado a: (nome = E30, preferencia = 1, vaga = 1)
P28 associado a: (nome = E28, preferencia = 1, vaga = 1)
P29 associado a: (nome = E45, preferencia = 1, vaga = 1)
P30 associado a: (nome = E45, preferencia = 1, vaga = 2)
P31 associado a: (nome = E36, preferencia = 5, vaga = 2)
P32 associado a: (nome = E50, preferencia = 1, vaga = 1)
P33 associado a: (nome = E33, preferencia = 3, vaga = 2)
P34 associado a: (nome = E34, preferencia = 3, vaga = 2)
P35 associado a: (nome = E49, preferencia = 5, vaga = 1)
P36 associado a: (nome = E50, preferencia = 2, vaga = 2)
P37 associado a: (nome = E32, preferencia = 4, vaga = 2)
P38 associado a: (nome = E38, preferencia = 3, vaga = 2)
P39 associado a: (nome = E39, preferencia = 1, vaga = 2)
P40 associado a: (nome = E12, preferencia = 5, vaga = 2)
P41 associado a: (nome = E40, preferencia = 1, vaga = 2)
P42 associado a:
P43 associado a:
P44 associado a: (nome = E40, preferencia = 1, vaga = 1)
P45 associado a: (nome = E11, preferencia = 3, vaga = 2)
P46 associado a: (nome = E46, preferencia = 2, vaga = 1)
P47 associado a:
P48 associado a:
P49 associado a: (nome = E6, preferencia = 2, vaga = 1)
P50 associado a: (nome = E14, preferencia = 5, vaga = 1)
P51 associado a:
P52 associado a:
P53 associado a: (nome = E48, preferencia = 1, vaga = 1)
P54 associado a: (nome = E47, preferencia = 1, vaga = 1)
P55 associado a: (nome = E46, preferencia = 1, vaga = 2)
P56 associado a:
P57 associado a: (nome = E44, preferencia = 1, vaga = 1)
P58 associado a: (nome = E43, preferencia = 1, vaga = 2)
P59 associado a: (nome = E42, preferencia = 1, vaga = 1)
P60 associado a: (nome = E8, preferencia = 1, vaga = 1)
P61 associado a:
P62 associado a: (nome = E39, preferencia = 1, vaga = 1)
P63 associado a: (nome = E38, preferencia = 1, vaga = 1)
P64 associado a: (nome = E37, preferencia = 1, vaga = 1)
P65 associado a: (nome = E13, preferencia = 2, vaga = 1)
P66 associado a: (nome = E35, preferencia = 1, vaga = 1)
P67 associado a: (nome = E34, preferencia = 1, vaga = 1)
P68 associado a: (nome = E33, preferencia = 1, vaga = 1)
P69 associado a: (nome = E32, preferencia = 1, vaga = 1)
P70 associado a: (nome = E12, preferencia = 2, vaga = 1)
P71 associado a: (nome = E35, preferencia = 3, vaga = 2)
P72 associado a: (nome = E1, preferencia = 2, vaga = 1)
P73 associado a: (nome = E28, preferencia = 1, vaga = 2)
P74 associado a: (nome = E27, preferencia = 1, vaga = 1)
P75 associado a: (nome = E24, preferencia = 3, vaga = 1)
P76 associado a: (nome = E25, preferencia = 1, vaga = 2)
P77 associado a: (nome = E24, preferencia = 1, vaga = 2)
P78 associado a: (nome = E23, preferencia = 1, vaga = 2)
P79 associado a: (nome = E22, preferencia = 1, vaga = 2)
P80 associado a: (nome = E21, preferencia = 1, vaga = 1)
P81 associado a:
P82 associado a: (nome = E19, preferencia = 1, vaga = 2)
P83 associado a: (nome = E27, preferencia = 2, vaga = 2)
P84 associado a:
P85 associado a: (nome = E16, preferencia = 1, vaga = 1)
P86 associado a: (nome = E15, preferencia = 1, vaga = 2)
P87 associado a: (nome = E14, preferencia = 1, vaga = 2)
P88 associado a: (nome = E37, preferencia = 3, vaga = 2)
P89 associado a:
P90 associado a: (nome = E11, preferencia = 1, vaga = 1)
P91 associado a:
P92 associado a: (nome = E9, preferencia = 1, vaga = 1)
P93 associado a:
P94 associado a:
P95 associado a: (nome = E47, preferencia = 2, vaga = 2)
P96 associado a: (nome = E5, preferencia = 1, vaga = 1)
P97 associado a: (nome = E4, preferencia = 1, vaga = 1)
P98 associado a:
P99 associado a: (nome = E2, preferencia = 1, vaga = 1)
P100 associado a: (nome = E17, preferencia = 5, vaga = 1)

E1 associado a: (nome = P72, preferencia = 2, vaga = 1)
E2 associado a: (nome = P99, preferencia = 1, vaga = 1)
E3 associado a: (nome = P1, preferencia = 4, vaga = 1)
E4 associado a: (nome = P97, preferencia = 1, vaga = 1)
E5 associado a: (nome = P96, preferencia = 1, vaga = 1)
E6 associado a: (nome = P49, preferencia = 2, vaga = 1)
E7 associado a: (nome = P10, preferencia = 2, vaga = 1)
E8 associado a: (nome = P60, preferencia = 1, vaga = 1)
E9 associado a: (nome = P92, preferencia = 1, vaga = 1)
E10 associado a: (nome = P7, preferencia = 1, vaga = 1) (nome = P3, preferencia = 1, vaga = 2)
E11 associado a: (nome = P90, preferencia = 1, vaga = 1) (nome = P45, preferencia = 3, vaga = 2)
E12 associado a: (nome = P70, preferencia = 2, vaga = 1) (nome = P40, preferencia = 5, vaga = 2)
E13 associado a: (nome = P65, preferencia = 2, vaga = 1) (nome = P5, preferencia = 5, vaga = 2)
E14 associado a: (nome = P50, preferencia = 5, vaga = 1) (nome = P87, preferencia = 1, vaga = 2)
E15 associado a: (nome = P86, preferencia = 1, vaga = 2)
E16 associado a: (nome = P85, preferencia = 1, vaga = 1)
E17 associado a: (nome = P100, preferencia = 5, vaga = 1)
E18 associado a: (nome = P25, preferencia = 5, vaga = 1)
E19 associado a: (nome = P82, preferencia = 1, vaga = 2)
E20 associado a: (nome = P15, preferencia = 1, vaga = 1) (nome = P16, preferencia = 1, vaga = 2)
E21 associado a: (nome = P80, preferencia = 1, vaga = 1) (nome = P9, preferencia = 4, vaga = 2)
E22 associado a: (nome = P79, preferencia = 1, vaga = 2)
E23 associado a: (nome = P78, preferencia = 1, vaga = 2)
E24 associado a: (nome = P75, preferencia = 3, vaga = 1) (nome = P77, preferencia = 1, vaga = 2)
E25 associado a: (nome = P76, preferencia = 1, vaga = 2)
E26 associado a: (nome = P11, preferencia = 5, vaga = 1) (nome = P21, preferencia = 5, vaga = 2)
E27 associado a: (nome = P74, preferencia = 1, vaga = 1) (nome = P83, preferencia = 2, vaga = 2)
E28 associado a: (nome = P28, preferencia = 1, vaga = 1) (nome = P73, preferencia = 1, vaga = 2)
E29 associado a: (nome = P13, preferencia = 4, vaga = 1) (nome = P12, preferencia = 5, vaga = 2)
E30 associado a: (nome = P27, preferencia = 1, vaga = 1)
E31 associado a: (nome = P14, preferencia = 4, vaga = 1)
E32 associado a: (nome = P69, preferencia = 1, vaga = 1) (nome = P37, preferencia = 4, vaga = 2)
E33 associado a: (nome = P68, preferencia = 1, vaga = 1) (nome = P33, preferencia = 3, vaga = 2)
E34 associado a: (nome = P67, preferencia = 1, vaga = 1) (nome = P34, preferencia = 3, vaga = 2)
E35 associado a: (nome = P66, preferencia = 1, vaga = 1) (nome = P71, preferencia = 3, vaga = 2)
E36 associado a: (nome = P17, preferencia = 5, vaga = 1) (nome = P31, preferencia = 5, vaga = 2)
E37 associado a: (nome = P64, preferencia = 1, vaga = 1) (nome = P88, preferencia = 3, vaga = 2)
E38 associado a: (nome = P63, preferencia = 1, vaga = 1) (nome = P38, preferencia = 3, vaga = 2)
E39 associado a: (nome = P62, preferencia = 1, vaga = 1) (nome = P39, preferencia = 1, vaga = 2)
E40 associado a: (nome = P44, preferencia = 1, vaga = 1) (nome = P41, preferencia = 1, vaga = 2)
E41 associado a: (nome = P19, preferencia = 4, vaga = 1) (nome = P18, preferencia = 5, vaga = 2)
E42 associado a: (nome = P59, preferencia = 1, vaga = 1)
E43 associado a: (nome = P20, preferencia = 4, vaga = 1) (nome = P58, preferencia = 1, vaga = 2)
E44 associado a: (nome = P57, preferencia = 1, vaga = 1)
E45 associado a: (nome = P29, preferencia = 1, vaga = 1) (nome = P30, preferencia = 1, vaga = 2)
E46 associado a: (nome = P46, preferencia = 2, vaga = 1) (nome = P55, preferencia = 1, vaga = 2)
E47 associado a: (nome = P54, preferencia = 1, vaga = 1) (nome = P95, preferencia = 2, vaga = 2)
E48 associado a: (nome = P53, preferencia = 1, vaga = 1)
E49 associado a: (nome = P35, preferencia = 5, vaga = 1)
E50 associado a: (nome = P32, preferencia = 1, vaga = 1) (nome = P36, preferencia = 2, vaga = 2)

Professores satisfeitos: 65
Professores alocados: 77