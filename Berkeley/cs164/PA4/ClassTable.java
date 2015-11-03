/*
Copyright (c) 2000 The Regents of the University of California.
All rights reserved.

Permission to use, copy, modify, and distribute this software for any
purpose, without fee, and without written agreement is hereby granted,
provided that the above copyright notice and the following two
paragraphs appear in all copies of this software.

IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF
CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*/

// This is a project skeleton file

import java.io.PrintStream;
import java.util.*;

/** This class may be used to contain the semantic information such as
 * the inheritance graph.  You may use it or not as you like: it is only
 * here to provide a container for the supplied methods.  */
class ClassTable {
    private int semantErrors;
    private PrintStream errorStream;
    private Graph<String> class_graph;

    /** Creates data structures representing basic Cool classes (Object,
     * IO, Int, Bool, String).  Please note: as is this method does not
     * do anything useful; you will need to edit it to make if do what
     * you want.
     * */
    private void installBasicClasses() {
	AbstractSymbol filename 
	    = AbstractTable.stringtable.addString("<basic class>");
	
	// The following demonstrates how to create dummy parse trees to
	// refer to basic Cool classes.  There's no need for method
	// bodies -- these are already built into the runtime system.

	// IMPORTANT: The results of the following expressions are
	// stored in local variables.  You will want to do something
	// with those variables at the end of this method to make this
	// code meaningful.

	// The Object class has no parent class. Its methods are
	//        cool_abort() : Object    aborts the program
	//        type_name() : Str        returns a string representation 
	//                                 of class name
	//        copy() : SELF_TYPE       returns a copy of the object

	class_c Object_class = 
	    new class_c(0, 
		       TreeConstants.Object_, 
		       TreeConstants.No_class,
		       new Features(0)
			   .appendElement(new method(0, 
					      TreeConstants.cool_abort, 
					      new Formals(0), 
					      TreeConstants.Object_, 
					      new no_expr(0)))
			   .appendElement(new method(0,
					      TreeConstants.type_name,
					      new Formals(0),
					      TreeConstants.Str,
					      new no_expr(0)))
			   .appendElement(new method(0,
					      TreeConstants.copy,
					      new Formals(0),
					      TreeConstants.SELF_TYPE,
					      new no_expr(0))),
		       filename);
	
	// The IO class inherits from Object. Its methods are
	//        out_string(Str) : SELF_TYPE  writes a string to the output
	//        out_int(Int) : SELF_TYPE      "    an int    "  "     "
	//        in_string() : Str            reads a string from the input
	//        in_int() : Int                "   an int     "  "     "

	class_c IO_class = 
	    new class_c(0,
		       TreeConstants.IO,
		       TreeConstants.Object_,
		       new Features(0)
			   .appendElement(new method(0,
					      TreeConstants.out_string,
					      new Formals(0)
						  .appendElement(new formalc(0,
								     TreeConstants.arg,
								     TreeConstants.Str)),
					      TreeConstants.SELF_TYPE,
					      new no_expr(0)))
			   .appendElement(new method(0,
					      TreeConstants.out_int,
					      new Formals(0)
						  .appendElement(new formalc(0,
								     TreeConstants.arg,
								     TreeConstants.Int)),
					      TreeConstants.SELF_TYPE,
					      new no_expr(0)))
			   .appendElement(new method(0,
					      TreeConstants.in_string,
					      new Formals(0),
					      TreeConstants.Str,
					      new no_expr(0)))
			   .appendElement(new method(0,
					      TreeConstants.in_int,
					      new Formals(0),
					      TreeConstants.Int,
					      new no_expr(0))),
		       filename);

	// The Int class has no methods and only a single attribute, the
	// "val" for the integer.

	class_c Int_class = 
	    new class_c(0,
		       TreeConstants.Int,
		       TreeConstants.Object_,
		       new Features(0)
			   .appendElement(new attr(0,
					    TreeConstants.val,
					    TreeConstants.prim_slot,
					    new no_expr(0))),
		       filename);

	// Bool also has only the "val" slot.
	class_c Bool_class = 
	    new class_c(0,
		       TreeConstants.Bool,
		       TreeConstants.Object_,
		       new Features(0)
			   .appendElement(new attr(0,
					    TreeConstants.val,
					    TreeConstants.prim_slot,
					    new no_expr(0))),
		       filename);

	// The class Str has a number of slots and operations:
	//       val                              the length of the string
	//       str_field                        the string itself
	//       length() : Int                   returns length of the string
	//       concat(arg: Str) : Str           performs string concatenation
	//       substr(arg: Int, arg2: Int): Str substring selection

	class_c Str_class =
	    new class_c(0,
		       TreeConstants.Str,
		       TreeConstants.Object_,
		       new Features(0)
			   .appendElement(new attr(0,
					    TreeConstants.val,
					    TreeConstants.Int,
					    new no_expr(0)))
			   .appendElement(new attr(0,
					    TreeConstants.str_field,
					    TreeConstants.prim_slot,
					    new no_expr(0)))
			   .appendElement(new method(0,
					      TreeConstants.length,
					      new Formals(0),
					      TreeConstants.Int,
					      new no_expr(0)))
			   .appendElement(new method(0,
					      TreeConstants.concat,
					      new Formals(0)
						  .appendElement(new formalc(0,
								     TreeConstants.arg, 
								     TreeConstants.Str)),
					      TreeConstants.Str,
					      new no_expr(0)))
			   .appendElement(new method(0,
					      TreeConstants.substr,
					      new Formals(0)
						  .appendElement(new formalc(0,
								     TreeConstants.arg,
								     TreeConstants.Int))
						  .appendElement(new formalc(0,
								     TreeConstants.arg2,
								     TreeConstants.Int)),
					      TreeConstants.Str,
					      new no_expr(0))),
		       filename);

	/* Do somethind with Object_class, IO_class, Int_class,
           Bool_class, and Str_class here */
	class_graph = new Graph<String>(Object_class.getName().toString(),
					IO_class.getName().toString(),
					Int_class.getName().toString(),
					Bool_class.getName().toString(),
					Str_class.getName().toString());

	class_graph.addEdge(IO_class.getName().toString(), Object_class.getName().toString());
	class_graph.addEdge(Int_class.getName().toString(), Object_class.getName().toString());
	class_graph.addEdge(Bool_class.getName().toString(), Object_class.getName().toString());
	class_graph.addEdge(Str_class.getName().toString(), Object_class.getName().toString());
	
	class_lookup.put("Object", Object_class);
	class_lookup.put("IO", IO_class);
	class_lookup.put("Int", Int_class);
	class_lookup.put("Bool", Bool_class);
	class_lookup.put("String", Str_class);
	class_lookup.put("SELF_TYPE", null); //Yikes...

	basicClasses = new Classes(0)
	    .appendElement(Object_class)
	    .appendElement(IO_class)
	    .appendElement(Int_class)
	    .appendElement(Bool_class)
	    .appendElement(Str_class);

    }

