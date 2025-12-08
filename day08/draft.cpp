
int part1(const std::vector<point_t>& points) {
    int pair_number = 1000;
    std::vector<connection_t> connections {};
    for (int i = 0; i < points.size(); ++i) {
        point_t p1 = points[i];
        for (int j = i+1; j < points.size(); ++j) {
            point_t p2 = points[j];
            if (p1 == p2) {
                continue;
            }
            connections.push_back({ squared_dist(p1, p2), p1, p2 });
            std::push_heap(connections.begin(), connections.end(), comparator);
            if (connections.size() > pair_number) {
                std::pop_heap(connections.begin(), connections.end(), comparator);
                connections.pop_back();
            }
        }
    }
    /*
    for (auto x : connections) {
        auto [dist, p1, p2] = x;
        auto [x1, y1, z1] = p1;
        auto [x2, y2, z2] = p2;
        std::cout << dist << " (" << x1 << "," << y1 << "," << z1
            << ") (" << x2 << "," << y2 << "," << z2 << ")\n";
    }
    */
    graph_t graph;
    for (auto [_, p1, p2] : connections) {
        graph[p1].push_back(p2);
        graph[p2].push_back(p1);
    }
    std::vector<int> cluster_sizes;
    std::set<point_t> seen;
    for (auto [point, _] : graph) {
        int cluster_size = dfs(point, graph, seen);
        if (cluster_size == 0) {
            continue;
        }
        std::cout << cluster_size << "\n";
        cluster_sizes.push_back(cluster_size);
        std::push_heap(cluster_sizes.begin(), cluster_sizes.end(), std::greater<int> {});
        if (cluster_sizes.size() > 3) {
            std::pop_heap(cluster_sizes.begin(), cluster_sizes.end(), std::greater<int> {});
            cluster_sizes.pop_back();
        }
    }
    return std::accumulate(cluster_sizes.begin(), cluster_sizes.end(), 1, std::multiplies<int> {});
}



int part1(const std::vector<point_t>& points) {
    int pair_number = 10;
    std::vector<int> connections {};
    for (int i = 0; i < points.size(); ++i) {
        for (int j = i+1; j < points.size(); ++j) {
            auto p1 = points[i], p2 = points[j];
            connections.push_back(squared_dist(p1, p2));
            std::cout << squared_dist(p1, p2) << "\n";
            std::push_heap(connections.begin(), connections.end());
            if (connections.size() > pair_number) {
                std::pop_heap(connections.begin(), connections.end());
                connections.pop_back();
            }
        }
    }
    int lowest = 0;
    for (int i = 0; i < connections.size(); ++i) {
        lowest = connections[0];
        std::pop_heap(connections.begin(), connections.end());
        connections.pop_back();
    }
    return 0;
}
