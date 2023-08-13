#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>

// D IS DIMENSION OF K-TREE
// K IS NO OF NEAREST NEIGHBOURS WE WANT TO FIND

struct Node_Queue 
// Making a structure which creates priority queue
{
    long long int *arr;// Stores the points in array
    long long int priority;// Stores the distance of point from target point
};
typedef struct Node_Queue node_queue ;

node_queue * queue = NULL;
long long int size = -1;
// Declaring a global queue and size of that queue

void enqueue(long long int array[], long long int dist, long long int d)
// Function to insert element in the priority queue
{
    size++;
    if (size>0)
    {
        queue = (node_queue*)realloc(queue,(size+1)*sizeof(node_queue));
    }
    queue[size].arr = (long long int*)malloc(d*sizeof(long long int)); 
    // Allocating size to queue and each arr in queue
    for (long long int i = 0; i < d; i++)
    {
        queue[size].arr[i]=array[i];
    }
    queue[size].priority = dist;
    // Inserting the array and distance as priority to the queue
}

long long int max_index(long long int k,long long int d)
//finding the index of the max element in the queue
{
    long long int largest = 0;
    for (long long int i = 1; i < k; i++)
    {
        if (queue[largest].priority<=queue[i].priority)
        {
            largest=i;
        }
    }
    return largest;
    // Returning the Index of largest Element priority in priority queue
}

struct Node
//structure of node of K-D Tree
{
    long long int *point;
    struct Node *left, *right;
};
typedef struct Node node;

node* new_node(long long int arr[],long long int d)
// Creating new node in tree
{
    node* newnode= (node*)malloc(sizeof(node));
    newnode->point= (long long int*)malloc(d*sizeof(long long int));

    for (int i = 0; i < d; i++)
    {
        *(newnode->point+i)=arr[i];
    }
    newnode->left=NULL;
    newnode->right=NULL;
    return newnode;
}   

node* insert(node* root, long long int arr[], long long int depth, long long int d)
// Inserting a point in tree by comparing values at depth%k
{
    if (root==NULL)
    {
        return new_node(arr,d);
    }
    long long int dimension= depth%d;
    if (*(root->point+dimension)<=arr[dimension])
    {
        root->right=insert(root->right,arr,depth+1,d);
    }
    else
    {
        root->left=insert(root->left,arr,depth+1,d);
    }
    return root;
}

long long int search_node(node* root, long long int arr[], long long int depth, long long int d)
// Searching for a point in the tree
{
    if (root == NULL)
    {
        return 0;
    }
    long long int flag=1;
    for (long long int i = 0; i < d; ++i)
    {
        if (root->point[i] != arr[i])
        {
            flag=0;
            break;
        }
    }
    if (flag==1)
    {
        return 1;
    }
    long long int dimension = depth % d;
    if (*(root->point+dimension)<=arr[dimension])
    {
        return search_node(root->right, arr, depth + 1, d);
    }
    else
    {
        return search_node(root->left, arr, depth + 1, d);
    }   
}

long long int distancesqaured(long long int point1[], long long int *point2, long long int d)
// Calculating Eucledian distance between Two Points
{
    long long int distance=0;
    for (long long int i = 0; i < d; i++)
    {
        distance=distance+pow(point1[i]-point2[i],2);
    }
    return distance;
}

node* closestnode(node* node2, node* node3, long long int point1[],  long long int d)
// Function to get the closet of the two nodes from the Point
{
    if (node2 == NULL) 
    {
        return node3;
    }

    if (node3 == NULL) 
    {
        return node2;
    }

    long long int d1 = distancesqaured(point1, node2->point, d);
    // Distance of point 1 from node2 
    long long int d2 = distancesqaured(point1, node3->point, d);
    // Distance of point 1 from node 3

    if (d1 < d2)
    {
        return node2;
    }
    else
    {
        return node3;
    }
}

node * nearestNeighbour(node* root, long long int point1[], long long int depth, long long int d)
// Function to the get the nearest Neighbour
{
    node* bestBranch;
    node* otherBranch;
    if (root==NULL)
    {
        return NULL;
    }

    if (point1[depth % d] < root->point[depth % d])
    {
        bestBranch = root->left;
        otherBranch = root->right;
    }
    else
    {
        bestBranch = root->right;
        otherBranch = root->left;
    }

    node* temp = nearestNeighbour(bestBranch,point1,depth+1,d);
    node* best_till_now = closestnode(temp, root, point1, d);

    long long int sqaureofdistance = distancesqaured(point1, best_till_now->point, d);
    long long int distanc = point1[depth%d] - root->point[depth%d];

    if (sqaureofdistance >= distanc*distanc)
    {
        temp = nearestNeighbour(otherBranch, point1, depth+1, d);
        best_till_now = closestnode(temp, best_till_now, point1, d);
    }

    return best_till_now;
}

