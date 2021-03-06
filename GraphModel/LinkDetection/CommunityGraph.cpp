#include "CommunityGraph.h"
#include "GraphCommon/CommonTools.h"
#include <fstream>
#include <iostream>

namespace GraphModel
{
    Edge::Edge(const VertexId& front_vertex_id, const VertexId& tail_vertex_id):BaseEdge(front_vertex_id, tail_vertex_id) {}

    Vertex::Vertex(const VertexId& vid):BaseVertex(vid) {}


    Graph::Graph():BaseGraph() {}
 
    bool Graph::addEdge(const VertexId& front_vertex_id, const VertexId& tail_vertex_id)
    {
        if (VertexIdComp(front_vertex_id, tail_vertex_id) == 0)
        {
//            std::cout << "[Error][Same VertexId: " << front_vertex_id << "]\n";
//            fprintf(stderr, "[Error][Same VertexId]\n");
            return false;
        }

        BaseVertex * f_vertex;
        BaseVertex * t_vertex;
        IdToVertexMap::iterator itr = vertex_map_.find(front_vertex_id);
        if (itr == vertex_map_.end())
        {
            f_vertex = new Vertex(front_vertex_id);
            vertex_map_[front_vertex_id] = f_vertex;
        }
        else
        {
            f_vertex = itr->second;
        }

        itr = vertex_map_.find(tail_vertex_id);
        if (itr == vertex_map_.end())
        {
            t_vertex = new Vertex(tail_vertex_id);
            vertex_map_[tail_vertex_id] = t_vertex;
        }
        else
        {
            t_vertex = itr->second;
        }

        if (f_vertex->isAdjVertex(t_vertex))
        {
//            fprintf(stderr, "[Error][Edge is exist]\n");
//            std::cout << "[Error][Edge "<< front_vertex_id << "----" << tail_vertex_id <<" is exist]\n";
            return false;
        }

        BaseEdge * edge = new Edge(front_vertex_id, tail_vertex_id);
        f_vertex->addEdge(edge);
        t_vertex->addEdge(edge);

        edge_num_ ++;
        return true;
    }

    bool Graph::addEdge(const VertexId& front_vertex_id, const VertexId& tail_vertex_id, double weight)
    {

        if (VertexIdComp(front_vertex_id, tail_vertex_id) == 0)
        {
//            fprintf(stderr, "[Error][Same VertexId]\n");
            return false;
        }

        BaseVertex * f_vertex;
        BaseVertex * t_vertex;
        IdToVertexMap::iterator itr = vertex_map_.find(front_vertex_id);
        if (itr == vertex_map_.end())
        {
            f_vertex = new Vertex(front_vertex_id);
            vertex_map_[front_vertex_id] = f_vertex;
        }
        else
        {
            f_vertex = itr->second;
        }

        itr = vertex_map_.find(tail_vertex_id);
        if (itr == vertex_map_.end())
        {
            t_vertex = new Vertex(tail_vertex_id);
            vertex_map_[tail_vertex_id] = t_vertex;
        }
        else
        {
            t_vertex = itr->second;
        }

        if (f_vertex->isAdjVertex(t_vertex))
        {
//            fprintf(stderr, "[Error][Edge is exist]\n");
            return false;
        }

        BaseEdge * edge = new Edge(front_vertex_id, tail_vertex_id);
        edge->weight_ = weight;
        f_vertex->addEdge(edge);
        t_vertex->addEdge(edge);

        edge_num_ ++;
        return true;
    }

    bool Graph::readGraph(const char * filepath)
	{
        std::ifstream fin(filepath);
	    if(!fin)
	    {
		    fprintf(stderr, "[error][Can not Open file: %s]\n",filepath);
		    return false;
		}

		string line;
		vector<string> fields;
		while(getline(fin, line))
		{
	        split_string(line,'\t',&fields);
			if (fields.size() != 2)
			    continue;

			int f_vertex_id = atoi(fields[0].c_str());
			int t_vertex_id = atoi(fields[1].c_str());
			addEdge(f_vertex_id, t_vertex_id);
		}

	    fin.close();
	    return true;
	}

	bool Graph::readBinaryGraph(const char * filepath)
	{
	    return true;
	}

	void Graph::printGraphMsg() const
	{
	    fprintf(stderr,"[Info][Total Node Num: %u]\n", (uint32_t)vertex_map_.size());
		fprintf(stderr,"[Info][Total Edge Num: %u]\n", edge_num_);

		IdToVertexMap::const_iterator itr;
		for(itr=vertex_map_.begin();itr!=vertex_map_.end();itr++)
		{
			BaseVertex * v = itr->second;
			v->printVertexMsg();
			/*
			EdgeSet::iterator eitr;
			v->printVertexMsg();
			for(eitr=(v->adj_edges_).begin();eitr!=(v->adj_edges_).end();eitr++)
			{
				(*eitr)->printEdgeMsg();
			}
			*/
		}
		printf("Read Graph Done\n");
	}
}
