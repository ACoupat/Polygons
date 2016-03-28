/********************************************************************************************************************
 * This file contains the definition of all the data structures of the LO27 project: 
 * It contains the definition of the linked lists, enum types and structures.
 * Authors: Clement BARETH - Antoine COUPAT
 * Semester : A2014
 ********************************************************************************************************************/

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/****************************************   Enum types *************************************************************/


/*Definition of the type Boolean*/
typedef enum { FALSE, TRUE } Boolean;

/*Defintion of the type "Status"*/
/*This type is used in the function containsPolygon*/
typedef enum { INSIDE, OUTSIDE, INTERSECT, ENCLOSING, EQUAL } Status;



/************************************* Definition of a doubly circular linked list : polygon *************************/

/*
 * This type is used to represent a polygon composed of different points.
 */
 
 
/*Definition of the type "Point" */
typedef struct{

	double x;
	double y;

}Point;

/*Defintion of the type "PointElement"*/
typedef struct pelem{

	Point data;

	struct pelem* next;
	struct pelem* prev;

}PointElement;

/*Definition of the type "Polygon"*/
typedef struct{

	PointElement* head;
	int size;
	
}Polygon;


/******************************** Definition of a doubly linked list : ListOfPoly ************************************/

/*
 * This type is used to organize the different polygons entered by the users in order to use them easily 
 * in the different menus.
 */

/*Definition of the type "ListOfPolyElem"*/

typedef struct lpelem{

	Polygon data;
	struct lpelem* next;
	struct lpelem* prev;

}ListOfPolyElem;

/*Definition of the type "ListOfPolyElem"*/
typedef struct{

	ListOfPolyElem* head;
	ListOfPolyElem* last;	
	int size;

}ListOfPoly;


/*******************************************   Structures types **************************************************/

/*
 *  This type is used in the function convexHullPolygon, to sort points according to an angle.
 */

typedef struct{
	
	Point point;
	double angle;
	
}AnglePoint;

#endif