void knearestNeighbour(node* root, long long int point1[], long long int depth, long long int d, long long int k)
// Function to get the K nearest Points in a queue using KNN Algorithm
{
    node* bestBranch;
    node* otherBranch;
    if (root==NULL)
    {
        return;
    }

    if (point1[depth % d] < root->point[depth % d])
    {
        bestBranch = root->left;
        otherBranch = root->right;
    }
    else
    {
        bestBranch = root->right;
        otherBranch = root->left;
    }

    knearestNeighbour(bestBranch,point1,depth+1,d,k);
    long long int distanc = distancesqaured(point1, root->point, d);
    long long int index;
    long long int maxdist;
    if (size<k-1)
    {
        enqueue(root->point,distanc,d);
    }
    else
    {
        index = max_index(k,d);
        maxdist = queue[index].priority;
        if (distanc<maxdist)
        {            
            for (int i = 0; i < d; i++)
            {        
                queue[index].arr[i]=root->point[i];
                queue[index].priority=distanc;
            }
        }
    }
    
    if (size<k-1)
    {
        knearestNeighbour(otherBranch, point1, depth+1, d,k);
    }
    else
    {
        index = max_index(k,d);
        maxdist = queue[index].priority;
        long long int dist = point1[(depth)%d] - root->point[(depth)%d];
        if ((maxdist >= dist*dist))
        {
            knearestNeighbour(otherBranch, point1, depth+1, d,k);
        }
    }
}

void swapping(long long int index, long long int k, long long int d)
// Funtcion to swap two indexes in queue and take max to end
{
    long long int temp[d];
    long long int temppriority;
    for (long long int i = 0; i < d; i++)
    {
        temp[i] = queue[index].arr[i];
    }
    temppriority = queue[index].priority;
    for (long long int i = 0; i < d; i++)
    {
        queue[index].arr[i] = queue[k-1].arr[i];
    }
    queue[index].priority=queue[k-1].priority;
    for (long long int i = 0; i < d; i++)
    {
        queue[k-1].arr[i] = temp[i];
    }
    queue[k-1].priority = temppriority;
}

void sort_queue(long long int nearest, long long int d)
// Function which sorts the queue by Getting The Index of Max Priority
{
    if (nearest==0)
    {
        return;
    }
    long long int index;
    index = max_index(nearest,d);
    swapping(index,nearest,d);
    nearest--;
    sort_queue(nearest,d);
}

int main()
{
    //getting inputs from input text file
    FILE * filePointer; 
    filePointer = fopen("input.txt", "r");

    //dimension of the point
    long long int d;
    fscanf(filePointer,"%lld",&d);

    //number of nearest neighbours to find
    long long int k;
    fscanf(filePointer,"%lld",&k);

    //number of points in the data sample
    long long int number_points;
    fscanf(filePointer,"%lld",&number_points);
    
    node *root = NULL;
    
    //point1 around which we find k nearest neighbours
    long long int point1[d];
    for (int i = 0; i < d; i++)
    {
        fscanf(filePointer,"%lld",&point1[i]);
    }

    // Array having the points in the text File
    long long int *points[number_points];

    for (long long int i = 0; i < number_points; i++)
    {
        points[i]=(long long int*)malloc(k*sizeof(long long int));
    }
    printf("\n\n");

    // Storing The Points From Txt File to Points Array 
    for (long long int i = 0; i < number_points; i++)
    {
        for (long long int j = 0; j < d; j++)
        {
            fscanf(filePointer,"%lld ",&points[i][j]);
        }
    }
 
    // Insertion of the points in tree
    for (long long int i=0; i<number_points; i++)
    {
        root = insert(root, points[i], 0, d);
    }
    
    queue=(node_queue*)malloc(sizeof(node_queue));
    node* temp;


    // Applying Nearest Algorithm 
    printf("Result of Application OF Nearest Algorithm:\n");
    temp = nearestNeighbour(root,point1,0,d);
    printf("1 Nearest Point is {");
    for (long long int i = 0; i < d-1; i++)
    {           
        printf("%lld-",temp->point[i]);
    }
    for (long long int i = d-1; i < d; i++)
    {
        printf("%lld}",temp->point[i]);
    } 
    long long int distanc = distancesqaured(temp->point,point1,d);
    printf(" at a Distance: %f\n",sqrt(distanc));
    printf("\n\n");

    // Applying KNN Algorithm
    knearestNeighbour(root,point1,0,d,k);
    long long int nearest = k;
    sort_queue(nearest,d);
    printf("Results of Application OF KNN Algorithm :\n");
    for (long long int i = 0; i < k; i++)
    {        
        printf("%lld Nearest Point is {",i+1);
        for (long long int j = 0; j <d-1; j++)
        {           
            printf("%lld-",queue[i].arr[j]);
        }
        for (long long int j = d-1; j < d; j++)
        {
            printf("%lld}",queue[i].arr[j]);
        }
        printf(" at a Distance: %f\n",sqrt(queue[i].priority));
    }
    return 0;
}
