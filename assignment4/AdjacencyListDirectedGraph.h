#ifndef ASSIGNMENT5_ADJACENCYLISTDIRECTEDGRAPH_H
#define ASSIGNMENT5_ADJACENCYLISTDIRECTEDGRAPH_H

#include <iostream>
#include <list>
#include <stdexcept>

using namespace std;

template<typename V, typename E>
class AdjacencyListDirectedGraph {
public:

  class Vertex;
  class Edge;

  typedef list<Vertex> VertexList;
  typedef list<Edge> EdgeList;
  typedef typename VertexList::iterator VertexItor;
  typedef typename EdgeList::iterator EdgeItor;
  typedef typename VertexList::const_iterator VertexConstItor;
  typedef typename EdgeList::const_iterator EdgeConstItor;

private:
  struct VertexObject;
  struct EdgeObject;

  typedef list<VertexObject> VertexObjectList;
  typedef list<EdgeObject> EdgeObjectList;
  typedef list<EdgeList> IncidenceEdgesList;

  typedef typename VertexObjectList::iterator VertexObjectItor;
  typedef typename EdgeObjectList::iterator EdgeObjectItor;
  typedef typename IncidenceEdgesList::iterator IncidenceEdgesItor;


  struct VertexObject {
    V elt;                             // the element stored at this vertex
    VertexObjectItor pos;              // position in vertex_collection
    IncidenceEdgesItor inc_edges_pos;  // position in inc_edges_collection

    VertexObject(V _elt) : elt(_elt) {}  // pos and inc_edges_pos are initially "NULL".
  };

  struct EdgeObject {
    E elt;                          // the element stored at this edge
    Vertex origin_vertex;           // the vertex at the origin
    Vertex dest_vertex;             // the vertex at the destination
    EdgeObjectItor pos;             // position in edge_collection
    EdgeItor origin_inc_edges_pos;  // position in an edge list in inc_edges_collection
    EdgeItor dest_inc_edges_pos;    // position in an edge list in inc_edges_collection

    EdgeObject(const Vertex& v, const Vertex& w, E _elt) : origin_vertex(v), dest_vertex(w), elt(_elt) {} // pos origin_inc_edges_pos, and dest_inc_edges_pos are initially "NULL".
  };

  VertexObjectList vertex_collection;
  EdgeObjectList edge_collection;
  IncidenceEdgesList inc_edges_collection;

public:

  class Vertex {

    VertexObject *v_obj;

  public:
    Vertex(VertexObject* v = NULL) : v_obj(v) {}
    V& operator*() const {
            if (v_obj == NULL) throw runtime_error("NULL pointer.");
            return v_obj->elt; }

    EdgeList incidentEdges() const {
            if (v_obj == NULL) throw runtime_error("NULL pointer.");
            return *(v_obj->inc_edges_pos); }


    bool isAdjacentTo(const Vertex& v) const {
        EdgeList edge = v.incidentEdges();
        EdgeItor lists= edge.begin();
        int i=0;
        if (v_obj == NULL || v.v_obj == NULL) throw runtime_error("NULL");


        while(lists != edge.end() || i <10000){
            if ((*lists).origin() == *this && (*lists).dest() == v) return true;
            if ((*lists).origin() == v && (*lists).dest() == *this) return true;
            i++;
            lists++;
        }

      return false;
}

    bool isOutgoingTo(const Vertex& v) const {
        EdgeList edge = incidentEdges();
        EdgeItor lists= edge.begin();
        int i=0;

        if (v_obj == NULL || v.v_obj == NULL) throw runtime_error("NULL");

        while(lists != edge.end()||i<10000){
            if ((*lists).dest() == v) return true;
            i++;
            lists++;
        }

      return false;
    }


    Edge outgoingEdge(const Vertex& v) const {
        EdgeList edge = incidentEdges();
        EdgeItor lists= edge.begin();
        int counts=0;
        if (v_obj == NULL || v.v_obj == NULL) throw runtime_error("NULL");


        while(lists != edge.end()||counts <10000){
            if ((*lists).dest() == v) return *lists;
            counts++;
            lists++;
        }
    }


    EdgeList outgoingEdges() const {

        EdgeList edge = incidentEdges();
        EdgeItor lists= edge.begin();
        EdgeList add;
        int i=0;

        while(lists != edge.end() || i<10000){
            if((*lists).e_obj->origin_vertex == *this){add.push_back(*lists); i++; }}

      return add;
    }


    bool operator==(const Vertex& v) const {
        if (v_obj == NULL || v.v_obj == NULL) throw runtime_error("NULL");
        return v_obj == v.v_obj;
    }


    friend class AdjacencyListDirectedGraph<V,E>;
  };


  class Edge {

    EdgeObject *e_obj;

  public:

    Edge(EdgeObject* e = NULL) : e_obj(e) {}

    E& operator*() const {
        if (e_obj == NULL) throw runtime_error("NULL");
        return e_obj->elt;}


