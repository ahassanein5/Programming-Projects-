// You need to complete this program for your second project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <stack>
#include <vector>
#include <fstream>
#include <set>
#include <utility>
#include <iomanip>
#include <chrono>

using namespace std;


//------------------------------------------------------------------------------------------------------------------
//Graham Scan
struct Point 
{ 
    int x, y; 
}; 
  
// A global point needed for  sorting points with reference 
// to  the first point Used in compare function of qsort() 
Point p0; 
  
// A utility function to find next to top in a stack 
Point nextToTop(stack<Point> &S) 
{ 
    Point p = S.top(); 
    S.pop(); 
    Point res = S.top(); 
    S.push(p); 
    return res; 
} 
  
// A utility function to swap two points 
void swap(Point &p1, Point &p2)
{ 
    Point temp = p1; 
    p1 = p2; 
    p2 = temp; 
} 
  
// A utility function to return square of distance 
// between p1 and p2 
int distSq(Point p1, Point p2) 
{ 
    return (p1.x - p2.x)*(p1.x - p2.x) + 
          (p1.y - p2.y)*(p1.y - p2.y); 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;  // colinear
    if(val >0)
        return 1;
    else
        return 2;
    // clock or counterclock wise 
} 
  
// A function used by library function qsort() to sort an array of 
// points with respect to the first point 
int compare(const void *vp1, const void *vp2) 
{ 
   Point *p1 = (Point *)vp1; 
   Point *p2 = (Point *)vp2; 
  
   // Find orientation 
   int o = orientation(p0, *p1, *p2); 
   if (o == 0) 
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1; 
  
   return (o == 2)? -1: 1; 
} 
  
// Prints convex hull of a set of n points. 
void convexHullG(Point points[], int n)
{ 
   // Find the bottommost point 
   int ymin = points[0].y, min = 0; 
   for (int i = 1; i < n; i++) 
   { 
     int y = points[i].y; 
  
     // Pick the bottom-most or chose the left 
     // most point in case of tie 
     if ((y < ymin) || (ymin == y && 
         points[i].x < points[min].x)) 
         ymin = points[i].y;
         min = i;
   } 
  
   // Place the bottom-most point at first position 
   swap(points[0], points[min]); 
  
   // Sort n-1 points with respect to the first point. 
   // A point p1 comes before p2 in sorted output if p2 
   // has larger polar angle (in counterclockwise 
   // direction) than p1 
   p0 = points[0]; 
   qsort(&points[1], n-1, sizeof(Point), compare); 
  
   // If two or more points make same angle with p0, 
   // Remove all but the one that is farthest from p0 
   // Remember that, in above sorting, our criteria was 
   // to keep the farthest point at the end when more than 
   // one points have same angle. 
   int m = 1; // Initialize size of modified array 
   for (int i=1; i<n; i++) 
   { 
       // Keep removing i while angle of i and i+1 is same 
       // with respect to p0 
       while (i < n-1 && orientation(p0, points[i], 
                                    points[i+1]) == 0) 
          i++; 
  
  
       points[m] = points[i]; 
       m++;  // Update size of modified array 
   } 
  
   // If modified array of points has less than 3 points, 
   // convex hull is not possible 
   if (m < 3) return; 
  
   // Create an empty stack and push first three points 
   // to it. 
   stack<Point> S; 
   S.push(points[0]); 
   S.push(points[1]); 
   S.push(points[2]); 
  
   // Process remaining n-3 points 
   for (int i = 3; i < m; i++) 
   { 
      // Keep removing top while the angle formed by 
      // points next-to-top, top, and points[i] makes 
      // a non-left turn 
      while (orientation(nextToTop(S), S.top(), points[i]) != 2) 
         S.pop(); 
      S.push(points[i]); 
   } 
  
   //create file and write points to it
    std::ofstream outfile("hull_G.txt");
    while (!S.empty()){
        Point p = S.top();
        outfile << p.x << " " << p.y << endl;
        S.pop();
    }
}

//----------------------------------------------------------------------------------------------------
//Jarvis Scan
// Prints convex hull of a set of n points.
void convexHullJ(Point points[], int n)
{
    // There must be at least 3 points
    if (n < 3) return;
  
    // Initialize Result
    std::vector<Point> hull;
  
    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;
  
    // Start from leftmost point, keep moving counterclockwise
    // until reach the start point again.  This loop runs O(h)
    // times where h is number of points in result or output.
    int p = l, q;
    do
    {
        // Add current point to result
        hull.push_back(points[p]);
  
        // Search for a point 'q' such that orientation(p, x,
        // q) is counterclockwise for all points 'x'. The idea
        // is to keep track of last visited most counterclock-
        // wise point in q. If any point 'i' is more counterclock-
        // wise than q, then update q.
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
           // If i is more counterclockwise than current q, then
           // update q
           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }
  
        // Now q is the most counterclockwise with respect to p
        // Set p as q for next iteration, so that q is added to
        // result 'hull'
        p = q;
  
    } while (p != l);  // While we don't come to first point
  
    
    //create and write to file
    std::ofstream outfile("hull_J.txt");
    for (int i = 0; i < hull.size(); i++){
        outfile <<  hull[i].x << " " << hull[i].y << "\n";
    }
}
//----------------------------------------------------------------------------------------------------
//Quickhull
// iPair is integer pairs
  vector<Point> hull;

