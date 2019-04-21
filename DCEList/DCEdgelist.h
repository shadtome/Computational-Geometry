#ifndef DOUBLECONNECTEDEDGELIST_H
#define DOUBLECONNECTEDEDGELIST_H

#include <LineInter/Point.h>
#include <vector>

//Forward Declerations
struct Half_Edge;
struct Face;


/* information about the vertex
* Holds the coordinates, and a arbitrary half edge that starts at
* this vertex.
*/
struct Vertex
{
  Point2 coordinates;

  //arbitrary Half edge that starts here
  Half_Edge* incident_Edge;

  //Need Constructors/Copy Constructors/ Destructors/copy assighment constructors
};

/* Half-edge
* Holds origin/face it bounds and its twin
*/
struct Half_Edge
{
  //Where this half edge starts
  Vertex* origin;

  //Twin half edge
  Half_Edge* twin;

  //Face it bounds
  Face* incident_Face;
};

/* Face
* Holds pointer to some outer half edge on the outer component,
* for unbounded faces, this would be nullptr.
* Also, holds a collection of pointers to a arbitrary half-edge in the holes.
*/
struct Face
{
  //Pointer to a arbitrary half edge that bounds this face
  Half_Edge* outer_Component;

  //Collection of pointers to the holes in the face
  std::vector<Half_Edge*> holes;
};


/* Doubly Connected edge list.
* contains all the vertices of this planar graph (does not need to be connected)
*
*/
class DCEL
{
  //Collection of Vertices (keep them all togetherhere)
  std::vector<Vertex> vertices;

  //Collection of Half-edges
  std::vector<Half_Edge> half_edges;

  //collection of Faces
  std::vector<Face> faces;



};



#endif
