class Solution {
public:
    int max_area(vector<int>& heights) {
        stack<int> ind({0});
        int area = heights[0];
        for (int i = 1; i < heights.size(); ++i) {
            while (!ind.empty() && heights[i] < heights[ind.top()]) {
                int curr = ind.top();
                ind.pop();
                int width = ind.empty() ? i : (i - ind.top()) - 1;
                area = max(area, heights[curr] * width);
            }
            ind.push(i);
        }
        while (!ind.empty()) {
            int curr = ind.top();
            ind.pop();
            int width = ind.empty() ? heights.size() : (heights.size() - ind.top()) - 1;
            area = max(area, heights[curr] * width);
        }
        return area;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int area = 0;
        vector<int> heights(matrix[0].size());
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if (matrix[i][j] == '0') heights[j] = 0;
                else ++heights[j];
            }
            area = max(area, max_area(heights));
        }
        return area;
    }
};
