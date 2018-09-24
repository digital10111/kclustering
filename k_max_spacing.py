import unionfind


def init():
    k = 4
    edge = unionfind.Edge()
    edge_vec = unionfind.EdgeVec()
    parent = unionfind.XVec()
    total_components = None
    with open("clustering1.txt", "r") as f:
        for i, line in enumerate(f.readlines()):
            if i == 0:
                total_components = int(line)
                continue
            splt = line.split(" ")
            edge.set_src(int(splt[0]))
            edge.set_dest(int(splt[1]))
            edge.set_cost(int(splt[2]))
            edge_vec.append(edge)
            edge = unionfind.Edge()
    unionfind.sort_edges_by_cost(edge_vec)
    for i in range(0, total_components):
        parent.append(-1)
    return edge_vec, parent, total_components, k


def get_aux_graph(edge_set, vert_set, new_edge):
    graph = unionfind.Graph()
    graph.set_e(len(edge_set.union([new_edge])))
    graph.set_v(len(vert_set.union([new_edge.src, new_edge.dest])))
    edge_vec_aux = unionfind.EdgeVec()
    for e in edge_set:
        edge_vec_aux.append(e)
    edge_vec_aux.append(new_edge)
    graph.set_edges(edge_vec_aux)
    return graph


def form_clusters():

    edge_vec, parent, total_components, k = init()
    for edge in edge_vec:
        if total_components > k:
            ret = unionfind.union(parent, edge.src, edge.dest)
        if total_components == k:
            ret = unionfind.union(parent, edge.src, edge.dest)
            if ret:
                print edge.cost
                break
        elif total_components > k:
            if ret:
                total_components -= 1


if __name__ == '__main__':
    form_clusters()
