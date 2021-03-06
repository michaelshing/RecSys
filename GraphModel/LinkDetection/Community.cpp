#include "Community.h"
#include <iostream>

namespace CommunityDetection
{
    Community::Community(Graph * graph, Vertex * vertex, uint32_t id)
    {
        graph_ = graph;
        nodes_.insert(vertex);
        community_id_ = id;
        in_degree_ = 0;
        total_degree_ = vertex->getDegree();
    }

    Community::~Community() {}

    uint32_t Community::getInLinkNum(const Vertex * vertex) const
    {
        uint32_t count = 0;
        VertexSet::const_iterator itr = nodes_.begin();
        while (itr != nodes_.end())
        {
            if (vertex->isAdjVertex(*itr))
                count ++;
            itr ++;
        }

        return count;
    }

    uint32_t Community::getOutDegree() const
    {
        return total_degree_ - in_degree_;
    }

    bool Community::insertVertex(Vertex * vertex)
    {
        if(nodes_.find(vertex) == nodes_.end())
        {
            uint32_t in_links = getInLinkNum(vertex);
            in_degree_ += 2 * in_links;
            total_degree_ += vertex->getDegree();
            nodes_.insert(vertex);
            return true;
        }
        else
        {
            //fprintf(stderr, "Node[id: %u] is Exist in the Community]\n",vertex->vid_);
            return false;
        }
    }

    bool Community::removeVertex(Vertex * vertex)
    {
        if (nodes_.find(vertex) != nodes_.end())
        {
            uint32_t in_links = getInLinkNum(vertex);
            in_degree_ -= 2 * in_links;
            total_degree_ -= vertex->getDegree();

            if (in_degree_ < 0)
            {
                fprintf(stderr, "[Error][in_degree_ < 0]\n");
                return false;
            }

            if (total_degree_ < 0)
            {
                fprintf(stderr, "[Error][total_degree_ < 0]\n");
                return false;
            }

            nodes_.erase(vertex);
            return true;
        }
        else
        {
            //fprintf(stderr, "[Error][Vertex[id: %u] is not Exist in th Community]\n",vertex->vid_);
            return false;
        }
    }
 
    void Community::printCommunityMsg() const
    {
        printf("Community vertexs\n");
        VertexSet::const_iterator itr;
        for (itr=nodes_.begin();itr!=nodes_.end();itr++)
        {	
            Vertex * v = *itr;
            std::cout << v->vid_ << "\t";
        }
        std::cout << "\n";
    }
}
