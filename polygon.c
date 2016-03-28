/************************************************************************************
 * This file contains the body of all the functions of the LO27 project : 
 * It contains the prototypes of functions for the manipulation of the polygons, 
 * function to manipulate linked lists and others useful functions.
 * Authors: Clement BARETH - Antoine COUPAT
 * Semester : A2014
 ************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "polygon.h"
#include "dataStructures.h"

/* EPSILON is used to parameter the error when we compare floats */

#define EPSILON 0.001
#define M_PI  3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

/*
 * Creates a 2D-Point according to the specified abscissa and ordinate
 * x - abscissa of the point
 * y - ordinate of the point
 * Returns the point which was just created
 */
Point createPoint (double x,double y)
{

	Point* p_pt=(Point*) malloc (sizeof(Point));

	if (p_pt != NULL)
	{
		p_pt->x=x;
		p_pt->y=y;
			
	}
	else
	{
		printf("\n\nError during the creation of the point, please retry \n\n");
	}


	return *p_pt;
}

/*
 * Creates an empty polygon and initializes its fields (size to 0 and PointElement* to NULL)
 * Returns the polygon which was just created
 */
Polygon createPolygon ()
{
	Polygon* p_poly = (Polygon*) malloc(sizeof(Polygon));
	
	if (p_poly != NULL)
	{
		p_poly->size=0;
		p_poly->head=NULL;
		
		
	}
	else
	{
		printf("\n\nError during the creation of the polygon, please retry\n\n");
	}
	
	return *p_poly;
}

/*
 * Adds the specified point to the specified polygon
 * poly - polygon in which the point will be added to
 * p - point which will be added to the polygon
 * Returns the polygon which was just modified
 */
Polygon addPoint (Polygon poly, Point p)
{
	
	PointElement* p_newPointElement = (PointElement*) malloc(sizeof(PointElement));
	
	if(poly.head == NULL)
	{

		p_newPointElement->data=p;
		p_newPointElement->next=p_newPointElement;
		p_newPointElement->prev=p_newPointElement;

		poly.head=p_newPointElement;

	}
	else
	{
		p_newPointElement->data= p;
		p_newPointElement->next=poly.head;
		p_newPointElement->prev=poly.head->prev;
	
		poly.head->prev->next=p_newPointElement;
		poly.head->prev=p_newPointElement;
	}

	poly.size++;

	
	return poly;

}

/*
 * Removes the i th point from the specified polygon 
 * (points are indexed from 1 to N in a polygon)
 * poly - polygon in which the point will be removed of    ????????????????
 * index - index (in the polygon) of the point which will be removed
 */
Polygon removePoint (Polygon poly, int index)  
{
	PointElement* pe = poly.head;
	int i=1;

	if (index >0 && index<=poly.size) /* we verify if the point corresponding to the index does exist*/
	{
		if (index == 1) /* case where we remove the first point, we have to modify the Polygon structure*/
		{
			poly.head=pe->next;
			pe->prev->next=pe->next;
			pe->next->prev=pe->prev;
			
		}
		else
		{
			
	
			while (i<index)
			{
				pe = pe->next;
				i++;
			}
	
			pe->prev->next=pe->next;
			pe->next->prev=pe->prev;
	
			free(pe);
		}
		
		poly.size--;
		
	}
	else if (index <= 0)
	{
		printf("\n\nError during the removing of the point, please enter a positive index (%d)\n\n",index);
	}
	else if (index > poly.size)
	{
		printf("\n\nError during the removing of the point, index greater than the size of the polygon (%d > %d)\n\n", index, poly.size);
	}
	

	return poly;
}


/*
 * Computes the translation of the specified polygon according to the vector defined by
 * the two specified points (vector going from the first specified point (A) to the
 * second one (B))
 * poly - polygon which will be translated
 * A - first point of the translation vector
 * B - second point of the translation vector
 */
Polygon translatePolygon (Polygon poly, Point A, Point B)
{

	PointElement* pe = poly.head;
	float tX, tY;
	
	if (pe != NULL)
	{
		tX = B.x - A.x;
		tY = B.y - A.y;	
		
		do
		{
			pe->data.x = pe->data.x + tX;
			pe->data.y = pe->data.y + tY;
			pe = pe->next;
		
		}while(pe != poly.head);
		
	}
	else
	{
		printf("\n\n Error during the translation, the polygon is empty\n\n");
	}



	return poly;
}