    HashMap<String, HashSet<Feature>> class_features;
    HashMap<String, class_c> class_lookup;
    ArrayList<String> topographicalSort;

    public HashSet<Feature> getClassFeatures(String class_name) {
	return class_features.get(class_name);
    }
    
    Classes basicClasses;
    public Classes basicClasses() {
	return basicClasses;
    }

    public boolean containsClass(String class_name) {
	return class_lookup.containsKey(class_name);
    }

    public class_c getClass_c(String class_name) {
	return class_lookup.get(class_name);
    }

    public ArrayList<String> classes() {
	return topographicalSort;
    }

    public ClassTable(Classes cls) {
	class_lookup = new HashMap<String, class_c>();
	installBasicClasses();
	errorStream = System.err;
	semantErrors = 0;
	boolean error = false;
	for(int i = 0; i < cls.getLength(); i++) {
	    class_c next = (class_c)(cls.getNth(i));
	    String className = next.getName().toString();
	    class_lookup.put(className, next);
	    try {
		if(className.toString().equals(TreeConstants.SELF_TYPE.toString()))
		    throw new Exception();
		class_graph.addNode(className);
		class_graph.addEdge(className,
				    next.getParent().toString());
		if(next.getParent().equals(TreeConstants.SELF_TYPE) ||
		   next.getParent().equals(TreeConstants.Bool) || 
		   next.getParent().equals(TreeConstants.Int) || 
		   next.getParent().equals(TreeConstants.Str)) {
		    error = true;
		    semantError(next).printf("Class %s cannot inherit class %s.\n",
					     className,
					     next.getParent());
		}
	    } catch (Exception e) {
		semantError(next).printf("Class %s was previously defined.\n", className);
		error = true;
	    }
	}
	topographicalSort = class_graph.topographicalSort();
	if(error || topographicalSort == null) { 
	    if(!error)
		semantError().println("Ill-formed class hierarchy in program.");
	    System.err.println("Compilation halted due to static semantic errors.");
	    System.exit(1);
	} else {
	    class_features = new HashMap<String, HashSet<Feature>>();
	    
	    /*
	     * Copy all features to our map
	     */
	    for(String class_name : topographicalSort) {
		class_features.put(class_name, new HashSet<Feature>());
		class_c _class = class_lookup.get(class_name);
		Features features = _class.getFeatures();
		for(int i = 0; i < features.getLength(); i++) {
		    Feature next = (Feature)features.getNth(i);
		    class_features.get(class_name).add(next);
		}
	    }
	}
    }

