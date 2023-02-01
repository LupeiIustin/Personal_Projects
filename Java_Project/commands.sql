DROP TABLE commands;

CREATE TABLE commands(createdBy VARCHAR2(50), id INTEGER, name VARCHAR2(50), description VARCHAR2(3000));


INSERT INTO commands VALUES('Lupei Iustin',1, 'menger', 'Teorema lui Menger  -  Fie G un grafic finit nedirecționat și s și t două vârfuri distincte. Numărul minim de muchii de eliminat pentru a deconecta s și t este egal cu numărul maxim de căi disjuncte de margine ale G care conectează s și t ."
                      --                      + "  https://profs.info.uaic.ro/~olariu/curent/AG/files/agr5.pdf ');
INSERT INTO commands VALUES('Lupei Iustin',2, 'dijkstra', 'Dijkstra s algorithm is an algorithm for finding the shortest paths between nodes in a graph, which may represent, for example, road networks. ');

INSERT INTO commands VALUES('Lupei Iustin',3, 'bellmanfordsalgorithm', 'Bellman Ford s algorithm is a shortest path finding algorithm for graphs that can have negative weights. Bellman ford''s algorithm is also great for detecting negative weight cycles as the algorithm converges to an optimal solution in O(V*E) steps. If the resultant is not optimal, then graph contains a negative weight cycle.');

INSERT INTO commands VALUES('Lupei Iustin',4, 'dfs', 'Depth First Search is one of the most simple graph algorithms. It traverses the graph by first checking the current node and then moving to one of its sucessors to repeat the process. If the current node has no sucessor to check, we move back to its predecessor and the process continues (by moving to another sucessor). If the solution is found the search stops.');

--INSERT INTO commands VALUES(5, '', '');
--INSERT INTO commands VALUES(6, '', '');
--INSERT INTO commands VALUES(7, '', '');
--INSERT INTO commands VALUES(8, '', '');