#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QDebug>



namespace old {
class Object3D;

class Vertex
{
public:
   Vertex();
   Vertex(float x, float y, float z);

   int index;
   //float position[3];
   QVector3D position;
   float normal[3];
   //QVector3D position;
   //QVector3D color;
   bool selected;
};

inline Vertex::Vertex() : selected(false) {}



//class VertexArray
//{
//public:
//    VertexArray();
//    Object3D* owner;
//};

//typedef std::vector<Vertex*> VertexArray;
//Q_DECLARE_METATYPE(VertexArray*);

}

#endif // VERTEX_H











