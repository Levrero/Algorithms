#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <time.h>

// input data reading function
std::vector<std::vector<int>> read_input(const std::string &file_name)
{
    std::fstream input_file(file_name, std::ios_base::in);

    std::vector<std::vector<int>> input_data;

    // read one line at a time into the variable line
    std::string line;
    while (std::getline(input_file, line))
    {
        std::vector<int> node_connectivity;
        std::stringstream line_stream(line);

        // read an integer at a time from the line
        int node;
        while (line_stream >> node)
        {
            node_connectivity.push_back(node);
        }

        input_data.push_back(node_connectivity);
    }

    // expand the list to a list of edges
    std::vector<std::vector<int>> edge_list = {};
    int ii = 0;
    for (int jj = 0; jj < input_data.size(); ++jj)
    {
        for (int kk = 1; kk < input_data[jj].size(); ++kk)
        {
            edge_list.push_back({});
            if (jj < input_data[jj][kk] - 1)
            {
                edge_list[ii] = {jj, input_data[jj][kk] - 1};
            }
            else
            {
                edge_list[ii] = {input_data[jj][kk] - 1, jj};
            }
            
            ++ii;
        }
    }

    return edge_list;
}

// choose pivot function (uniform randomly)
int choose_edge(int n)
{
    return rand() % n;
}

void remove_self_loops(std::vector<std::vector<int>> &input_graph,
    const std::vector<std::vector<int>> &vertex_list)
{
    int ii = 0;
    while (ii < input_graph.size())
    {
        bool flag = true;

        for (int jj = 0; jj < vertex_list.size(); ++jj)
        {
            if (std::find(vertex_list[jj].begin(), vertex_list[jj].end(), input_graph[ii][0]) != vertex_list[jj].end() &&
                std::find(vertex_list[jj].begin(), vertex_list[jj].end(), input_graph[ii][1]) != vertex_list[jj].end())
            {
                input_graph.erase(input_graph.begin() + ii);
                flag = false;
            }
        }

        if (flag)
        {
            ++ii;
        }
    }
}

// randomized graph contraction
std::vector<std::vector<int>> randomized_graph_contraction(std::vector<std::vector<int>> input_graph)
{
    int n = input_graph.size();

    // initialize the vertex list
    int abs_max = 0;
    for (int ii = 0; ii < n; ++ii)
    {
        int max = *std::max_element(input_graph[ii].begin(), input_graph[ii].end()) + 1;
        if (max > abs_max)
        {
            abs_max = max;
        }
    }

    std::vector<std::vector<int>> vertex_list(abs_max);
    for (int ii = 0; ii < abs_max; ++ii)
    {
        vertex_list[ii].push_back(ii);
    }

    int vertex_size = vertex_list.size();
    while (vertex_size > 2)
    {
        // choose edge at random
        int edge = choose_edge(input_graph.size());

        // set source node
        int destination_node = input_graph[edge][0];
        int source_node = input_graph[edge][1];

        // merge nodes in the selected edge
        int destination_node_pos = vertex_list[destination_node][0];
        int source_node_pos = vertex_list[source_node][0];
        int vertex_row = vertex_list[source_node_pos].size();
        for (int ii = 0; ii < vertex_row; ++ii)
        {
            vertex_list[destination_node_pos].push_back(vertex_list[source_node_pos][ii]);
            vertex_list[vertex_list[source_node_pos][ii]].clear();
            vertex_list[vertex_list[source_node_pos][ii]].push_back(destination_node_pos);
        }

        // update edge list
        input_graph.erase(input_graph.begin() + edge);
            
        // remove self-loops
        remove_self_loops(input_graph, vertex_list);

        // update vertex count
        --vertex_size;
    }    

    // check for redundant edges
    auto end = input_graph.end();
    for (auto it = input_graph.begin(); it < end; ++it)
    {
        end = std::remove(it + 1, end, *it);
    }

    input_graph.erase(end, input_graph.end());

    return input_graph;
}

// main function
int main()
{
    // initiate random engine
    srand(time(0));

    // read vector from file
    std::string file_name = "input_8_1.txt";
    std::vector<std::vector<int>> edge_list = read_input(file_name);

    int num_tests = 1000;
    std::vector<int> min_cut_sizes_list = {};
    std::vector<std::vector<std::vector<int>>> min_cuts_list = {};
    for (int itest = 0; itest < num_tests; ++itest)
    {
        // obtain a minimum cut of the input graph
        std::vector<std::vector<int>> min_cut = randomized_graph_contraction(edge_list);
        min_cuts_list.push_back(min_cut);
        min_cut_sizes_list.push_back(min_cut.size());

        // output minimum cut
        std::cout << "Minimum cut number " << itest << " is " << min_cut.size() << std::endl;
        std::cout << std::endl;
    }

    std::cout << "The minimum number of cuts in all runs is " << *std::min_element(min_cut_sizes_list.begin(),
        min_cut_sizes_list.end()) << std::endl;

    return 0;
}