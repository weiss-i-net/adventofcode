struct point {
  int x, y;
  point& operator+= (const point & rhs) { x += rhs.x; y += rhs.y; return *this; }
};
point operator+ (const point & lhs, const point & rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y}; }
point operator- (const point & lhs, const point & rhs) { return {lhs.x - rhs.x, lhs.y - rhs.y}; }
bool operator== (const point & lhs, const point & rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
bool operator!= (const point & lhs, const point & rhs) { return !(lhs == rhs); }
bool operator< (const point & lhs, const point & rhs) { if (lhs.x == rhs.x) return lhs.y < rhs.y; else return lhs.x < rhs.x; }
bool operator>= (const point & lhs, const point & rhs) { return !(lhs < rhs); }
bool operator> (const point & lhs, const point & rhs) { if (lhs.x == rhs.x) return lhs.y > rhs.y; else return lhs.x > rhs.x; }
bool operator<= (const point & lhs, const point & rhs) { return !(lhs > rhs); }
