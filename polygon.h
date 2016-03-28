/********************************************************************************************************************
 * This file contains the prototypes of all the functions of the LO27 project (whose body is in the file polygon.c) : 
 * It contains the prototypes of functions for the manipulation of the polygons, functions to manipulate linked lists 
 * and other useful functions.
 * Authors: Clement BARETH - Antoine COUPAT
 * Semester : A2014
 ********************************************************************************************************************/

#ifndef POLYGON_H
#define POLYGON_H

#include "dataStructures.h"

/*
 *Creates a 2D-Point according to the specified abscissa and ordinate
 * x - abscissa of the point
 * y - ordinate of the point
 * Returns the point which was just created
 */
Point createPoint (double x,double y);

/*
 * Creates an empty polygon and initializes its fields (size to 0 and PointElement* to NULL)
 * Returns the polygon which was just created
 */
Polygon createPolygon ();

/*
 * Adds the specified point to the specified polygon
 * poly - polygon in which the point will be added to        ?????????????????????
 * p - point which will be added to the polygon
 * Returns the polygon which was just modified
 */
Polygon addPoint (Polygon poly, Point p);

/*
 * Removes the i th point from the specified polygon 
 * (points are indexed from 1 to N in a polygon)
 * poly - polygon in which the point will be removed of    ????????????????
 * index - index (in the polygon) of the point which will be removed
 */
Polygon removePoint (Polygon poly, int index);


 /* Returns the list of the intersection points between poly1 and poly2 as a polygon
  * poly1 - first polygon of the intersection
  * poly2 - second polygon of the intersection
  */ 
Polygon intersectionPoints(Polygon poly1, Polygon poly2);

/*
 * computes the union between the two specified polygons
 * polyA - first polygon of the union
 * polyB - second polygon of the union
 */
Polygon unionPolygons (Polygon poly1, Polygon poly2);

/*
 * computes the intersection between the two specified polygons
 * polyA - first polygon of the intersection
 * polyB - second polygon of the intersection
 */
Polygon intersectionPolygons (Polygon polyA, Polygon polyB);

/*
 * computes the exclusive OR between the two specified polygons
 * polyA - first polygon of the exclusive OR
 * polyB - second polygon of the exclusive OR
 */
Polygon exclusiveORPolygons (Polygon poly1, Polygon poly2);

/*
 * computes the difference between the two specified polygons
 * polyA - first polygon of the difference
 * polyB - second polygon of the difference
 */
Polygon differencePolygons (Polygon poly1, Polygon poly2);

/*
 * Returns true if the specified polygon contains the specified point, false otherwise
 * poly - Polygon where the point can be
 * p - point to test
 */
Boolean containsPoint (Polygon poly, Point p);


/*
 * Computes the central symmetry of the specified polygon according to the specified point
 * poly - polygon to apply the symmetry
 * p - center of the symmetry
 */
Polygon centralSymmetry (Polygon poly, Point center); 

/*
 * Computes the rotation of the specified polygon according to the specified point and the
 * specified angle in radians (counterclockwise)
 * poly - polygon which will be rotated
 * center - center of the rotation (point)
 * angle - angle of the rotation (in radians)
 */
Polygon rotatePolygon (Polygon poly, Point center, double angle);

/*
 * Scales the specified polygon according to the specified factor
 * poly - polygon to scale
 * factor - scaling factor
 */
Polygon scalePolygon (Polygon poly, float factor); 

/*
 * Computes the translation of the specified polygon according to the vector defined by
 * the two specified points (vector going from the first specified point (A) to the
 * second one (B))
 * poly - polygon which will be translated
 * A - first point of the translation vector
 * B - second point of the translation vector
 */
Polygon translatePolygon (Polygon poly, Point A, Point B); /* noms des points à changer*/

/*
 * Computes the convex hull  of the specified polygon using the Graham's method
 * poly - Polygon to transform
 */
Polygon convexHullPolygon (Polygon poly);

/*
 * Prints a 2D-Point on the console terminal
 * p - point to print
 */
