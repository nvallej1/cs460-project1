# Compiling

Type 'make' in bash terminal.

-------------------------------------
## Running

Type './a.out' in bash terminal.

-------------------------------------
## Design

#### How control points (vertex) are created:

- Each vertex is represented as a std::pair<float,float>
```
std::pair<float, float> vertex1 (5,10);
// or
std::pair<float, float> vertex1 = std::make_pair<float, float> (5,10);
```
- The x-coordinate and y-coordinate of a vertex is stored in the instance variables 'first' and 'second'
```
std::pair<float,float> vertex (5,10);
float x = vertex.first;  // x-coordinate 5
float y = vertex.second; // y-coordinate 10
```

#### How control points (vertex) are stored:
- Vertexes are stored in a std::vector:
```
// In global space
std::vector< std::pair <float, float> > controlPoints;
...
void mouseFunc(int button, int state, int x, int y) {
	...
	controlPoints.push_back(std::make_pair<float, float> (x, y)); // store control point (x,y)
	...
}
```

#### Important notes on mouse click events:
- left-click event creates a control point which is then stored at the end of the 'controlPoints' vector
- right-click event creates the final control point which is then stored at the end of the 'controlPoints' vector
- right-click event also creates and stores an additional vertex - called the 'dummyVertex' which has coordinates (-1,-1) - at the end of the 'controlPoints' vector

#### Purpose of the 'dummyVertex':
- A 'dummyVertex' stored in the 'controlPoints' vector represents the end of a line and the beginning of a new line   