/*
 * Computes the rotation of the specified polygon according to the specified point and the
 * specified angle in radians (counterclockwise)
 * poly - polygon which will be rotated
 * center - center of the rotation (point)
 * angle - angle of the rotation (in radians)
 */
Polygon rotatePolygon (Polygon poly, Point center, double angle)
{
	PointElement* pe = poly.head;
	float x2,y2;

	if (pe !=NULL)
	{
		do
		{
			

			x2 = cos(angle)*(pe->data.x-center.x) - sin(angle)*(pe->data.y-center.y) + center.x;

			
			y2 = sin(angle)*(pe->data.x-center.x) + cos(angle)*(pe->data.y-center.y) + center.y ;

			
			pe->data.x = x2;
			pe->data.y = y2;
			
			pe = pe->next;
		
		}while(pe != poly.head);

	}
	else
	{
		printf("\n\n Error during the rotation, the polygon is empty\n\n");
	}


	return poly;
}

/*
 * Scales the specified polygon according to the specified factor
 * poly - polygon to scale
 * factor - scaling factor
 */
Polygon scalePolygon (Polygon poly, float factor)
{
	if (poly.head != NULL)
	{
		PointElement* pe =poly.head;
		Point origin = {0,0};
		Point barycenter1 = barycenter(poly);
	
		translatePolygon(poly, barycenter1, origin); 
		
		do
		{
			pe->data.x = pe->data.x * factor;
			pe->data.y = pe->data.y * factor;
			
			pe = pe->next;
		
		}while (pe != poly.head);
		translatePolygon(poly, origin, barycenter1);

	
	}
	else
	{
		printf("\nEmpty polygon, the scale did not occure\n");
	}
	
	
	return poly;

}

/*
 * Returns true if the specified polygon 
 contains the specified point, false otherwise
 * poly - Polygon where the point can be
 * p - point to test
 * Principe : Considering a ray starting from p and directed on the vertical axis, we look if there
 * is an intersection between this ray and each edge of the polygon. If the total number of
 * intersections is odd then the point p is inside of the polygon. If this number is even then the
 * point is outside of the polygon. 
 *
 */
Boolean containsPoint (Polygon poly, Point p)
{
	Boolean contains = FALSE;
	
	int nbIntersect = 0;
	if (poly.head != NULL)
	{
		PointElement* pe = poly.head;
		do
		{
		
			if (compare(pe->data.y,"==", p.y) && compare(pe->data.x,"==", p.x)) /* If the point p is one of the points of the polygon we consider that the polygon contains p*/
			{
				contains = TRUE;
			} 
		
			else if (compare(p.x,"==",pe->data.x) && compare(p.x,"==",pe->next->data.x))
			{
				if (p.y < max(pe->data.y,pe->next->data.y) && p.y > min(pe->data.y,pe->next->data.y))/*Case where te point is aligned with a vertical segment of the polygon*/
				{
					contains = TRUE;
				}
			}
		
			else if ((p.x >= min(pe->data.x,pe->next->data.x) && p.x <=max(pe->data.x,pe->next->data.x) )) /*Case where the abscissa of p is between the abscissa of the first point and the abscissa of the second point*/
		
			{
				if (p.y < pe->data.y && p.y < pe->next->data.y) /*if p is under the two points of the considered segment*/
				{
					nbIntersect ++;
					
				
				}
			
				else if (p.y < max(pe->data.y,pe->next->data.y) && p.y > min(pe->data.y,pe->next->data.y) && isUnderSegment(p,pe->data,pe->next->data)) /*if p ordinate is between the ordinates of the two points considered and if the point is under the considered segment*/
				{

					nbIntersect++; 
					
				
				}
			
			}
			pe = pe->next;

			
		}while (pe != poly.head);
		
		if (nbIntersect % 2 == 1)
		{
			contains = TRUE;
		}
	
	}
	else
	{
		printf("\nEmpty polygon, it can not contain any point\n");
		
	}


	
	return contains;
}

/* 
 * Returns the minimum between two floats
 * a - first float to compare
 * b - second float to compare
*/
float min(float a, float b)
{
	if (compare(a,"<",b))
	{
		return a;
	}
	else
	{
		return b;
	}
	
}

