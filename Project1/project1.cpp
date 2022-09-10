#include <iostream>
#include <string>
using namespace std;

// Khoi Trinh
// DSA 5005
// Project 1
// 09.09.2022

class Node {
protected:
	int nodeNumber; // field to store node's number
	string nodeInfo; // field to store node's information
public:
	Node(); // default constructor
	// getters
	string getNodeInfo();
	int getNodeNumber();
	// setters
	void setNodeInfo(string newInfo);
	void setNodeNumber(int newNum);
	void display(); // display node details 
};
Node::Node() {
	// Initialize everything to default values
	nodeNumber = -1;
	nodeInfo = "";
} // default constructor
// getters
string Node::getNodeInfo() {
	return nodeInfo;
}
int Node::getNodeNumber() {
	return nodeNumber;
}
// setters
void Node::setNodeInfo(string newInfo) {
	nodeInfo = newInfo;
}
void Node::setNodeNumber(int newNum) {
	nodeNumber = newNum;
}
void Node::display() {
	cout << nodeNumber << ": " << nodeInfo << endl;
} // display node details 

// class to store one edge's details
class Edge {
protected:
	Node* u; // field to store source node pointer
	Node* v; // field to store destination node pointer
	string edgeInfo; // field to store edge information
public:
	Edge(); // default constructor
	// getters 
	Node& getu();
	Node& getv();
	string getEdgeInfo();
	// setters
	void setu(Node* newu);
	void setv(Node* newv);
	void setEdgeInfo(string newInfo);
	void display(); // display edge details
};

// Maybe need to add a non-default constructor?

Edge::Edge() {
	// Initialize everything to default value
	u = NULL;
	v = NULL;
	edgeInfo = "";
}
Node& Edge::getu() {
	// Return the pointer to node U
	return *u;
}
Node& Edge::getv() {
	// Return the pointer to node V
	return *v;
}
string Edge::getEdgeInfo() {
	// Return the string that stores the information
	return edgeInfo;
}
void Edge::setu(Node* newu) {
	u = newu;
}
void Edge::setv(Node* newv) {
	v = newv;
}
void Edge::setEdgeInfo(string newInfo) {
	edgeInfo = newInfo;
}
void Edge::display() {
	string nodeUInfo = u->getNodeInfo();
	string nodeVInfo = v->getNodeInfo();
	string displayEdgeInfo = getEdgeInfo();
	cout << nodeUInfo << " - " << nodeVInfo << " " << displayEdgeInfo << endl;
}

// class to store the graph database
class GraphDB {
protected:
	Node* myNodes; // array of nodes 
	Edge* myEdges; // array of edges
	int numNodes; // number of nodes
	int numEdges; // current number of edges
	int maxEdges; // store the max number of edges (array size)
public:
	GraphDB(int nNodes, int mEdges); // non-default constructor
	//setters
	void setNode(Node& newNode);
	void setEdge(Edge& newEdge);
	void setNodeInfo(int u, string newInfo);
	void setEdgeInfo(int u, int v, string newInfo);
	// getters
	Node* getNode(int nodeNum);
	string getNodeInfo(int nodeNum);
	Edge* getEdgeInfo(int u, int v);
	// operations
	bool isAnEdge(int u, int v); // is this edge existent
	bool edgeChecker(int u, int v);
	void addEdge(Edge& newEdge); // add an edge
	void deleteEdge(int u, int v); // delete/remove the edge
	void display(); // Display the database
};

