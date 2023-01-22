// This is pseudocode
fn A_Star(start: node, goal: node, h: (Fn(node) -> score)) -> Option<[node]>
    openSet := {start}
    cameFrom := empty map<node, node>
    gScore := map<node, score> with default value of Infinity
    gScore[start] := 0
    fScore := map<node, score> with default value of Infinity
    fScore[start] := h(start)

    while openSet is not empty
        // This operation can occur in O(Log(N)) time if openSet is a min-heap or a priority queue
        current := the node in openSet having the lowest fScore[] value
        if current = goal
            return reconstruct_path(cameFrom, current)

        openSet.Remove(current)
        for each neighbor of current
            tentative_gScore := gScore[current] + d(current, neighbor)
            if tentative_gScore < gScore[neighbor]
                cameFrom[neighbor] := current
                gScore[neighbor] := tentative_gScore
                fScore[neighbor] := tentative_gScore + h(neighbor)
                if neighbor not in openSet
                    openSet.add(neighbor)
    return failure