/* 
 * Returns the minimum between two floats
 * a - first float to compare
 * b - second float to compare
*/
float max(float a, float b)
{
	if (compare(a,"<",b))
	{
		return b;
	}
	else
	{
		return a;
	}
	
}
/*
 * Returns True if the the point p is under the segment [AB]
 * p - point to test
 * A - first extremity of the segment
 * B second extremity of the segment
 */
Boolean isUnderSegment(Point p, Point A, Point B)
{

	Boolean under = FALSE;
	float yp2;
	
	if (A.x!=B.x)
	{
		
		yp2 = ((A.y-B.y)/(A.x-B.x))*(p.x-B.x)+B.y; /*yp2 is the ordinate of the projection of the point p on the considered segment along the y-axis*/
		if (compare(yp2,">=",p.y))
		{
			under = TRUE;
	
		}
	}
	else /* case where the considered segment is vertical, so yp2 cannot be computed*/
	{ 
		
	
	}
	
	return under;
}

/*
 * Computes the central symmetry of the specified polygon according to the specified point
 * poly - polygon to apply the symmetry
 * p - center of the symmetry
 */
Polygon centralSymmetry (Polygon poly, Point center)
{
	if (poly.head != NULL)
	{
		PointElement* pe =poly.head;
		Point origin = {0,0};
		
	
		translatePolygon(poly, center, origin); 

		
		do
		{
			pe->data.x = pe->data.x * -1;
			pe->data.y = pe->data.y * -1;
			
			pe = pe->next;
		
		}while (pe != poly.head);
		translatePolygon(poly, origin, center);

	
	}
	else
	{
		printf("\nEmpty polygon, the scale did not occure\n");
	}
	
	
	return poly;

}
/* Compares to floats with a possible error majored by the constant EPSILON
 * a - first number to compare
 * b - second number to compare
 * symbol - symbol of comparison wanted , it can be "==" , "<=" , ">=", "<=", "<" ,">" */
Boolean compare(float a,char* symbol, float b)
{
	if (strcmp(symbol,"==")==0)
	{
		if (a < b+EPSILON && a>b-EPSILON)
		{
			return TRUE;
		}
		else return FALSE;
	}
	else if (strcmp(symbol,"<=")==0 || strcmp(symbol,"<")==0)
	{
		if (a < b+EPSILON)
		{
			return TRUE;
		}
		else return FALSE;
	}
	else if (strcmp(symbol,">=")==0 || strcmp(symbol,">")==0)  
	{
		if (a> (b-EPSILON))
		{
			return TRUE;
		}
		else return FALSE;
	}
	else 
	{
	
		printf("Error in the compare function");
		
	
	}
	return FALSE;
	
	

}

/*
 *Prints a 2D-Point on the console terminal
 * p - point to print
 */
void printPoint (Point p)
{

	printf("\nPoint coordinates : x: %.2f , y: %.2f\n",p.x,p.y);

}

/*
 * Prints a Polygon on the console terminal
 * poly - polygon to print
 */
void printPolygon (Polygon poly)
{
	printf("\n\n============== This is the different points of this polygon ===== size : %d =========\n\n",poly.size);
	if (poly.size != 0)
	{
		PointElement* pe = poly.head;
	
		do
		{
			printPoint(pe->data);
			pe=pe->next;
		}while (pe != poly.head);
	}
	else 
	{
		printf("\n This polygon is empty, there is no point to print\n");
	}
	printf("\n\n=======================================================\n\n");
}

/*
 * Returns the coordinates of the barycenter of the polygon entered
 * poly - Polygon where we want to find the barycenter
 */
Point barycenter(Polygon poly)
 {
 	
 	Point barycenter;
 	float sumX=0;
 	float sumY;
	if (poly.size != 0)
	{
	 	PointElement* pe = poly.head;

	 	do
	 	{
	 		sumX = sumX + (pe->data.x + pe->next->data.x)*(pe->data.x*pe->next->data.y-pe->next->data.x*pe->data.y);
	 		
	 		sumY = sumY + (pe->data.y + pe->next->data.y)*(pe->data.x*pe->next->data.y-pe->next->data.x*pe->data.y);
	 		pe = pe->next;
	 	}while (pe != poly.head);
	 	
		barycenter.x = sumX/(6*area(poly));
	 	
	 	barycenter.y = sumY/(6*area(poly));
	 	
	 }
	 else 
	 {
	 	barycenter.x = 0;
	 	
	 	barycenter.y = 0;
	 	printf("\n Empty polygon, there is no barycenter to compute \n");
	 }
 	
	 
	 return barycenter;
 }
 
 float area (Polygon poly)
 {
 	float area=0;
	 if (poly.size != 0)
	{

	 	
	
	 	PointElement* pe = poly.head;

	 	do
	 	{
	 		area = area + (pe->data.x*pe->next->data.y-pe->next->data.x*pe->data.y);
	 		pe = pe->next;
	 	}while (pe != poly.head);
	 	area = 0.5*area;
	 	
	 	
	 }
	 else 
	 {
	 	area =0;
	 	printf("\n Empty polygon, there is no area to compute \n");
	 }
	 	
	 return area;
 }
		


