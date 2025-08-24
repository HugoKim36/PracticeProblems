class Solution:
    def minRefuelStops(self, target: int, startFuel: int, stations: List[List[int]]) -> int:
        min_stops = 0
        max_pq = []
        curr_pos = 0
        curr_fuel = startFuel
        for pos, fuel in stations:
            if (target - curr_pos) <= (curr_fuel):
                return min_stops
            while curr_fuel < (pos - curr_pos) and max_pq:
                curr_fuel -= heapq.heappop(max_pq)
                min_stops += 1
            if curr_fuel < (pos - curr_pos): 
                return -1
            curr_fuel -= (pos - curr_pos)
            curr_pos = pos
            heapq.heappush(max_pq, -fuel)

        while curr_fuel < (target - curr_pos) and max_pq:
            curr_fuel -= heapq.heappop(max_pq)
            min_stops += 1
        if (target - curr_pos) > curr_fuel:
            min_stops = -1
        return min_stops