void printPoint (Point p);

/*
 * Prints a Polygon on the console terminal
 * poly - polygon to print
 */
void printPolygon (Polygon poly);

/*
 * Outputs the list of points of a Polygon into
 * a string strictly respecting the following template (no space at all)
 * poly - the string returned is based on this polygon 
 */
char* toString(Polygon poly);


/* 
 * Compares to floats with a possible error majored by the constant EPSILON
 * a - first number to compare
 * b - second number to compare
 * symbol - symbol of comparison wanted , it can be "==" , "<=" , ">=", "<=", "<" ,">" 
 */
Boolean compare(float a,char* symbol, float b);

/*
 * Returns the coordinates of the barycenter of the polygon 
 * poly - Polygon where we want to find the barycenter
 */
Point barycenter(Polygon poly);

/*
 * Returns the area of the corresponding polygon
 * poly - Polygon where we want to find the area
 */ 
float area (Polygon poly);

/*
 * Returns True if the the point B is under the segment [AB]
 * p - point to test
 * A - first extremity of the segment
 * B second extremity of the segment
 */
Boolean isUnderSegment(Point p, Point A, Point B);

/* Returns True if the list of points forms a polygon, FALSE otherwise */
Boolean is_polygon(Point list[],int size);

/* Fill the array with points asked to the user*/
void fill_list (Point*);

/* 
 * Returns the minimum between two floats
 * a - first float to compare
 * b - second float to compare
*/
float min(float a,float b);

/* 
 * Returns the minimum between two floats
 * a - first float to compare
 * b - second float to compare
*/
float max(float a,float b);

/* Returns a number given by the users verifying it is in a specific range
 * a - Lower bound of the range
 * b - Upper bound of the range
 */
int getInt(int a, int b, char* str);

/*
 * returns a Status enumeration type that could take the following values :
 *  INSIDE if the second polygon is fully inside the first one ;
 *  OUTSIDE if the second polygon is fully outside the first one ;
 *  INTERSECT if the second polygon is partially inside/outside the first
 *     one, in other words intersecting the second one ;
 *  ENCLOSING if the first polygon is fully inside the second one ;
 *  EQUAL both polygons are exactly equal.
 *	
 * poly1 - first polygon to compare
 * poly2 - second polygon to compare
 */
Status containsPolygon(Polygon poly1, Polygon poly2);
 
/*
 * Returns TRUE if the three points in parameter are aligned, False otherwise.
 *  p1 - first point to check
 *  p2 - second point to check
 *  p3 - third point to check
*/
Boolean AreAligned(Point p1, Point p2, Point p3);
 
/*
 * Sorts the table entered in parameter (by adress)
 * a - array of AnglePoint to sort
 */
void bubbleSortTp( AnglePoint* a , int size);




/*********************  Functions manipulating the linked list ListOfPoly ************************/

/*
 * Adds a polygon to a list of polygons and returns this list.
 * l - list in which the polygon will be added to  ?????????????
 * poly - polygon to add to the list
 */
ListOfPoly addPoly( ListOfPoly l, Polygon poly);

/*
 * Initializes all the fieds of a new list of polygons.
 */
ListOfPoly initList();


/*
 * Prints all the polygons of the list.
 * l - list to print
 */
void printListOfPoly(ListOfPoly l);
 
/*
 * Returns the polygon corresponding to the index in the list
 * l - list where the polygon is
 * index - index of the polygon to return
 */
Polygon selectPolygon(ListOfPoly l, int index);

/*
 * Returns a pointer on the polygon corresponding to the index in the list
 * l - list where the polygon is
 * index - index of the polygon to return
 */
Polygon* selectPolygonP(ListOfPoly l, int index);
 
 /*********************************** Freeing functions ***********************************************/
 
 
/*
 * Frees the memory corresponding to the specified polygon
 * poly - polygon to free
 */
void freePolygon(Polygon* poly); 
 
 /* Frees the memory corresponding to the whole list of polygons 
  * l - list to free
  */
void freeListOfPoly( ListOfPoly l);




#endif



