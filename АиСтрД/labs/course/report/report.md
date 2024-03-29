---
title: 'Отчет по Курсовой работе по АиСтрД'
date: 2019-12-15
---

## Задание

Построить полное множество циклов для ориентированного графа.

## Математическая формулировка

Введем некоторые термины из теории графов.

Ориентированным графом называется пара $V$ -- множество вершин и $E$ --
множество дуг (ориентированных ребер), где дуга -- упорядоченная пара вершин $(v, w)$.

Путь -- это такая последовательность дуг, что конец одной дуги является началом
другой. Путь, который начинается и заканчивается в одной и той же вершине,
называется циклом. Все возможные циклы графа образуют полное множество циклов
графа.

Итак, дан граф $G = (V, E)$, где $V = \{v_1, v_2, \ldots, v_N\}$, $E = \{(v_i,
v_j)\}, 1 \le i,j \le N, i \ne j$. Необходимо найти множество $M = \{(v_i,
v_{k1}), (v_{k1}, v_{k2}), \ldots,$ $(v_{kn}, v_i)\}, 1 \le i,k_1,\ldots,k_n \le N,
i \ne k_j$.

В процессе реализации алгоритма нам также потребуется понятие поиска в глубину
(DFS). Это название одного из методов обхода графа, общая идея которого
заключается в том, что для каждой не пройденной вершины нужно рассмотреть все
не пройденные смежные и повторить поиск для них,то есть следует двигаться
вглубь графа насколько это возможно.

## Способ представления данных

В программе используется два способа представления графа: список ребер (в
таком виде граф хранится в файле) и список смежности.

Список ребер был выбран из соображений простоты чтения из файла (как
компьютера, так и человека) и дальнейшего парсинга.

Список ребер был выбран по причине нетребовательности к памяти, простоты
получения списка соседей. Остальные либо
требовательнее к памяти (матрица смежности, матрица инцидентности), либо слабо
подходят для представления орграфа (связный список).

## Описание алгоритма

Будем реализовывать переборный алгоритм, основная идея которого
заключается в последовательном применении поиска в глубину к каждой
вершине графа для определения всех путей, которые начинаются и
заканчиваются в вершине, из которой был запущен поиск.

Алгоритм:

1.  Берем следующую вершину графа $u$, из которой еще не запускали
    DFS.

2. Вызываем DFS(u, u).

3. DFS(start, v):

   *   Инициализировать пустной список путей.
   *   Отметить вершину $v$ как просмотренную.
   *   Для каждой непосещенной (только DFS) смежной вершины $w$
       выполнить DFS($v$, $w$). Добавить пути, которые вернул DFS, в список
       путей, причем к каждому пути следует добавить $w$.
   *   Если смежная вершина равна $start$, то добавить новый путь, состоящий из
       вершины $start$, в список путей.
   *   Вернуть список путей.

В результате получим список всех циклов.

## Временная сложность алгоритма

Оценим временную сложность. В худшем случае потребуется оботи все вершины и вызвать для каждой вершины DFS.
Как известно, сложность DFS составляет $O(|V| + |E|)$. Тогда общая сложность будет

$$ O(|V|(|V| + |E|) = O(|V|^2 + |V||E|) = O(|V|^2). $$

## Примеры

![Пример 1](res/sample1.png)

![Пример 2](res/sample2.png)

![Пример 3](res/sample3.png)

## Вывод

В ходе выполнения курсовой работы изучены различные способы представления
графов в памяти компьютера (с целью выбора наилучшего для конкретного
алгоритма). Был получен опыт в реализации переборных алгоритмах на графах, а
также практический опыт применения мощных средств языка C++ таких, как
наследование, полиморфизм, стандартные контейнеры, указатели и другие.

## Список литературы

1.  Колинько П.Г. Алгоритмы и структуры данных. Часть 1: Методические
    указания к самостоятельной работе на ПЭВМ и курсовому проектированию.
    Вып. 1909. -- СПб.: СПбГЭТУ «ЛЭТИ», 2019. -- 69 с.

2.  Иванов Б. Н. Дискретная математика. Алгоритмы и программы: Учеб. пособие.
    -- М.: Лаборатория Базовых Знаний, 2001 -- 288 с. 

3. Скиена С. Алгоритмы. Руководство по разработке. -- 2-е изд.: Пер. с англ.
   -- СПб.: БХВ-Петербург, 2016. -- 720 с.: ил.

4. C++ reference // Справка по языку C++. https://en.cppreference.com/
   Просмотрено: 15.12.2019.

\newpage
## Приложение А. Код программы.
\lstinputlisting{../main.cpp}

\lstinputlisting{../graph-data.h}
\lstinputlisting{../graph-source.h}
\lstinputlisting{../graph.h}
\lstinputlisting{../node.h}

\lstinputlisting{../graph-data.cpp}
\lstinputlisting{../graph-source.cpp}
\lstinputlisting{../graph.cpp}
\lstinputlisting{../node.cpp}