#ifndef __BASE_GRAPH__H__
#define __BASE_GRAPH__H__

#include "GraphCommon.h"
#include <tr1/unordered_map>
#include <tr1/unordered_set>

namespace GraphModel
{
    class BaseEdge
    {
    public:
        BaseEdge();
        BaseEdge(const VertexId& front_vertex_id, const VertexId& tail_vertex_id);
        BaseEdge(const VertexId& front_vertex_id, const VertexId& tail_vertex_id, double weight);
        virtual ~BaseEdge();

    public:
        inline const VertexId& getAdjVertex(const VertexId& vertex_id) const
        {
            if (VertexIdComp(vertex_id, front_vertex_id_) == 0)
                return tail_vertex_id_;
            else if (VertexIdComp(vertex_id, tail_vertex_id_) == 0 )
                return front_vertex_id_;
            else
                return ERROR_VERTEX_ID;
        }

        bool isSameEdge(const BaseEdge& edge) const;
        bool operator==(const BaseEdge& edge) const;

        virtual void printEdgeMsg() const;
    public:
        VertexId front_vertex_id_;
        VertexId tail_vertex_id_;
        double weight_;
    };

    typedef std::tr1::unordered_set<BaseEdge*> EdgeSet;

    class BaseVertex
    {
    public:
        BaseVertex();
        BaseVertex(const VertexId& vid);
        virtual ~BaseVertex();

    public:
        void addEdge(BaseEdge * edge);
        void removeEdge(BaseEdge * edge);

        bool isAdjVertex(BaseVertex * vertex) const;
        bool operator==(const BaseVertex& vertex) const;

        inline uint32_t getDegree() const
        {
            return adj_edges_.size();
        }

        virtual void printVertexMsg() const;

    public:
        VertexId vid_;
        EdgeSet adj_edges_;
    };

    typedef std::tr1::unordered_map<VertexId, BaseVertex*> IdToVertexMap;
    class BaseGraph
    {
    public:
        BaseGraph();
        virtual ~BaseGraph();

    public:
        virtual bool addEdge(const VertexId& front_vertex_id, const VertexId& tail_vertex_id);
        virtual bool addEdge(const VertexId& front_vertex_id, const VertexId& tail_vertex_id, double weight);
        bool isVertexExist(const BaseVertex * vertex) const;
        
        virtual bool readGraph(const char * filepath);
        virtual void printGraphMsg() const;

    public:
        uint32_t edge_num_;
        IdToVertexMap vertex_map_;
    };

}

#endif //__BASE_GRAPH__H__