/* Returns an integer given by the user verifying that it is in a specific range [a,b], a and b can be equals
 * a - Lower bound of the range
 * b - Upper bound of the range
 */
int getInt(int a, int b, char* str)
{
	int i;
	/*char c;*/
	i=-42;
	printf("\n\n  Your choice :");
	scanf("%d",&i);
	/*c=getchar();*/
	
	if (a != b)
	{
		while ((i<a || i>b))
		{
			
			
			printf("%s\n\n  Your choice :",str);
			scanf("%d",&i);
			
			
		}
	}
	else
	{
		while (i!=a /*&& isInteger != 1 */)
		{
			

			printf("%s\n\n  Your choice :",str);
			scanf("%d",&i);
			
		}
	}
	
	return i;

}


/*
 *returns a Status enumeration type that could take the following values :
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
Status containsPolygon(Polygon poly1, Polygon poly2)
{
	Status stat;
	int i=0,k=0 ;
	PointElement* p2 = poly2.head ; 
	PointElement* p1 = poly1.head ; 
	do
		{
			
	if ( p2->data.x == p1->data.x && p2->data.y == p1->data.y)
				{
					k++;
					i++;
				}
	else if  ( containsPoint (poly1 , p2->data )) /* Searching if the 2nd polygon is included in the 1st one */ 
				{
					i++;
				}
			p2 = p2->next;
			p1 = p1->next;
		} while (p2!=poly2.head);
		
	if ( k == poly2.size )
		{
			stat = EQUAL ; 
		}
		else if (i==poly2.size)
			{ 
				stat = INSIDE ; 
			}
	
		else if (i != 0 )
			{
				stat = INTERSECT ;
			}
		else 
			{
				
				i = 0 ;
				
				p1 = poly1.head ; 
				do
					{
						if  ( containsPoint (poly2 , p1->data ) )  /* Searching if the 1st polygon is included in the 2nd one */ 
						{
							i++;
						}
							
						p1 = p1->next;
					}while (p1!=poly1.head);
				
				if ( i == poly1.size) 
				{
					stat = ENCLOSING ; 
				}
				else if (i!=0)
				{
					stat = INTERSECT;
				}
				else 
				{
					stat = OUTSIDE;
				}
			}
		




	return stat;

}

/*
 * Outputs the list of points of a Polygon into
 * a string strictly respecting the following template (no space at all)
 * poly - the string returned is based on this polygon 
 */
char* toString(Polygon poly)
{
	int strsize= 12*poly.size+1; /*computing the number of characters the final string will contain according to the number of points of the polygon*/

	char* str = (char*) malloc(strsize*sizeof(char));
	char strtmp [12];
	PointElement* pe =poly.head;
	strcat(str,"[");
	do
	{
		if (pe->next == poly.head)
		{
			sprintf(strtmp,"[%.2f,%.2f]",pe->data.x,pe->data.y);
			strcat(str,strtmp);	
		}
		else
		{
			sprintf(strtmp,"[%.2f,%.2f],",pe->data.x,pe->data.y);
			strcat(str,strtmp);	
		}
		pe = pe->next;
	}while (pe != poly.head);
	
	strcat(str,"]");
	
		return str;
	
}

/*********************  Functions manipulating the linked list ListOfPoly ************************/

/*
 * Adds a polygon at the end of a list of polygons and returns this list.
 * l - list to which the polygon will be added 
 * poly - polygon to add to the list
 */
