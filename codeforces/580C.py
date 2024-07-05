from collections import defaultdict, deque

def count_paths_with_cats(n, k, v, edges):
    # Build adjacency list
    adj = defaultdict(list)
    for a, b in edges:
        adj[a].append(b)
        adj[b].append(a)
    
    # Initialize BFS
    visited = [False] * n
    q = deque([(0, v[0], v[0])])  # (current node, current consecutive cats, max consecutive cats)
    visited[0] = True
    count = 0
    
    while q:
        node, curr_cats, max_cats = q.popleft()
        
        # Check if it's a leaf node
        is_leaf = True
        for neighbor in adj[node]:
            if not visited[neighbor]:
                is_leaf = False
                new_cats = curr_cats + v[neighbor] if v[neighbor] == 1 else 0
                if new_cats <= k:
                    q.append((neighbor, new_cats, max(new_cats, max_cats)))
                    visited[neighbor] = True
        
        if is_leaf and max_cats <= k:
            count += 1
    
    return count

# Read inputs
n, k = map(int, input().split())
v = list(map(int, input().split()))
edges = [tuple(map(int, input().split())) for _ in range(n - 1)]

# Adjust edge indices to be 0-based
edges = [(a - 1, b - 1) for a, b in edges]

# Calculate the result
result = count_paths_with_cats(n, k, v, edges)
print(result)