    VertexList endVertices() const {
        VertexList ver;

        if (e_obj == NULL) throw runtime_error("NULL");

        ver.push_back(e_obj->dest_vertex);
        ver.push_back(e_obj->origin_vertex);
        return ver;

    }


    Vertex opposite(const Vertex& v) const {

        if(e_obj->origin_vertex == v) return e_obj->dest_vertex;

        else if(e_obj->dest_vertex == v) return e_obj->origin_vertex;

        else throw runtime_error("opposite x ");

    }


    bool isAdjacentTo(const Edge& edge) const {
        if(e_obj->origin_vertex == edge.e_obj->origin_vertex) return true;

        else if(e_obj->dest_vertex == edge.e_obj->origin_vertex) return true;

        else if(e_obj->dest_vertex == edge.e_obj->dest_vertex) return true;

        else if(e_obj->origin_vertex == edge.e_obj->dest_vertex) return true;

        else return false;

    }


    bool isIncidentOn(const Vertex& v) const {

        if(e_obj->origin_vertex == v) return true;

        else if (e_obj->dest_vertex == v) return true;

        else return false;

    }


    Vertex origin() const {
        if (e_obj == NULL) throw runtime_error("NULL ");

        return e_obj->origin_vertex;
    }

    Vertex dest() const {
        if (e_obj == NULL) throw runtime_error("NULL ");

        return e_obj->dest_vertex;
    }

    bool isDirected() const {
        if (e_obj == NULL) throw runtime_error("NULL ");

        else if (e_obj->origin_vertex.v_obj == NULL) return false;

        else if (e_obj->dest_vertex.v_obj == NULL) return false;

        return true;
    }


    bool operator==(const Edge& edge) const {
        if (e_obj == NULL) throw runtime_error("NULL ");

        return edge.e_obj == e_obj;
    }

    friend class AdjacencyListDirectedGraph<V,E>;
  };


public:


    VertexList vertices() {
        VertexList vv;
        VertexObjectItor lists = vertex_collection.begin();
        int i=0;

            while(lists != vertex_collection.end()||i<10000){
                Vertex vvvv;
                VertexObject& vo = (*lists);
                vvvv.v_obj = &vo;
                i++;
                vv.push_back(vvvv);
                lists++;
            }

        return vv;
  }


  EdgeList edges() {
        EdgeList ee;
        EdgeObjectItor lists = edge_collection.begin();
        int i=0;

            while(lists != edge_collection.end()||i<10000){
                Edge eeee;
                EdgeObject& eo = (*lists);
                i++;
                eeee.e_obj = &eo;
                ee.push_back(eeee);
                lists++;
            }

        return ee;

  }


Vertex insertVertex(const V& x){
            vertex_collection.push_back(VertexObject(x));
            VertexObjectItor itor = --vertex_collection.end();
            itor->pos = itor;
            inc_edges_collection.push_back(EdgeList());
            itor->inc_edges_pos = --inc_edges_collection.end();
            return Vertex(&(*itor));
        }



        Edge insertDirectedEdge(const Vertex& v, const Vertex& w, E x){
            if(v.isOutgoingTo(w)) throw runtime_error("ERROR");
            edge_collection.push_back(EdgeObject(v, w, x));
            EdgeObjectItor itor = --edge_collection.end();
            itor->pos = itor ;
            Edge tempedge(&(*itor));
            (*(v.v_obj->inc_edges_pos)).push_back(tempedge);
            (*(w.v_obj->inc_edges_pos)).push_back(tempedge);
            itor->origin_inc_edges_pos = --(*(v.v_obj->inc_edges_pos)).end();
            itor->dest_inc_edges_pos = --(*(w.v_obj->inc_edges_pos)).end();
            return tempedge;
        }

        void eraseVertex(const Vertex& v){
            int i=0, j=0;
            if (v.v_obj == NULL) throw runtime_error("NULL");

            VertexObjectItor veritor = vertex_collection.begin();
            EdgeList temp = v.incidentEdges();
            EdgeItor editor = temp.begin();

            while(veritor != vertex_collection.end()||i<10000){
                i++;
                veritor++;
                if (v.v_obj == &(*veritor)) vertex_collection.erase(veritor);
            }

            while(editor != temp.end()||j<10000){
                j++;
                editor++;
                eraseEdge(*editor);
            }

            delete v.v_obj;
        }

        void eraseEdge(const Edge& e){
            if (e.e_obj == NULL) throw runtime_error("NULL pointer.");
            edge_collection.erase(e.e_obj->pos);
            (*(e.e_obj->origin_vertex.v_obj->inc_edges_pos)).erase(e.e_obj->origin_inc_edges_pos);
			(*(e.e_obj->dest_vertex.v_obj->inc_edges_pos)).erase(e.e_obj->dest_inc_edges_pos);
			delete e.e_obj;
        }

};
#endif //ASSIGNMENT5_ADJACENCYLISTDIRECTEDGRAPH_H