ListOfPoly addPoly( ListOfPoly l, Polygon poly)
{

	ListOfPolyElem* new = (ListOfPolyElem*) malloc(sizeof(ListOfPolyElem));
	
	new -> data = poly;
	new -> next = NULL;
	
	if (l.head == NULL)
	{
		new -> prev = NULL;
		l.head = new;
		l.last = new;
	}
	else 
	{
		new -> prev = l.last;
		l.last->next = new;
		l.last = new;
		
	}
	l.size++;

	return l;
}



/*
 * Creates and initializes all the fields of a new list of polygons.
 */
ListOfPoly initList()
{

	ListOfPoly l;
	l.head = NULL;
	l.last = NULL;
	l.size = 0;
	
	return l;

}


/*
 * Prints all the polygons of the list.
 * l - list to print
 */
void printListOfPoly(ListOfPoly l)
{
	ListOfPolyElem* lpe;
	int i=1;
	lpe = l.head;
	
	printf("======================== LIST OF CURRENT POLYGONS ====================\n\n");
	if (lpe == NULL)
	{
		printf("\n There is no polygon in the list, you can add polygons in the menu.\n\n");
	
	}
	
	while (lpe != NULL)
	{
		printf("Polygon n° %d",i);
		printPolygon(lpe->data);
		lpe = lpe-> next;
		i++;
	
	}

}
 /**********************************************************************************************************************************/
 /*
 * Returns the polygon corresponding to the index in the list
 * l - list where the polygon is
 * index - index of the polygon to return
 */
Polygon selectPolygon(ListOfPoly l, int index)
{
	ListOfPolyElem* lpe = l.head;
	int i =1;
	while ( i != index )
	{
	
		lpe = lpe-> next;
		i++;
	
	}


	return lpe->data;
}
 /*****************************************************************************************************************************/
/*
 * Returns a pointer on the polygon corresponding to the index in the list
 * l - list where the polygon is
 * index - index of the polygon to return
 */
Polygon* selectPolygonP(ListOfPoly l, int index)
{
	ListOfPolyElem* lpe = l.head;
	int i =1;
	while ( i != index )
	{
	
		lpe = lpe-> next;
		i++;
	
	}


	return &(lpe->data);
}

 /**************************************************************************************************************************************************/

/* Returns the list of the intersection points between poly1 and poly2 as a polygon
  * poly1 - first polygon of the intersection
  * poly2 - second polygon of the intersection
  */ 
Polygon intersectionPoints(Polygon poly1, Polygon poly2)
{
	PointElement* p1 = poly1.head;
	PointElement* p2 = poly2.head;
	Polygon intersection_points=createPolygon();
	Point p_int;
	double a1=0,a2=0,b1=0,b2=0 ;
	double x_int,y_int ;
	
	do
	{
		/* determining the 1st coef */ 
		a1 = ((p1->next->data.y - p1->data.y) / (p1->next->data.x - p1->data.x ));
		/*determining the origin ordinate*/
		b1 = (p1->data.y - (a1*(p1->data.x)));
		p2 = poly2.head;
	
		 do
		 {
			 a2 = ( (p2->next->data.y - p2->data.y) / (p2->next->data.x - p2->data.x) );
			 b2 = (p2->data.y - (a2*p2->data.x)) ;
		 
			 if (a1-a2 != 0)	
			 {
				x_int = (b2 - b1) / (a1 - a2);
				y_int = a2*x_int + b2;
				p_int = createPoint(x_int,y_int);
				
				/* We look if p_int is between p1 and p2 */ 
				
				 if ( ((x_int >= p1->data.x && x_int <= p1->next->data.x) && (x_int >=p2->data.x && x_int <= p2->next->data.x) )|| ( (x_int <= p1->data.x && x_int >= p1->next->data.x) && (x_int <= p2->data.x && x_int >= p2->next->data.x) ) || ((x_int >= p1->data.x && x_int <= p1->next->data.x) && (x_int <= p2->data.x && x_int >= p2->next->data.x) ) || ((x_int <=  p1->data.x && x_int >= p1->next->data.x) && (x_int >=p2->data.x && x_int <= p2->next->data.x) ) )
				{
					
					intersection_points = addPoint(intersection_points, p_int);
				}
			 }
		 
			p2=p2->next;
		
		 }while(p2 != poly2.head);
	 p1=p1->next;
	}while (p1 != poly1.head);
	
	return intersection_points;
}
/*
 * Returns TRUE if the three points in parameter are aligned, False otherwise.
 * p1 - first point to check
 * p2 - second point to check
 * p3 - third point to check
 */
