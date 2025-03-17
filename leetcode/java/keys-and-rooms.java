import java.util.*;
class Solution {
    public boolean canVisitAllRooms(List<List<Integer>> rooms) {
        Set<Integer> visited = new HashSet<>();
        dfs(rooms, visited, 0);
        return visited.size() == rooms.size();
    }
    private void dfs(List<List<Integer>> rooms, Set<Integer> visited, int room) {
        visited.add(room);
        for (int key : rooms.get(room)) {
            if (!visited.contains(key)) {
                dfs(rooms, visited, key);
            }
        }
    }
}