GraphDB::GraphDB(int nNodes, int mEdges) {
	// Initialize all the fields appropriately
	numNodes = nNodes;
	maxEdges = mEdges;
	numEdges = 0;
	myNodes = new Node[numNodes];
	myEdges = new Edge[maxEdges];
}
void GraphDB::setNode(Node& newNode) {
	int newNodeNum = newNode.getNodeNumber();
	string newNodeInfo = newNode.getNodeInfo();
	// Now I need to set this into the myNodes array
	myNodes[newNodeNum].setNodeNumber(newNodeNum);
	myNodes[newNodeNum].setNodeInfo(newNodeInfo);
}
void GraphDB::setEdge(Edge& newEdge) {
	// Extract the string information from newEdge
	string newEdgeInfo = newEdge.getEdgeInfo();
	// Set the information to the "last box" of
	// myEdges array
	myEdges[numEdges-1].setu(&newEdge.getu());
	myEdges[numEdges-1].setv(&newEdge.getv());
	myEdges[numEdges-1].setEdgeInfo(newEdgeInfo);
}
void GraphDB::setNodeInfo(int u, string newInfo) {
	// Set the nodeInfo at node U to newInfo
	myNodes[u].setNodeInfo(newInfo);
}
void GraphDB::setEdgeInfo(int u, int v, string newInfo) {
	// Find the edge that connects u and v
	// use setEdgeInfo(newInfo)
	// Loop through the myEdges array
	for (int i = 0; i < numEdges; ++i) {
		// Create 2 nodes to store u and v
		Node nodeU = myEdges[i].getu();
		Node nodeV = myEdges[i].getv();
		// If the u and v matches tempU and tempV, then set the newInfo into that edge
		// and break the loop
		if (nodeU.getNodeNumber() == u && nodeV.getNodeNumber() == v) {
			myEdges[i].setEdgeInfo(newInfo);
			break;
		}
	}
}
Node* GraphDB::getNode(int nodeNum) {
	return &myNodes[nodeNum];
}
string GraphDB::getNodeInfo(int nodeNum) {
	return myNodes[nodeNum].getNodeInfo();
}
Edge* GraphDB::getEdgeInfo(int u, int v) {
	// You have to find the edge that connects the node numbers u and v 
	// given here as arguments in the myEdges array 
	// and then return that pointer from the myEdges array.
	
	for (int i = 0; i < numEdges; ++i) {
		Edge thisEdge = myEdges[i];
		Node nodeU = myEdges[i].getu();
		Node nodeV = myEdges[i].getv();
		if (nodeU.getNodeNumber() == u && nodeV.getNodeNumber() == v) {
			// return would also break the loop
			return &thisEdge;
		}
	}
}
bool GraphDB::edgeChecker(int u, int v) {
	bool isEdge = false;
	for (int i = 0; i < numEdges; ++i) {
		Edge thisEdge = myEdges[i];
		Node nodeU = myEdges[i].getu();
		Node nodeV = myEdges[i].getv();
		// Find the edge
		if (nodeU.getNodeNumber() == u && nodeV.getNodeNumber() == v) {
			isEdge = true;
			return isEdge;
		}
		else {
			// Keep looping until you find the edge
			continue;
		}
	}
	return isEdge;
}
bool GraphDB::isAnEdge(int u, int v) {
	bool isEdge = edgeChecker(u, v);
	if (isEdge == true) {
		cout << "Edge exists between " << myNodes[u].getNodeInfo() << " and " << myNodes[v].getNodeInfo() << endl;
	}
	else {
		cout << "No edge exists between " << myNodes[u].getNodeInfo() << " and " << myNodes[v].getNodeInfo() << endl;
	}
	return isEdge;
}
void GraphDB::addEdge(Edge& newEdge) { // Similar to setEdge
	// Currently, if statement not being executed
	//cout << numEdges << maxEdges << endl;
	numEdges = numEdges + 1;
	if (numEdges < maxEdges) {
		setEdge(newEdge);
	}
	else {
		// Increase by 1 every time
		int difference = 1;
		// Update maxEdges to a larger number
		maxEdges = maxEdges + difference;
		// Expand array
		Edge* tempEdge = new Edge[maxEdges];
		for (int i = 0; i < numEdges; ++i) {
			// Fill up the temp array
			tempEdge[i] = myEdges[i];
		}
		// Delete old myEdges array
		delete[] myEdges;
		// Point new myEdges array to temp array
		myEdges = tempEdge;		
		// Set the edge
		setEdge(newEdge);
	}
}
void GraphDB::deleteEdge(int u, int v) {
	bool isEdge = edgeChecker(u, v);
	if (isEdge == true) {
		// If edge exists, delete it
		cout << "Removing " << u << " " << v << endl;
		// Create a temp array with the size of maxEdges
		Edge* tempEdge = new Edge[maxEdges];
		for (int i = 0; i < numEdges; ++i) {
			Edge thisEdge = myEdges[i];
			Node nodeU = myEdges[i].getu();
			Node nodeV = myEdges[i].getv();
			// Find the edge to be remove
			if (nodeU.getNodeNumber() == u && nodeV.getNodeNumber() == v) {
				// Fill first part of temp, skip i
				for (int j = 0; j < i; ++j) {
					//cout << "Filling first half" << endl;
					tempEdge[j] = myEdges[j];
				}
				// Fill the rest of temp
				for (int j = i + 1; j < numEdges; ++j) {
					// Need j - 1 for tempEdge otherwise the 
					// new array will have an empty spot
					tempEdge[j - 1] = myEdges[j];
				}
				break;
			}
		}
		// Decrease numEdges by 1
		numEdges = numEdges - 1;
		// Delete old array
		delete[] myEdges;
		// Assign new array pointer 
		myEdges = tempEdge;
	}
	else {
		// If edge does not exist, print a statement
		cout << "Removing " << u << " " << v << " but this edge does not exist." << endl;
	}
}

