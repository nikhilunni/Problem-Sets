import java.util.*;

public class Graph<T> {
    HashMap<T, HashSet<T>> out_edges;
    HashMap<T, HashSet<T>> in_edges;

    public Graph(T... nodes) {
	out_edges = new HashMap<T, HashSet<T>>();
	if(nodes != null) {
	    for(T node : nodes) {
		out_edges.put(node, new HashSet<T>());
	    }
	}
    }

    public HashMap<T, HashSet<T>> out_edges() {
	return out_edges;
    }

    public HashMap<T, HashSet<T>> in_edges() {
	return in_edges;
    }

    public void addNode(T node) throws Exception {
	if(out_edges.containsKey(node))
	    throw new Exception("Duplicate class names");
	out_edges.put(node, new HashSet<T>());	
    }

    public void addEdge(T from, T to) {
	out_edges.get(from).add(to);
    }
    
    private HashMap<T, HashSet<T>> getInEdges() {
	HashMap<T, HashSet<T>> out = new HashMap<T, HashSet<T>>();
	for(T node : out_edges.keySet())
	    out.put(node, new HashSet<T>());
	for(T from : out_edges.keySet()) {
	    for(T to : out_edges.get(from)) {
		if(!out.containsKey(to)) //There is a parent class that doesn't exist
		    return null;
		out.get(to).add(from);
	    }
	}
	return out;
    }

    public ArrayList<T> topographicalSort() {
	Stack<T> stack = new Stack<T>();
	
	in_edges = getInEdges();
	if(in_edges == null)
	    return null;

	ArrayList<T> noIncoming = new ArrayList<T>();
	for(T t : in_edges.keySet()) {
	    if(in_edges.get(t).isEmpty()) //No incoming edges
		noIncoming.add(t);
	}
	while(!noIncoming.isEmpty()) {
	    T next = noIncoming.remove(noIncoming.size() - 1); //Get last element
	    stack.push(next); //Add to tail of out
	    for(T _out : out_edges.get(next)) {
		in_edges.get(_out).remove(next);
		if(in_edges.get(_out).isEmpty()) //No incoming edges to out
		    noIncoming.add(_out);
	    }
	}
	for(T t : in_edges.keySet()) {
	    if(!in_edges.get(t).isEmpty())
		return null;
	}

	ArrayList<T> out = new ArrayList<T>();
	while(!stack.isEmpty())
	    out.add(stack.pop());
	in_edges = getInEdges();
	return out;
    }

    public void printGraph() {
	for(T node : out_edges.keySet()) {
	    System.out.print(node + " : [");
	    for(T out : out_edges.get(node)) {
		System.out.print(out + ", ");
	    }
	    System.out.println("]");
	}
    }
}