    /** Prints line number and file name of the given class.
     *
     * Also increments semantic error count.
     *
     * @param c the class
     * @return a print stream to which the rest of the error message is
     * to be printed.
     *
     * */
    public PrintStream semantError(class_c c) {
	return semantError(c.getFilename(), c);
    }

    /** Prints the file name and the line number of the given tree node.
     *
     * Also increments semantic error count.
     *
     * @param filename the file name
     * @param t the tree node
     * @return a print stream to which the rest of the error message is
     * to be printed.
     *
     * */
    public PrintStream semantError(AbstractSymbol filename, TreeNode t) {
	errorStream.print(filename + ":" + t.getLineNumber() + ": ");
	return semantError();
    }
    

    public boolean isLEQ(AbstractSymbol child, AbstractSymbol ancestor) {
	if(child.equals(TreeConstants.No_type))
	    return true;
	class_c curr = getClass_c(child.toString());
	for(; !curr.name.equals(TreeConstants.Object_); curr = getClass_c(curr.parent.toString())) {
	    if(curr.name.equals(ancestor))
		return true;
	}
	if(curr.name.equals(ancestor))
	    return true;
	return false;
    }

    public AbstractSymbol LUB(AbstractSymbol a, AbstractSymbol b, class_c classA, class_c classB) {
	if(a == null)
	    return b;
	else if(b == null)
	    return a;
	if(a.equals(b))
	    return a;

	if(a.equals(TreeConstants.SELF_TYPE))
	    a = classA.name;
	if(b.equals(TreeConstants.SELF_TYPE))
	    b = classB.name;


	ArrayList<AbstractSymbol> aPath = new ArrayList<AbstractSymbol>();
	ArrayList<AbstractSymbol> bPath = new ArrayList<AbstractSymbol>();
	class_c curr = getClass_c(a.toString());
	for(; !curr.name.equals(TreeConstants.Object_); curr = getClass_c(curr.parent.toString())) {
	    aPath.add(curr.name);
	}
	aPath.add(curr.name);

	curr = getClass_c(b.toString());
	for(; !curr.name.equals(TreeConstants.Object_); curr = getClass_c(curr.parent.toString())) {
	    bPath.add(curr.name);	    
	}
	bPath.add(curr.name);

	int a_i = aPath.size()-1, b_i = bPath.size()-1;
	while(a_i >= 0 && b_i >= 0 && aPath.get(a_i).equals(bPath.get(b_i))) {
	    a_i--; b_i--;
	}
	return aPath.get(a_i+1);
    }

    /** Increments semantic error count and returns the print stream for
     * error messages.
     *
     * @return a print stream to which the error message is
     * to be printed.
     *
     * */
    public PrintStream semantError() {
	semantErrors++;
	return errorStream;
    }

    /** Returns true if there are any static semantic errors. */
    public boolean errors() {
	return semantErrors != 0;
    }

    // NOT TO BE INCLUDED IN SKELETON
    public static void main(String[] args) {
	new ClassTable(null).installBasicClasses();
    }
}
			  
    