void GraphDB::display() {
	cout << "Displaying myNodes: " << endl;
	for (int i = 0; i < numNodes; i++) {
		myNodes[i].display();
	}
	cout << "Displaying myEdges: " << endl;
	for (int i = 0; i < numEdges; i++) {
		myEdges[i].display();
	}

}

// Main function, where the program is run
int main() {
	int numNodes;
	int maxEdges;
	int nodeNum;
	char command;
	int u, v;
	
	string nodeLabel;

	cin >> numNodes;
	cin >> maxEdges;

	cout << "numNodes: " << numNodes << endl;
	cout << "maxEdges: " << maxEdges << endl;

	GraphDB* masterGraph;
	// this will initialize the myNodes and myEdges array in the GraphDB class
	masterGraph = new GraphDB(numNodes, maxEdges); 
	
	// Add the nodes to the myNodes array
	for (int i = 0; i < numNodes; i++) {
		cin >> nodeNum >> nodeLabel;
		Node* addNode = new Node();
		addNode->setNodeNumber(nodeNum);
		addNode->setNodeInfo(nodeLabel);
		masterGraph->setNode(*addNode);
	}

	// Read in the rest of the input
	// Use switch cases to determine which action to take
	// Case I, Case E, Case R, Case D
	cin >> command;
	while (!cin.eof()) {
		switch (command) {
			case 'I':{
				cin >> u >> v >> nodeLabel; // Keep all cin in the main class
				Edge* newEdge = new Edge();
				Node *nodeU = masterGraph->getNode(u);
				Node *nodeV = masterGraph->getNode(v);
				newEdge->setu(nodeU);
				newEdge->setv(nodeV);
				newEdge->setEdgeInfo(nodeLabel);
				cout << "Inserting " << u << " " << v << ": " << nodeLabel << endl;
				masterGraph->addEdge(*newEdge);
				break;
			}
			case 'E': {
				// check if there is an edge between 2 nodes
				cin >> u >> v;
				masterGraph->isAnEdge(u, v);
				break;
			}
			case 'R': {
				// delete edge
				cin >> u >> v;
				masterGraph->deleteEdge(u, v);
				break;
			}
			case 'D': {
				// display the current result
				// Display myNodes and myEdges
				masterGraph->display();
				break;
			}
			default: cout << "Holy cow!!" << endl;
		}
		cin >> command;
	}

	return 0;
}