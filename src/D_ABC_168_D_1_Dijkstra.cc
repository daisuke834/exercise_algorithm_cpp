/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 168-D.
 */

#include "src/D_ABC_168_D_1_Dijkstra.h"

namespace ABC_168_D_1 {

struct Vertex {
  int32_t distance{INT32_MAX};
  bool explored{false};
  int32_t parent{-1};
  std::vector<int32_t> neighbours;
};

void CallDijkstra(std::istream &input_stream) noexcept {
  std::cin.tie(0);
  std::ios::sync_with_stdio(false);

  using DistanceIndexPair = std::pair<int32_t, int32_t>;
  std::priority_queue<DistanceIndexPair, std::vector<DistanceIndexPair>, std::greater<DistanceIndexPair>> pqueue;

  constexpr int32_t kStart = 1;
  int32_t number_of_vertices, number_of_edges;
  input_stream >> number_of_vertices >> number_of_edges;
  std::vector<Vertex> vertices(number_of_vertices + 1);

  for (int32_t i = 0; i < number_of_edges; ++i) {
    int32_t a, b;
    input_stream >> a >> b;
    vertices[b].neighbours.push_back(a);
    vertices[a].neighbours.push_back(b);
  }

  pqueue.push(DistanceIndexPair(0, kStart));
  while (pqueue.size() > 0) {
    const DistanceIndexPair p = pqueue.top();
    pqueue.pop();
    const int32_t target_distance = p.first;
    const int32_t target_index = p.second;

    Vertex &cvertex = vertices[target_index];

    cvertex.explored = true;
    for (const int32_t next_index : cvertex.neighbours) {
      if (!vertices[next_index].explored) {
        const int32_t temp_distance = (target_distance != INT32_MAX) ? target_distance + 1 : INT32_MAX;
        if (temp_distance < vertices[next_index].distance) {
          vertices[next_index].distance = temp_distance;
          vertices[next_index].parent = target_index;
          pqueue.push(DistanceIndexPair(temp_distance, next_index));
        }
      }
    }
  }
  bool found = true;
  for (int32_t i = 2; i <= number_of_vertices; ++i) {
    if (vertices[i].parent < 0) {
      found = false;
    }
  }

  if (!found) {
    std::cout << "No" << std::endl;
  } else {
    std::cout << "Yes" << std::endl;
    for (int32_t i = 2; i <= number_of_vertices; ++i) {
      std::cout << vertices[i].parent << std::endl;
    }
  }
}

}  // namespace ABC_168_D_1
