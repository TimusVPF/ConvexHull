//
//  main.cpp
//  ConvexHull
//
//  Created by plaza on 8/24/15.
//  Copyright (c) 2015 __ComputationalGeometry__. All rights reserved.
//
//  Summary: Implementation of Graham's scan algorithm to compute the
//           convex hull of a set of points in the xy-plane
//
//
//  Input : A set of points in the xy-plane
//  Output: Two arrays containing the upper convex hull and the lower
//          convex hull of the input.



#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;


// Point in the xy-plane
struct PointType{
    double x;
    double y;
};


// Sort criterion: points are sorted with respect to their x-coordinate.
//                 If two points have the same x-coordinate then we compare
//                 their y-coordinates
bool sortPoints(const PointType &lhs, const PointType &rhs) 
{ 
    return (lhs.x < rhs.x) || (lhs.x==rhs.x && lhs.y < rhs.y); 
}


// Check if three points make a right turn using cross product
bool right_turn(const PointType &P1, const PointType &P2, const PointType &P3)
{
    return ((P3.x-P1.x)*(P2.y-P1.y) - (P3.y-P1.y)*(P2.x-P1.x)) > 0;
}


int main () {
    
    
    ifstream myfile;
    int n_points;
    PointType *points;
    vector<PointType> lowerCH;
    vector<PointType> upperCH;
    
    // reading data from file
    myfile.open("test1.txt");
    
    if(myfile.is_open())
    {
        myfile >> n_points;
        points = new PointType[n_points];
        
        for(int i=0; i< n_points; i++)
            myfile >> points[i].x >> points[i].y;
        
        myfile.close();
    
    
        //Sorting points
        sort(points, points + n_points, sortPoints);
        cout << "Sorted Points\n";
        for(int i = 0; i != n_points; ++i)
            cout << "(" << points[i].x << " , " << points[i].y << ")" << endl;
    

        //Computing upper convex hull
        upperCH.push_back(points[0]);
        upperCH.push_back(points[1]);
        
        for(int i=2; i<n_points; i++)
        {
            while(upperCH.size() > 1 and (!right_turn(upperCH[upperCH.size()-2],upperCH[upperCH.size()-1], points[i])))
                upperCH.pop_back();
            upperCH.push_back(points[i]);
        }
        cout << "Upper Covex Hull" << endl;
        for(int i=0; i < upperCH.size(); i++)
            cout << "(" << upperCH[i].x << " , " << upperCH[i].y << ")" << endl;
        
        
    
        //Computing lower convex hull
        lowerCH.push_back(points[n_points-1]);
        lowerCH.push_back(points[n_points-2]);
        
        for(int i=2; i< n_points; i++)
        {
            while(lowerCH.size() > 1 and (!right_turn(lowerCH[lowerCH.size()-2],lowerCH[lowerCH.size()-1], points[n_points-i-1])))
                lowerCH.pop_back();
            lowerCH.push_back(points[n_points-i-1]);
        }
        cout << "Lower Covex Hull" << endl;
        for(int i=0; i < lowerCH.size(); i++)
            cout << "(" << lowerCH[i].x << " , " << lowerCH[i].y << ")" << endl;
        
    }
    
    
    
    return 0;
}