/************************************************************************
 * This file contains the main function of the LO27 project : 
 * Designing a C library to manipulate 2D polygons and making
 * a simple program to test this library.
 * Authors: Clement BARETH - Antoine COUPAT
 * Semester : A2014
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "polygon.h"
#include "dataStructures.h"

#define EXIT_SUCCESS 0


int main (int argc, char* argv[])
{

	int mainMenu,i,nbPointAdd, choice;

	double x,x2,y,y2,angle,factor;
	Point point,A,B;
	Polygon poly,poly2;
	Polygon* p_poly;
	char* str;
	

	/*PointElement* p_pe;*/
	
	ListOfPoly l=initList();
	
	
	do
	{	
		printf("\n\n\n================================  POLYGONS  ====================================\n\n");
		printf("Please chose one of the following options :\n\n");
		printf("\t1. Add a polygon\n\n");
		printf("\t2. Modify a polygon\n\n");
		printf("\t3. Boolean operations (intersection, exclusive or etc...)\n\n");	
		printf("\t4. Containing functions\n\n");	
		printf("\t5. Basic operations\n\n");	
		printf("\t6. Print functions\n\n\n\n");
		
		printf("\t0. Exit program\n\n");

	
	
		mainMenu=getInt(0,6,"Wrong input please retry with a value between 0 and 6");
		printf("\n\n");
		
		switch(mainMenu)
		{
		
		
		
			printf("\n\n");
			
		
			case 1:
		
				printf("\n\n\n================================  ADD A POLYGON  ====================================\n\n");
				
				l = addPoly(l , createPolygon());
				i=4;

						
						
				printf("You have to enter at least three points\n\n");

				printf("\nx1 :"); 
				scanf("%lf",&x);
				printf("y1 :");
				scanf("%lf",&y);
				l.last->data=addPoint(l.last->data,createPoint(x,y)); /* Adding the point to the polygon*/
				
				/* Asking the coordinates of the second point to the user*/
				printf("\nx2 :"); 
				scanf("%lf",&x2);
				
				printf("y2 :");
				scanf("%lf",&y2);
				
				if (x == x2)
				{
					while ( y2 == y)
					{
						printf("The two points you just entered are the same, please enter a different ordinate for the second point\n\n");
						printf("y2 :");
						scanf("%lf",&y2);
					}
				}
				l.last->data=addPoint(l.last->data,createPoint(x2,y2));
				
				/* Asking to the user a third point for the polygon */
				printf("\nThe third point must not be aligned with the previous points\n");
			
				
				printf("x3 :");
				scanf("%lf",&x);
				printf("y3 :");
				scanf("%lf",&y);
				/*Creating a point to verify if the three points are aligned*/
				point.x =x; 
				point.y=y;
				
				/* Checking if the three points are not aligned, if they are, re-asking other coordinates until they work*/
				while (AreAligned(l.last->data.head->data,l.last->data.head->next->data,point)) 
				{
					printf("\n The three points are aligned, please enter other coordinates for the third point \n");
					printf("\nx3 :");
					scanf("%lf",&x);
					printf("y3 :");
					scanf("%lf",&y);
					point.x=x;
					point.y=y;
					
				}
				printf("\n\nPoint accepted\n\n");
				l.last->data=addPoint(l.last->data,point);	
				
				/* Asking the user if he wants to add more than 3 points to the polygon*/
				i=0;
				printf("\n How many points do you want to add ? (0 if you don't want to add other points)");
				nbPointAdd = getInt(0,20,"Wrong input, please enter a correct number of points");
				
				while (i!=nbPointAdd)/* Asking the user to enter the two first points of the polygon*/
				{
					printf("\nx%d :",i+4);
					scanf("%lf",&x);
					printf("y%d :",i+4);
					scanf("%lf",&y);
					l.last->data=addPoint(l.last->data,createPoint(x,y));	
					i++;
				
				}
				
				
				printf("\n\n\n\n ====================================== List of polygons updated ==================================\n\n");
				
				printListOfPoly(l);
				
				
				printf("\n\n\n\t0. Main menu\n\n");
		
				choice = getInt(0,0,"Wrong input, please enter 0 to return to the main menu");
		
			break;
		
			case 2:
				printf("\n\n\n================================  MODIFY A POLYGON  ====================================\n\n\n\n");
			
				
				if (l.size != 0)
				{
					printListOfPoly(l);
					printf("\n\nWhich polygon do you want to modify ? :");
					i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
					p_poly = selectPolygonP(l,i);
				
					printf("\n\n What do you want to do with the polygon n°%d ?",i);
					printf("\n\n      1. Add a point at the end of the list\n");
					printf("      2. Remove a point of your choice\n\n"); 

				
					choice = getInt(1,2,"Wrong input, please retry with a value between 1 and 2");
				
					switch(choice)
					{
						case 1:
							
							printf("Please enter the coordinates of the point you want to add\n\n");
							printf("x :");
							scanf("%lf",&x);
							printf("y :");
							scanf("%lf",&y);
							*p_poly=addPoint(*p_poly, createPoint(x,y));
							printf("Point added successfully");
							printPolygon(*p_poly);
						
						
						break;
				
						case 2:
						
							if (p_poly->size >3)
							{
							
								printf("Which point do you want to remove ? (enter the index of the point)\n\n");
								i = getInt(1,p_poly->size,"There is no point corresponding to this index, please retry");
								*p_poly = removePoint(*p_poly,i);
								printf("\n\n The point n°%d was succesfully removed \n\n",i);
								
								
								printPolygon(*p_poly);
								
							}
							else 
							{
								printf("\nThis polygon has three points, if you remove one of them it would not be a polygon anymore\n");
							}
							
						break;
					
					}
				}
				else 
				{
					printf("There is no polygon to modify, please return to main menu and add a polygon\n");
				}	
				printf("\n\t0. Main menu\n\n");
				choice = getInt(0,0,"Wrong input, please enter 0 to go back to the main menu");
		
			break;
		
			case 3:
				
				do{
					printf("\n\n\n================================  BOOLEAN FUNCTIONS  ====================================\n\n\n\n");
					printf("\t1. Union \n\n");
					printf("\t2. Intersection \n\n");
					printf("\t3. Exclusive OR\n\n");	
					printf("\t4. Difference\n\n");
				
					printf("\n\n\n\t0. Main menu\n\n");
					
					if (l.size > 1)
					{
						choice = getInt(0,5,"Wrong input, please retry with a value between 0 and 5");
						
						switch(choice)
						{
							
							case 1:
							
								printListOfPoly(l);
								printf("\n\nPlease select the first polygon:");
								i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
								poly = selectPolygon(l,i);
								printf("\n\nPlease select the second polygon:");
								i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
								poly2 = selectPolygon(l,i);
								
								printf("\n\n ======= The Union between those two polygons is : ==============\n\n");
							
								printPolygon(unionPolygons(poly,poly2));
								printf("\n\n  A_____ The union between the two polygons is displayed above _____A  \n");
								
							break;
							
							case 2:
								
								printListOfPoly(l);
								printf("\n\nPlease select the first polygon:");
								i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
								poly = selectPolygon(l,i);
								printf("\n\nPlease select the second polygon:");
								i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
								poly2 = selectPolygon(l,i);
								
								printf("\n\n ======= The intersection between those two polygons is : ==============\n\n");
							
								printPolygon(intersectionPolygons(poly,poly2));
								printf("\n\n  A_____ The intersection between the two polygons is displayed above _____A  \n");
								
							break;
							
							case 3:
								
								printListOfPoly(l);
								printf("\n\nPlease select the first polygon:");
								i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
								poly = selectPolygon(l,i);
								printf("\n\nPlease select the second polygon:");
								i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
								poly2 = selectPolygon(l,i);
								
								printf("\n\n ======= The Exclusive OR between those two polygons is : ==============\n\n");
							
								printPolygon(exclusiveORPolygons(poly,poly2));
								printf("\n\n  A_____ The exclusive OR between the two polygons is displayed above _____A  \n");
								
							break;
							
							case 4:
								
								printListOfPoly(l);
								printf("\n\nPlease select the first polygon:");
								i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
								poly = selectPolygon(l,i);
								printf("\n\nPlease select the second polygon:");
								i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
								poly2 = selectPolygon(l,i);
								
								printf("\n\n ======= The Difference between those two polygons is : ==============\n\n");
							
								printPolygon(differencePolygons(poly,poly2));
								printf("\n\n  A_____ The difference between the two polygons is displayed above _____A  \n");
								
							break;
							
							
						}
					
					}
					else
					{
						printf("There is not enough polygon in the list, please return to main menu and add a polygon\n");
						choice = getInt(0,0,"Wrong input, please enter 0 to return to the main menu");
					}
					
					
					
					
				}while(choice !=0);
			break;
		
			case 4:
				do
				{
					printf("\n\n\n================================  CONTAINING FUNCTIONS  ====================================\n\n\n\n");
					printf("You want to know if a polygon contains :\n\n");
					printf("\t1. A Point \n\n");
					printf("\t2. Another Polygon \n\n");
					printf("\n\n\n\t0. Main menu\n\n");
					
					if (l.size !=0)
					{
						
						
						choice=getInt(0,2,"Wrong input, please retry with a value between 0 and 2");						
						
						switch(choice)
						{
							case 1:
								
								printListOfPoly(l);
								printf("\n\nWhich polygon do you want to test ? :");
								i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
								poly = selectPolygon(l,i);
							
								printf("\n\nPlease enter the coordinates of the point you want to test\n\n");
								printf("x =");
								scanf("%lf",&(point.x));
								printf("y =");
								scanf("%lf",&(point.y));
							
								if (containsPoint(poly, point))
								{
									printf("\nThe point with the coordinates (%.2f,%.2f) is contained in the polygon\n",point.x,point.y);
								}	
								else
								{
									printf("\nThe point with the coordinates (%.2f,%.2f) is not contained in the polygon\n",point.x,point.y);				
								}	
							
							break;
							
							case 2:
									
								printListOfPoly(l);
								printf("\n\nPlease select the first polygon:");
								i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
								poly = selectPolygon(l,i);
								printf("\n\nPlease select the second polygon:");
								i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
								poly2 = selectPolygon(l,i);
							
								
							
								switch ( containsPolygon(poly,poly2) )
								{ 
									case INSIDE :
										printf ("\n\nThe second polygon is inside the first one\n");
										break;
									case OUTSIDE : 
										printf("\n\nThe second polygon is outside the first one\n");
										break;
									case INTERSECT :
										printf("\n\nThe two polygons are intersecting\n");
										break;
									case ENCLOSING : 
										printf("\n\nThe second polygon encloses the first one\n");
										break;
									case EQUAL :
										printf ("\n\nThe two polygons are equals \n");
										break; 
								}
							
								
									
								
							break;
					
					
						}
					}	
					else 
					{
						printf("There is no polygon to test, please return to main menu and add a polygon\n");
						choice = getInt(0,0,"Wrong input, please enter 0 to return to the main menu");
					}	
					
					
				
				}while(choice != 0);
			break;
		
			case 5:
			
				do
				{
					printf("\n\n================================  BASIC OPERATIONS  ====================================\n\n\n\n");
					printf("\t1. Translation \n\n");
					printf("\t2. Rotation \n\n");
					printf("\t3. Central Symmetry\n\n");	
					printf("\t4. Scale\n\n");
					printf("\t5. Convex Hull Form\n\n");

					printf("\n\t0. Main menu\n\n");
					choice = getInt(0,5,"Wrong input, please retry with a value between 0 and 5");
						
					if (l.size !=0)
					{
						if (choice !=0)
						{
						
							printListOfPoly(l);
							printf("\n\nPlease select a polygon to transform :");
							i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
							poly = selectPolygon(l,i);
							
							
							switch(choice)
							{
								
								case 1:
									
									printf("\n\n Please enter the coordinates of the translation vector");
									printf("\nAx =");
									scanf("%lf",&A.x);
									printf("\nAy =");
									scanf("%lf",&A.y);
									printf("\nBx =");
									scanf("%lf",&B.x);
									printf("\nBy =");
									scanf("%lf",&B.y);
										
									printf("\n\n... BEFORE TRANSLATION ...\n\n");
									printPolygon(poly);
									printf("\n\n... AFTER TRANSLATION BY THE VECTOR AB (%0.2f,%0.2f) ...\n\n",B.x-A.x,B.y-A.y);
									printPolygon(translatePolygon(poly,A,B));
									printf("\n\n  A_____ The new version of the polygon is displayed above _____A  \n");
								
								break;
								
								case 2:
									
									printf("\n\n Please enter the coordinates of the center of the rotation");
									printf("\nAx =");
									scanf("%lf",&A.x);
									printf("\nAy =");
									scanf("%lf",&A.y);
									printf("\nPlease enter the angle of rotation (in radians)");
									scanf("%lf",&angle);
										
									printf("\n\n... BEFORE ROTATION ...\n\n");
									printPolygon(poly);
									printf("\n\n... AFTER ROTATION AROUND THE POINT O (%0.2f,%0.2f) WITH AN ANGLE a = %0.2f rad ...\n\n",A.x,A.y,angle);
									printPolygon(rotatePolygon(poly,A,angle));
									printf("\n\n  A_____ The new version of the polygon is displayed above _____A  \n");
									
								break;
								
								case 3:
									
									printf("\n\n Please enter the coordinates of the center of the symmetry");
									printf("\nAx =");
									scanf("%lf",&A.x);
									printf("\nAy =");
									scanf("%lf",&A.y);
							

									printf("\n\n... BEFORE SYMMETRY ...\n\n");
									printPolygon(poly);
									printf("\n\n... AFTER SYMMETRY AROUND THE POINT O (%0.2f,%0.2f) ...\n\n",A.x,A.y);
									printPolygon(centralSymmetry(poly,A));
									printf("\n\n  A_____ The new version of the polygon is displayed above _____A  \n");
									
								break;
								
								case 4:
									printf("\n\n Please enter the factor of scaling");
									scanf("%lf",&factor);
							

									printf("\n\n... BEFORE SCALING...\n\n");
									printPolygon(poly);
									printf("\n\n... AFTER SCALING ACCORDING TO THE BARYCENTER OF THE POLYGON ...\n\n");
									printPolygon(scalePolygon(poly,factor));
									printf("\n\n  A_____ The new version of the polygon is displayed above _____A  \n");
									
								break;
								
								case 5:
									
									poly = convexHullPolygon(poly);
									printf("\nThe convex Hull of the polygon is :\n");
									printPolygon(poly);
									printf("\n\n  A_____ The convex hull of the polygon is displayed above _____A  \n");

									
								break;
								
								
							}
						}
					}
					else
					{
						printf("There is no polygon to modify, please return to main menu and add a polygon\n");
						choice = getInt(0,0,"Wrong input, please enter 0 to return to the main menu");
					}
					
					
					
					
				}while(choice !=0);
		
			break;
		
			case 6:
		
			do
			{	
				printf("\n\n\n================================  Printing  ====================================\n\n\n\n");
				printf("You want to print :\n\n");
				printf("\t1. The list of current polygons  \n\n");
				printf("\t2. A string with the coordinates of the points\n\n");
			
				printf("\n\n\n\t0. Main menu\n\n");
				
				if (l.size != 0)
				{
					choice = getInt(0,2,"Wrong input, please retry with a value between 0 and 2");
				
					switch(choice)
					{
						case 1:
							
							printListOfPoly(l);
							printf("\n\n  A_____ The list of polygons is displayed above _____A  \n\n");
							
							

						break;
						
						case 2:
							
							printListOfPoly(l);
							printf("\n\nWhich polygon do you want to test ? :");
							i = getInt(1,l.size,"Wrong input, this polygon does not exist, please retry");
							poly = selectPolygon(l,i);
							str = toString(poly);
							printf("\n\n ======================  Formated coordinates ====================\n\n");
							printf("\n The polygon chosen has the following coordinates \n");
							printf("\n\n%s\n\n",str);
							printf("\n\n  A_____ The string is displayed above _____A  \n\n");


							
						break;
						
					}
				}
				else
				{
					printf("There is no polygon in the list, please return to the main menu and add a polygon\n");
					choice = getInt(0,2,"Wrong input, please retry with a value between 0 and 2");
					
				}
				
				
			
			}while(choice!=0);
		
			break;
		
		}
	}while(mainMenu!=0);
	
	freeListOfPoly(l);
	
	printf("\n\n================ Good bye , thank you for using this program ========================\n\n");
	
	return EXIT_SUCCESS;
	
	


}

