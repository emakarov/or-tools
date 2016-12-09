************************************************************************
file with basedata            : c1515_.bas
initial value random generator: 224309507
************************************************************************
projects                      :  1
jobs (incl. supersource/sink ):  18
horizon                       :  115
RESOURCES
  - renewable                 :  2   R
  - nonrenewable              :  2   N
  - doubly constrained        :  0   D
************************************************************************
PROJECT INFORMATION:
pronr.  #jobs rel.date duedate tardcost  MPM-Time
    1     16      0       27        4       27
************************************************************************
PRECEDENCE RELATIONS:
jobnr.    #modes  #successors   successors
   1        1          3           2   3   4
   2        3          3           5   8  17
   3        3          2           7  12
   4        3          2          15  16
   5        3          3           6   7   9
   6        3          1          14
   7        3          1          10
   8        3          2          11  13
   9        3          1          14
  10        3          1          16
  11        3          1          15
  12        3          1          13
  13        3          2          14  16
  14        3          1          15
  15        3          1          18
  16        3          1          18
  17        3          1          18
  18        1          0        
************************************************************************
REQUESTS/DURATIONS:
jobnr. mode duration  R 1  R 2  N 1  N 2
------------------------------------------------------------------------
  1      1     0       0    0    0    0
  2      1     7       2    7    2    0
         2    10       2    3    0    5
         3    10       2    4    2    0
  3      1     1       7    8    0    6
         2     2       4    7    8    0
         3     4       3    7    0    1
  4      1     3       5    6    0    1
         2     4       5    5    0    1
         3     5       5    4    0    1
  5      1     2       4    9    0    7
         2     4       4    5    9    0
         3     6       2    4    0    3
  6      1     1       6    7    0    7
         2     4       6    5   10    0
         3     5       5    4    0    3
  7      1     1       4   10    2    0
         2     6       4    8    2    0
         3     7       3    7    0    7
  8      1     6       5    8    0    6
         2     7       3    2    4    0
         3     7       1    4    0    3
  9      1     2       7    9    0    6
         2     3       5    8    7    0
         3     5       2    7    0    4
 10      1     2       4    6    9    0
         2     4       3    5    0    5
         3     7       1    5    0    4
 11      1     4       8    8   10    0
         2     6       6    5    0    7
         3    10       3    4   10    0
 12      1     2       8    9    2    0
         2     3       8    7    0    1
         3     9       6    4    2    0
 13      1     7       3    3   10    0
         2     9       2    2    7    0
         3    10       1    2    6    0
 14      1     1       5    4    0    5
         2     1       5    3    3    0
         3     4       3    3    0    5
 15      1     2       5   10    0    1
         2     5       5    9    7    0
         3     8       3    9    5    0
 16      1     7       4    8    5    0
         2     8       4    6    0    8
         3     8       4    5    5    0
 17      1     7       9    4    5    0
         2     8       7    3    0    8
         3    10       6    3    0    1
 18      1     0       0    0    0    0
************************************************************************
RESOURCEAVAILABILITIES:
  R 1  R 2  N 1  N 2
   25   31   50   41
************************************************************************