Boolean AreAligned(Point p1, Point p2, Point p3)
{
	float a,b;
	Boolean aligned = FALSE;
	if ( compare(p1.x,"==",p2.x) && compare(p1.x,"==",p3.x) && compare(p3.x,"==",p2.x) )
	{
		aligned = TRUE;
	}
	else 
	{
		a =(p2.y-p1.y)/(p2.x-p1.x);
		b =(p3.y-p1.y)/(p3.x-p1.x);
		if ( compare(a,"==",b))
		{
			aligned = TRUE;
	
		}
	}
	return aligned;

}



/*
 * computes the intersection between the two specified polygons
 * polyA - first polygon of the intersection
 * polyB - second polygon of the intersection
 */
Polygon intersectionPolygons (Polygon polyA, Polygon polyB)
{
	Polygon intersected_Polygon = createPolygon();
	Polygon intersection_points = intersectionPoints(polyA,polyB);
	PointElement* p1 = polyA.head;
	PointElement* p2 = polyB.head;
	PointElement* p3 = intersection_points.head;
	int i;
	
	intersection_points = intersectionPoints(polyA,polyB);
	
	if (containsPolygon (polyA,polyB) == INTERSECT) /* We check if polyA and PolyB are intersecting*/
	{
		do /* We add the point if he's contained in the other polygon */ 
		{
	
			if ( containsPoint (polyB, p1->data) )
			{ 
			
				intersected_Polygon = addPoint(intersected_Polygon,p1->data);
			
			}
				
		p1=p1->next;
		}while(p1!=polyA.head);
		
		do /* We add the point if he's contained in the other polygon */
		{
			
			if (containsPoint (polyA, p2->data))
			{
		
				intersected_Polygon = addPoint(intersected_Polygon,p2->data);
			
			}
											
		p2=p2->next;
				
		}while(p2!=polyB.head);
	
		for  (i=0;i<intersection_points.size;i++) /* Adding all the intersection points */ 
		{
			intersected_Polygon = addPoint(intersected_Polygon,p3->data);	
	
			p3=p3->next;
	
	
		}
		
	
	
	}
	return intersected_Polygon;
	
	
	

				
}  

/*
 * Computes the convex hull  of the specified polygon using the Graham's method
 * poly - Polygon to transform
 */
Polygon convexHullPolygon (Polygon poly)
{
	int i,index;
	Polygon convexHull = createPolygon();
	PointElement* pe = poly.head;
	Point lowerPoint ;
	PointElement* p_lowerPoint = poly.head;
	AnglePoint* tab = (AnglePoint*) malloc (poly.size*sizeof(AnglePoint));
	index =2;
	if (poly.size <3)
	{
		if (poly.size ==3)/* in the case where the polygon in parameter is a triangle, its convex hull is the polygon itself*/
		{
			return poly;
		}
		else
		{
			/* Assigning to p_lowerPoint the adress of the point with the lowest ordinate (and the lowest abscissa if there is several points with the same ordinate)*/
			do
			{
				if (p_lowerPoint->data.y > pe->data.y)
				{
					p_lowerPoint = pe;
				}
				else if (p_lowerPoint->data.y == pe->data.y)
				{
					if (p_lowerPoint->data.x > pe->data.x)
					{
						p_lowerPoint = pe;
					}
				}
				pe = pe->next;
			
			}while(pe != poly.head);
		

			/* Putting all the points in an array and sorting the array with the bubble sort (according to the angle with the lower point and the abscissa axe)*/
		
			lowerPoint = p_lowerPoint->data;
			pe = p_lowerPoint->next;		
			tab[0].point = lowerPoint;

			for( i = 1 ; i<poly.size; i++)
			{
				tab[i].point = pe->data;
				if (compare(pe->data.x - lowerPoint.x ,"==" ,0)) /*if the points have the same abscissa*/
				{
					if(!compare(pe->data.y - lowerPoint.y ,"==" ,0))/*if they are vertically aligned*/
					{
						tab[i].angle=M_PI/2;	
					}
				}
				else if(compare(pe->data.y - lowerPoint.y ,"==" ,0)) /* if the points are horizontally aligned*/
				{
					if (compare(pe->data.x,"<" ,lowerPoint.x ))
					{
						tab[i].angle=M_PI;
					}
					else
					{
						tab[i].angle=0;
					}
				}
				else 
				{
					tab[i].angle = atan((pe->data.y - lowerPoint.y) / (pe->data.x - lowerPoint.x));
					if (compare(tab[i].angle ,"<",0))
					{
						tab[i].angle=M_PI+tab[i].angle;
					}
				}
				pe=pe->next;
			
			}
		
			bubbleSortTp(&tab[1],poly.size-1);
		
			/*"Transforming" the array in a new polygon*/
			for (i=0;i<poly.size;i++)
			{
					convexHull = addPoint(convexHull, tab[i].point);
			}
		
			/* Selecting the points which will finally compose the convex hull of the polygon */
			pe = convexHull.head->next;
		
			do
			{
			
				if ( compare ( (pe->data.x - pe->prev->data.x)*(pe->next->data.y - pe->prev->data.y) - (pe->data.y - pe->prev->data.y)*(pe->next->data.x - pe->prev->data.x), "<" , 0))
				{
					pe=pe->next;
					convexHull = removePoint(convexHull,index);
				}
				else
				{
					pe = pe-> next;
					index++;			
				}
			
			}while (pe!=convexHull.head);

		
			return convexHull;
		}
	}
	else
	{
		printf("\n\n This polygon has less than 3 points so no modification could be done please retry");
		return poly;
	}
}


