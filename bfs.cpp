// bfs.C (Breitensuche)

#include "graph.h"
#include "queue.h"
#include<iostream>

Graph bfs(Graph const & graph, Graph::NodeId start_node)
{
      std::vector<bool> visited(graph.num_nodes(), false);
      std::vector<size_t> dist(graph.num_nodes(), 0);
      Graph bfs_tree(graph.num_nodes());
      Queue<Graph::NodeId> queue;

      queue.push_back(start_node);
      visited[start_node] = true;
      dist[start_node] = 0;

      while (not queue.is_empty())
      {
            Graph::NodeId cur_node = queue.pop_front();
            for (Graph::EdgeId i = 0; i != graph.get_node(cur_node).out_edges().size(); ++i)
            {
                  Graph::EdgeId edge = graph.get_node(cur_node).out_edges()[i];
                  Graph::NodeId head = graph.get_edge(edge).get_head();
                  if (not visited[head])
                  {
                        visited[head] = true;
                        dist[head] = dist[cur_node] + 1; 
                        bfs_tree.add_edge(cur_node, head);
                        queue.push_back(head);
                  }
            }
      }
      
	  /*
      std::cout << "The following vertices are reachable from vertex 0:\n";
	  for (Graph::NodeId i = 0; i != graph.num_nodes(); ++i) 
      {
            if (visited[i]) 
            {
                  std::cout << "Vertex " << i << " has distance " << dist[i] << ".\n";
            }
      }
	  */
      return bfs_tree;
}

void print_closed_pathway(Graph const & bfs_tree, Graph::NodeId node_id) {
	std::cout << node_id << "\n";
	std::vector<Graph::EdgeId> edges = bfs_tree.get_node(node_id).out_edges();
	if (!edges.empty()) {
		for (Graph::EdgeId i = 0; i < bfs_tree.get_node(node_id).out_edges().size(); ++i) {
			print_closed_pathway(bfs_tree, bfs_tree.get_edge(edges[i]).get_head());
			std::cout << node_id << "\n";
		}
	}
}

int main(int argc, char ** argv)
{
      if (argc > 1) 
      {
            Graph g = read_graph(argv[1]);
            Graph bfs_tree = bfs(g, 0);
			print_closed_pathway(bfs_tree, 0);
      }
      return 0;
}