// Stores the result (points of convex hull)
  
// Returns the side of point p with respect to line
// joining points p1 and p2.
int findSide(Point p1, Point p2, Point p)
{
    int val = (p.y - p1.y) * (p2.x - p1.x) -
              (p2.y - p1.y) * (p.x - p1.x);
  
    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}
  
// returns a value proportional to the distance
// between the point p and the line joining the
// points p1 and p2
int lineDist(Point p1, Point p2, Point p)
{
    return abs ((p.y - p1.y) * (p2.x - p1.x) -
               (p2.y - p1.y) * (p.x - p1.x));
}
  
// End points of line L are p1 and p2.  side can have value
// 1 or -1 specifying each of the parts made by the line L
void quickHull(Point a[], int n, Point p1, Point p2, int side)
{

    int ind = -1;
    int max_dist = 0;
  
    // finding the point with maximum distance
    // from L and also on the specified side of L.
    for (int i=0; i<n; i++)
    {
        int temp = lineDist(p1, p2, a[i]);
        if (findSide(p1, p2, a[i]) == side && temp > max_dist)
        {
            ind = i;
            max_dist = temp;
        }
    }
  
    // If no point is found, add the end points
    // of L to the convex hull.
    if (ind == -1)
    {
        if(!(p1.x==0 && p1.y==0)){
           hull.push_back(p1);
        }
        if(!(p2.x==0 && p2.y==0)){
           hull.push_back(p2);
        }
        return;
    }

    // Recur for the two parts divided by a[ind]
    quickHull(a, n, a[ind], p1, -findSide(a[ind], p1, p2));
    quickHull(a, n, a[ind], p2, -findSide(a[ind], p2, p1));

}

void printHullQ(Point a[], int n)
{
    // a[i].second -> y-coordinate of the ith point
    if (n < 3)
    {
        cout << "Convex hull not possible\n";
        return;
    }
  
    // Finding the point with minimum and
    // maximum x-coordinate
    int min_x = 0, max_x = 0;
    for (int i=1; i<n; i++)
    {
        if (a[i].x < a[min_x].x)
            min_x = i;
        if (a[i].x > a[max_x].x)
            max_x = i;
    }
  
    // Recursively find convex hull points on
    // one side of line joining a[min_x] and
    // a[max_x]
    quickHull(a, n, a[min_x], a[max_x], 1);
  
    // Recursively find convex hull points on
    // other side of line joining a[min_x] and
    // a[max_x]
    quickHull(a, n, a[min_x], a[max_x], -1);
  
    std::ofstream outfile("hull_Q.txt");
    while (!hull.empty())
    {
        outfile <<( *hull.begin()).x << " "
             << (*hull.begin()).y << "\n";
        hull.erase(hull.begin());
    }
}
  
//DRIVER

int main(int argc, char *argv[])
{
    int arraySize;
//    time_t start, end;
//    time(&start);
    std::cout << "Please specify your array size: ";
    std::cin >> arraySize;
    
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    
   if (argc < 3)
      std::cout << "wrong format! should be \"a.exe algType dataFile\"";
   else {
      
      std::string algType = argv[1];
      std::string dataFilename = argv[2];

      std::string outputFile = "";
      //read your data points from dataFile (see class example for the format)
      
       std::ifstream infile;
       infile.open(dataFilename);
       Point points[arraySize];
       int i = 0;
       while(!infile.eof()){
           int x,y;
           infile >> x >> y;
           points[i].x = x;
           points[i].y = y;
           i++;
       }
       infile.close();
       
      int n = sizeof(points)/sizeof(points[0]);

     

      if (algType[0]=='G') {
         //call your Graham Scan algorithm to solve the problem
         convexHullG(points, n);
         outputFile = "hull_G.txt";
      }
      else if (algType[0]=='J') {
         //call your Javis March algorithm to solve the problem
          convexHullJ(points, n);
         outputFile = "hull_J.txt";
      }
      else { //default
         //call your Quickhull algorithm to solve the problem
          printHullQ(points, n);
         outputFile = "hull_Q.txt";
      }
      
      //write your convex hull to the outputFile (see class example for the format)
      //you should be able to visulize your convex hull using the "ConvexHull_GUI" program.
    }
    
    auto end = chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
//    double temp = duration.count();
//    std::cout << setprecision (10) << fixed << temp << endl;
//    time(&end);

    
    
//    double time_taken = double(end - start);
    double time_taken =
        chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
      time_taken *= 1e-9;
      time_taken *= 1000;
      cout << "Time taken by program is : " << fixed
           << time_taken << setprecision(9);
      cout << " sec" << endl;
    return 0;
}


//need to change quickhall function from printitng to screen to the file
//start working on the time tables


//10/30/19--3:13pm
//so i need to change the program so that i can change the array size without changing the program
///evertime. then i need to get my times down into the table and finish the analysis,
//once you have your analysis down, go back and try to make sure the hulls are working like theyre supposed
//to be. i want to at least have something to turn in and then i can go to her for help on trying to fix
//it so she sees that i really am trying. 