/*
 * Sorts the table of AnglePoint entered in parameter (by adress)
 * a - array of AnglePoint to sort
 * size - size of the array a
 */
void bubbleSortTp( AnglePoint* a , int size)
{
	int i;
	Boolean swap; 
	AnglePoint tmp;
	
	do
	{
		swap=FALSE;
		for  (i=0; i<size-1;i++)
		{
			if (compare(a[i].angle, ">", a[i+1].angle))
			{
				tmp = a[i];
				a[i] = a[i+1];
				a[i+1] = tmp;
				swap = TRUE;
			}
			else if (compare (a[i].angle, "==", a[i+1].angle))
			{
				if (compare (a[i].point.x ,">", a[i+1].point.x))
				{
					tmp = a[i];
					a[i] = a[i+1];
					a[i+1] = tmp;
					swap = TRUE;	
				}
			}
		}
		size--;
		
	}while(swap);

}

/*
 * Computes the union between the two specified polygons
 * polyA - first polygon of the union
 * polyB - second polygon of the union
 */
Polygon unionPolygons (Polygon poly1, Polygon poly2)
{
	Polygon Union = createPolygon();
	Polygon intersections = intersectionPoints(poly1,poly2);
	PointElement* p1 = poly1.head ;
	PointElement* p2 = poly2.head ; 
	PointElement* p3 = intersections.head;
	int i;
	
	if ( containsPolygon(poly1,poly2) == INSIDE ) /* If poly2 is inside poly1, we return poly1) */
	{
		return poly1;
	}
	else if ( containsPolygon(poly1,poly2) == ENCLOSING ) /* In the opposite case we return poly2*/
	{
		return poly2;
	}
	else if (containsPolygon(poly1,poly2) == OUTSIDE ) /* If the two polygon are outside, we simply add the two polygons to Union */
	{
		for (i=0;i<poly1.size;i++)
		{
			Union = addPoint(Union,p1->data);
			p1=p1->next;
		}
		for (i=0;i<poly2.size;i++)
		{
			Union = addPoint(Union,p2->data);
			p2=p2->next;
		}
	}
	else
	{	/* We add each points which is not within the other polygon, plus the intersections points*/
		do
		{
			if ( !containsPoint(poly2,p1->data) ) 
			{
				Union = addPoint(Union,p1->data);
				
			}
			p1=p1->next;
		}while(p1!=poly1.head);
		
		do
		{
			if ( !containsPoint(poly1,p2->data))
			{
				Union = addPoint(Union,p2->data);
			}
			p2=p2->next;
		}while(p2!=poly2.head);
		do
		{
			Union = addPoint(Union,p3->data);
			p3=p3->next;
		}while(p3!=intersections.head);
	}
		
	return Union;
	
}

/*
 * computes the exclusive OR between the two specified polygons
 * polyA - first polygon of the exclusive OR
 * polyB - second polygon of the exclusive OR
 */
