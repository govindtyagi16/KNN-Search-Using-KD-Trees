# K-Nearest-Neighbour-Algorithm-using-K-D-Trees
Implementation of K-Nearest-Neighbour Algorithm using K-D Tree and custom build Priority Queue. From a given dataset, it gives us the nearest neighbour and K number of neighbours to any given point.

To run the program, compile and execute the main.c file

# Input
The input is taken from input.txt file<br>

1st line: Dimensions - d<br>
2nd line: Number of neighbours to find - K<br>
3rd line: Number of input points of d dimension - number_points<br>
4th line: the data point for which the neighbours are to be found <br>
Then the data points are input line by line number_point times<br>

For the given input file, the dataset repesent the following-<br>
The columns are equal to the number of dimensions of the data points

# Output
The program will give the K nearest neighbours for the given point.

For the given input file:-<br>
Given the number of dimensions - 4<br>
Number of nearest neighbours to find- 10<br>
Number of data points given - 10000<br>
The data point around which neighbours to find - {689-7890-55-909}<br>

Output on terminal:-<br>

Result of Application OF Nearest Algorithm:<br>
1 Nearest Point is {1446-5886-2679-699} at a Distance: 3393.897317 <br>


Results of Application OF KNN Algorithm :<br>
1 Nearest Point is {1446-5886-2679-699} at a Distance: 3393.897317 <br>
2 Nearest Point is {2870-7522-474-3499} at a Distance: 3431.595256 <br>
3 Nearest Point is {2138-10700-530-2461} at a Distance: 3553.874927<br>
4 Nearest Point is {4343-9578-1187-113} at a Distance: 4256.301094 <br>
5 Nearest Point is {4543-9680-110-1618} at a Distance: 4308.494169 <br>
6 Nearest Point is {3967-7037-2663-43} at a Distance: 4361.709757  <br>
7 Nearest Point is {1005-4940-2989-2625} at a Distance: 4511.692144<br>
8 Nearest Point is {5133-8413-2210-994} at a Distance: 4967.284369  <br>
9 Nearest Point is {3322-13287-334-703} at a Distance: 6015.028928  <br>
10 Nearest Point is {4872-8106-3656-3343} at a Distance: 6036.199218<br>
