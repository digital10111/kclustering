#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <iostream>
#include <fstream>
#include <set>
#include <boost/foreach.hpp>


class Edge {

    public:

        int src;
        int dest;
        int cost;

        void set_src(int src) {
            this -> src = src;
        }

        void set_dest(int dest) {
            this -> dest = dest;
        }

        void set_cost(int cost) {
            this -> cost = cost;
        }

        bool operator == (const Edge& edge) const { return cost == edge.cost && dest == edge.dest && src == edge.src; }
        bool operator < (const Edge& edge) const { return cost < edge.cost; }
};


int find(std::vector<int> parent, int i) {
    if (parent[i - 1] == -1) {
        return i;
    }
    return find(parent, parent[i-1]);
}


bool Union(std::vector<int>& parent, int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    if (xset != yset) {
        parent[xset - 1] = yset;
        return true;
    }
    return false;
}


void sort_by_cost(std::vector<std::vector<int>>& vec){

    std::sort(
        vec.begin(),
        vec.end(),
        [](
            const std::vector<int> a,
            const std::vector<int> b
            ) {
                return a[2] < b[2];
                }
    );

}


void sort_edges_by_cost(std::vector<Edge>& edges){

    std::sort(
        edges.begin(),
        edges.end(),
        [](
            const Edge& a,
            const Edge& b
            ) {
                return a.cost < b.cost;
                }
    );

}


BOOST_PYTHON_MODULE(unionfind)
{
    using namespace boost::python;

    def("sort_by_cost", sort_by_cost);
    def("sort_edges_by_cost", sort_edges_by_cost);

    class_<std::vector<int> >("XVec")
    .def(vector_indexing_suite<std::vector<int> >());


    class_<std::vector<std::vector<int>> >("XVecVec")
    .def(vector_indexing_suite<std::vector<std::vector<int>> >());


    class_<Edge>("Edge")
        .def("set_src", &Edge::set_src)
	    .def("set_dest", &Edge::set_dest)
	    .def("set_cost", &Edge::set_cost)
	    .def_readonly("cost", &Edge::cost)
	    .def_readonly("src", &Edge::src)
	    .def_readonly("dest", &Edge::dest);


    class_<std::vector<Edge> >("EdgeVec")
        .def(vector_indexing_suite<std::vector<Edge> >());

    def("union", Union);
}