Polygon exclusiveORPolygons (Polygon poly1, Polygon poly2)
{
	Polygon ExclusiveOR = createPolygon();
	Polygon intersections = intersectionPoints(poly1,poly2);
	PointElement* p1 = poly1.head ;
	PointElement* p2 = poly2.head ; 
	PointElement* p3 = intersections.head;
	int i;
	
	
	/* we add every point of the 3 polygons to ExclusiveOR */
	for (i=0;i<poly1.size;i++) 
	{
		ExclusiveOR = addPoint(ExclusiveOR,p1->data);
		p1=p1->next;
	}
	for (i=0; i<poly1.size;i++)
	{
		ExclusiveOR = addPoint(ExclusiveOR,p2->data);
		p2=p2->next;
	}
	for(i=0; i<intersections.size ;i++)
	{
		ExclusiveOR = addPoint(ExclusiveOR,p3->data);
		p3=p3->next;
	}
	
	
	return ExclusiveOR;
}	

/*
 * computes the difference between the two specified polygons
 * polyA - first polygon of the difference
 * polyB - second polygon of the difference
 */
Polygon differencePolygons(Polygon poly1, Polygon poly2)
{
	Polygon Difference = createPolygon();
	Polygon intersections = intersectionPoints(poly1,poly2);
	PointElement* p1 = poly1.head ;
	PointElement* p2 = poly2.head;
	PointElement* p3 = intersections.head;
	int i;
	
	
	if (  containsPolygon (poly1,poly2) == INSIDE ) /* If the poly2 is inside poly1*/
	{
		for (i=0;i<poly1.size;i++) 
		{
			Difference = addPoint(Difference,p1->data);
			p1=p1->next;
		}
		for (i=0; i<poly1.size;i++)
		{
			Difference = addPoint(Difference,p2->data);
			p2=p2->next;
		}
	}
	else if (containsPolygon (poly1,poly2) == ENCLOSING) /* If poly1 is inside poly2 */
	{
		return Difference;
	}
	else if (containsPolygon (poly1,poly2) == OUTSIDE) /* If they are outside */ 
	{
		return poly1;
	}
	
	/* We add the points of poly1 to Difference only if this point is not contained in poly2 */
	else 
	{
		do
		{
			if ( !containsPoint(poly2,p1->data) )
			{
				Difference = addPoint(Difference,p1->data);
			}
		p1=p1->next ;
		
		}while (p1!=poly1.head);
	
		/*we add each intersections points to Difference */
		for (i=0;i<intersections.size;i++)
		{
			Difference = addPoint(Difference,p3->data);
			p3=p3->next;
		}
	
		
	}
	
	return Difference;
}

	
	/*********************************** Freeing functions ***********************************************/



/*
 * Frees the memory corresponding to the specified polygon
 * poly - polygon to free
 */
void freePolygon(Polygon* p_poly)
{
	PointElement* p_pe;
	
	if (p_poly == NULL)
	{
			printf("Error, no polygon to free");
	}
	else if (p_poly-> head != NULL)
	{
		p_pe = p_poly-> head;
		
			p_pe->prev->next=NULL;
			p_pe->prev=NULL;
			p_pe = p_pe -> next;
			
		do
		{	
			
			p_pe->prev->next=NULL;
			free(p_pe->prev);
			p_pe->prev=NULL;
			p_pe = p_pe -> next;
			
		}while ( p_pe != NULL);
	}

}

/* Frees the memory corresponding to the whole list of polygons 
 * l - list to free
 */
void freeListOfPoly( ListOfPoly l)
{
	ListOfPolyElem* p_lpe;
	
	if (l. head != NULL)
	{
		if (l.size ==1)
		{
				freePolygon(&(l.head->data));
				free(l.head);
				l.head=NULL;
		}
		else
		{
			p_lpe =l. head;
			p_lpe = p_lpe -> next;
				
			while ( p_lpe != NULL)
			{	
				
				p_lpe->prev->next=NULL;
				freePolygon(&(p_lpe->prev->data));
				free(p_lpe->prev);
				p_lpe->prev=NULL;
				
				
				if (p_lpe->next == NULL)
				{
					freePolygon(&(p_lpe->data));
					free(p_lpe);
					p_lpe=NULL;
				}
				else
				{
					p_lpe = p_lpe -> next;
				}
				
			}
		}
		
	}
	

}
	
	
	
	


