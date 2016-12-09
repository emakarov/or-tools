************************************************************************
file with basedata            : cr162_.bas
initial value random generator: 778787766
************************************************************************
projects                      :  1
jobs (incl. supersource/sink ):  18
horizon                       :  120
RESOURCES
  - renewable                 :  1   R
  - nonrenewable              :  2   N
  - doubly constrained        :  0   D
************************************************************************
PROJECT INFORMATION:
pronr.  #jobs rel.date duedate tardcost  MPM-Time
    1     16      0       20       13       20
************************************************************************
PRECEDENCE RELATIONS:
jobnr.    #modes  #successors   successors
   1        1          3           2   3   4
   2        3          3           5   6   9
   3        3          3           7  11  16
   4        3          3           8   9  17
   5        3          3           7  11  12
   6        3          1           7
   7        3          3          13  14  15
   8        3          1          10
   9        3          2          15  16
  10        3          1          15
  11        3          2          13  14
  12        3          3          13  14  16
  13        3          1          17
  14        3          1          17
  15        3          1          18
  16        3          1          18
  17        3          1          18
  18        1          0        
************************************************************************
REQUESTS/DURATIONS:
jobnr. mode duration  R 1  N 1  N 2
------------------------------------------------------------------------
  1      1     0       0    0    0
  2      1     3       3    6   10
         2     4       2    6    5
         3     4       1    6    6
  3      1     1       7    9    5
         2     6       6    8    5
         3     8       4    7    4
  4      1     3       5    3    2
         2     3       7    2    2
         3     5       3    2    2
  5      1     4       8    8    7
         2     5       7    7    6
         3     9       7    6    6
  6      1     2       8    9    9
         2     4       8    9    6
         3     6       5    9    3
  7      1     6       6   10    2
         2     8       6    6    1
         3     8       5    7    2
  8      1     6       9    7    8
         2     6       9    5    9
         3     7       9    3    7
  9      1     6       8    4    7
         2     7       7    3    5
         3    10       6    3    3
 10      1     3       9   10    2
         2     4       6    9    2
         3     9       4    8    2
 11      1     4       8    5    5
         2     5       6    5    5
         3     8       5    2    4
 12      1     3       7    6    9
         2     7       7    6    7
         3     8       6    6    3
 13      1     1       7    6    5
         2     1       6    2   10
         3     1       7    4    7
 14      1     1       7   10    6
         2     7       6    8    4
         3     9       4    8    3
 15      1     1       7   10    6
         2     4       6   10    6
         3     8       6    9    6
 16      1     3       9    6    4
         2     6       7    5    4
         3    10       3    3    3
 17      1     6       6   10    5
         2     6       7   10    4
         3    10       5    9    2
 18      1     0       0    0    0
************************************************************************
RESOURCEAVAILABILITIES:
  R 1  N 1  N 2
   24  119   98
************************************************************************