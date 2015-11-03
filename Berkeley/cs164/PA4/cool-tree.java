// -*- mode: java -*- 
//
// file: cool-tree.m4
//
// This file defines the AST
//
//////////////////////////////////////////////////////////



import java.util.Enumeration;
import java.io.PrintStream;
import java.util.Vector;

import java.util.HashSet;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.Set;


/** Defines simple phylum Program */
abstract class Program extends TreeNode {
    protected Program(int lineNumber) {
        super(lineNumber);
    }
    public abstract void dump_with_types(PrintStream out, int n);
    public abstract void semant();

}


/** Defines simple phylum Class_ */
abstract class Class_ extends TreeNode {
    protected Class_(int lineNumber) {
        super(lineNumber);
    }
    public abstract void dump_with_types(PrintStream out, int n);
    public abstract AbstractSymbol getName();
    public abstract AbstractSymbol getParent();
    public abstract AbstractSymbol getFilename();
    public abstract Features getFeatures();

}


/** Defines list phylum Classes
    <p>
    See <a href="ListNode.html">ListNode</a> for full documentation. */
class Classes extends ListNode {
    public final static Class elementClass = Class_.class;
    /** Returns class of this lists's elements */
    public Class getElementClass() {
        return elementClass;
    }
    protected Classes(int lineNumber, Vector elements) {
        super(lineNumber, elements);
    }
    /** Creates an empty "Classes" list */
    public Classes(int lineNumber) {
        super(lineNumber);
    }
    /** Appends "Class_" element to this list */
    public Classes appendElement(TreeNode elem) {
        addElement(elem);
        return this;
    }
    public TreeNode copy() {
        return new Classes(lineNumber, copyElements());
    }
}


/** Defines simple phylum Feature */
abstract class Feature extends TreeNode {
    protected Feature(int lineNumber) {
        super(lineNumber);
    }
    public abstract void dump_with_types(PrintStream out, int n);
    public abstract void semant(class_c _class, SymbolTable st, ClassTable ct);
}


/** Defines list phylum Features
    <p>
    See <a href="ListNode.html">ListNode</a> for full documentation. */
class Features extends ListNode {
    public final static Class elementClass = Feature.class;
    /** Returns class of this lists's elements */
    public Class getElementClass() {
        return elementClass;
    }
    protected Features(int lineNumber, Vector elements) {
        super(lineNumber, elements);
    }
    /** Creates an empty "Features" list */
    public Features(int lineNumber) {
        super(lineNumber);
    }
    /** Appends "Feature" element to this list */
    public Features appendElement(TreeNode elem) {
        addElement(elem);
        return this;
    }
    public TreeNode copy() {
        return new Features(lineNumber, copyElements());
    }
}


/** Defines simple phylum Formal */
abstract class Formal extends TreeNode {
    protected Formal(int lineNumber) {
        super(lineNumber);
    }
    public abstract void dump_with_types(PrintStream out, int n);

}


/** Defines list phylum Formals
    <p>
    See <a href="ListNode.html">ListNode</a> for full documentation. */
class Formals extends ListNode {
    public final static Class elementClass = Formal.class;
    /** Returns class of this lists's elements */
    public Class getElementClass() {
        return elementClass;
    }
    protected Formals(int lineNumber, Vector elements) {
        super(lineNumber, elements);
    }
    /** Creates an empty "Formals" list */
    public Formals(int lineNumber) {
        super(lineNumber);
    }
    /** Appends "Formal" element to this list */
    public Formals appendElement(TreeNode elem) {
        addElement(elem);
        return this;
    }
    public TreeNode copy() {
        return new Formals(lineNumber, copyElements());
    }
}


/** Defines simple phylum Expression */
abstract class Expression extends TreeNode {
    protected Expression(int lineNumber) {
        super(lineNumber);
    }
    private AbstractSymbol type = null;                                 
    public AbstractSymbol get_type() { return type; }           
    public Expression set_type(AbstractSymbol s) { type = s; return this; } 
    public abstract void dump_with_types(PrintStream out, int n);
    public void dump_type(PrintStream out, int n) {
        if (type != null)
            { out.println(Utilities.pad(n) + ": " + type.getString()); }
        else
            { out.println(Utilities.pad(n) + ": _no_type"); }
    }
    public abstract void semant(class_c _class, SymbolTable st, ClassTable ct);

}


/** Defines list phylum Expressions
    <p>
    See <a href="ListNode.html">ListNode</a> for full documentation. */
class Expressions extends ListNode {
    public final static Class elementClass = Expression.class;
    /** Returns class of this lists's elements */
    public Class getElementClass() {
        return elementClass;
    }
    protected Expressions(int lineNumber, Vector elements) {
        super(lineNumber, elements);
    }
    /** Creates an empty "Expressions" list */
    public Expressions(int lineNumber) {
        super(lineNumber);
    }
    /** Appends "Expression" element to this list */
    public Expressions appendElement(TreeNode elem) {
        addElement(elem);
        return this;
    }
    public TreeNode copy() {
        return new Expressions(lineNumber, copyElements());
    }
}


/** Defines simple phylum Case */
abstract class Case extends TreeNode {
    protected Case(int lineNumber) {
        super(lineNumber);
    }
    public abstract void dump_with_types(PrintStream out, int n);

}


/** Defines list phylum Cases
    <p>
    See <a href="ListNode.html">ListNode</a> for full documentation. */
class Cases extends ListNode {
    public final static Class elementClass = Case.class;
    /** Returns class of this lists's elements */
    public Class getElementClass() {
        return elementClass;
    }
    protected Cases(int lineNumber, Vector elements) {
        super(lineNumber, elements);
    }
    /** Creates an empty "Cases" list */
    public Cases(int lineNumber) {
        super(lineNumber);
    }
    /** Appends "Case" element to this list */
    public Cases appendElement(TreeNode elem) {
        addElement(elem);
        return this;
    }
    public TreeNode copy() {
        return new Cases(lineNumber, copyElements());
    }
}


/** Defines AST constructor 'programc'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class programc extends Program {
    protected Classes classes;
    /** Creates "programc" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for classes
      */
    public programc(int lineNumber, Classes a1) {
        super(lineNumber);
        classes = a1;
    }
    public TreeNode copy() {
        return new programc(lineNumber, (Classes)classes.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "programc\n");
        classes.dump(out, n+2);
    }

    public void printAllFeatures(SymbolTable tb) {

	HashMap<AbstractSymbol, HashMap<AbstractSymbol, AbstractSymbol>> t_v = 
	    (HashMap<AbstractSymbol, HashMap<AbstractSymbol, AbstractSymbol>>)tb.variableLookup();
	HashMap<AbstractSymbol, HashMap<AbstractSymbol, method>> t_m = 
	    (HashMap<AbstractSymbol, HashMap<AbstractSymbol, method>>)tb.methodLookup();
	for(AbstractSymbol className : t_v.keySet()) {
	    System.out.println(className + " : ");
	    HashMap<AbstractSymbol, AbstractSymbol> m = t_v.get(className);
	    HashMap<AbstractSymbol, method> m_m = t_m.get(className);
	    for(AbstractSymbol varName : m.keySet())
		System.out.println("\t" + varName + " : " + m.get(varName));
	    for(AbstractSymbol varName : m_m.keySet())
		System.out.println("\t" + varName + " => " + m_m.get(varName).return_type);
	    System.out.println();
	}
    }
    

    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_program");
        for (Enumeration e = classes.getElements(); e.hasMoreElements(); ) {
	    ((Class_)e.nextElement()).dump_with_types(out, n + 2);
        }
    }
    public void semant() {
	/*
	 * A program is semantically correct if it:
	 * (a) Contains a Main class
	 * (b) The Main class has a main method
	 * (c) The main method has no args
	 * (d) All of the classes in the program are semantically correct
	 */
	
	/* ClassTable constructor may do some semantic analysis */
	ClassTable classTable = new ClassTable(classes);
	SymbolTable tb = new SymbolTable();
	tb.setClassTable(classTable);
	
	//Populate ClassTable's methodLookup and variableLookup
	for(int i = 0; i < classTable.basicClasses().getLength() + classes.getLength(); i++) {
	    class_c next = (class_c)(i < classTable.basicClasses().getLength() ? 
				     classTable.basicClasses().getNth(i) : classes.getNth(i-classTable.basicClasses().getLength()));
	    
	    
	    //Instantiate the lookup tables in tb
	    HashMap<AbstractSymbol, AbstractSymbol> t_v = 
		new HashMap<AbstractSymbol, AbstractSymbol>();
	    HashMap<AbstractSymbol, method> t_m = 
		new HashMap<AbstractSymbol, method>();
	    //Populate the lookup tables
	    for(int j = 0; j < next.features.getLength(); j++) {
		Feature next_f = (Feature)(next.features.getNth(j));
		if(next_f instanceof attr) {
		    attr next_a = (attr)next_f;
		    t_v.put(next_a.name, next_a.type_decl);
		}
		if(next_f instanceof method) {
		    method next_m = (method)next_f;
		    t_m.put(next_m.name, next_m);
		}
	    }
	    tb.variableLookup().put(next.getName(), t_v);
	    tb.methodLookup().put(next.getName(), t_m);
	}
	
	//If Main is not defined, or if Main.main is not defined, or if Main.main has > 0 args
	if(!classTable.containsClass("Main")) {
	    classTable.semantError().println("Class Main is not defined.");
	} else { 
	    HashSet<Feature> main_features = classTable.getClassFeatures("Main");
	    method main_main_feature = null;
	    for(Feature f : main_features) {
		if(f instanceof method && ((method)f).name.equals(TreeConstants.main_meth))
		    main_main_feature = (method)f;
	    }
	    if(main_main_feature == null) {
		classTable.semantError(classTable.getClass_c("Main"))
		    .println("No 'main' method in class Main.");
	    } else if(main_main_feature.formals.getLength() > 0) {
		classTable.semantError(classTable.getClass_c("Main").getFilename(),
				       main_main_feature)
		    .println("'main' method in class Main should have no arguments.");
	    }		    
	}
	tb.enterScope();
	tb.addId(TreeConstants.self, TreeConstants.SELF_TYPE);
	//Type check all of the classes
	for(int i = 0; i < classes.getLength(); i++) {
	    class_c next = ((class_c)classes.getNth(i));
	    ((class_c)classes.getNth(i)).semant(tb, classTable);
	}
	
	if (classTable.errors()) {
	    System.err.println("Compilation halted due to static semantic errors.");
	    System.exit(1);
	}
    }
}


/** Defines AST constructor 'class_c'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class class_c extends Class_ {
    protected AbstractSymbol name;
    protected AbstractSymbol parent;
    protected Features features;
    protected AbstractSymbol filename;
    /** Creates "class_c" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for name
      * @param a1 initial value for parent
      * @param a2 initial value for features
      * @param a3 initial value for filename
      */
    public class_c(int lineNumber, AbstractSymbol a1, AbstractSymbol a2, Features a3, AbstractSymbol a4) {
        super(lineNumber);
        name = a1;
        parent = a2;
        features = a3;
        filename = a4;
    }
    public TreeNode copy() {
        return new class_c(lineNumber, copy_AbstractSymbol(name), copy_AbstractSymbol(parent), (Features)features.copy(), copy_AbstractSymbol(filename));
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "class_c\n");
        dump_AbstractSymbol(out, n+2, name);
        dump_AbstractSymbol(out, n+2, parent);
        features.dump(out, n+2);
        dump_AbstractSymbol(out, n+2, filename);
    }

    public method oldestAncestorMethod(AbstractSymbol method_name, 
					ClassTable ct, 
					SymbolTable st) {
	method out = null;
 	class_c curr;
	for(curr = this; !curr.name.equals(TreeConstants.Object_); curr = ct.getClass_c(curr.parent.toString())) {
	    HashMap<AbstractSymbol, method> mLookup = (HashMap<AbstractSymbol, method>)(st.methodLookup().get(curr.name));
	    if(mLookup.containsKey(method_name))
		out = mLookup.get(method_name);
	}
	HashMap<AbstractSymbol, method> mLookup = (HashMap<AbstractSymbol, method>)(st.methodLookup().get(curr.name));
	if(mLookup.containsKey(method_name))
	    out = mLookup.get(method_name);
	
	return out;
    }
    public boolean checkAncAttrs(AbstractSymbol _attr, ClassTable ct, SymbolTable st) {
	return oldestAncestorAttr(_attr, ct, st) != null;
    }
    public AbstractSymbol oldestAncestorAttr(AbstractSymbol _attr, ClassTable ct, SymbolTable st) {
	if(this.parent == null || this.name.equals(TreeConstants.Object_))
	    return ((HashMap<AbstractSymbol, AbstractSymbol>)(st.variableLookup().get(TreeConstants.Object_))).get(_attr);
	class_c curr = ct.getClass_c(this.parent.toString());
	AbstractSymbol out = null;
	for(; !curr.name.equals(TreeConstants.Object_); curr = ct.getClass_c(curr.parent.toString())) {
	    HashMap<AbstractSymbol, AbstractSymbol> vLookup = 
		(HashMap<AbstractSymbol, AbstractSymbol>)(st.variableLookup().get(curr.name));	    
	    if(vLookup.containsKey(_attr)) {
		out = vLookup.get(_attr);
	    }
	}
	HashMap<AbstractSymbol, AbstractSymbol> vLookup = 
	    (HashMap<AbstractSymbol, AbstractSymbol>)(st.variableLookup().get(curr.name));
	if(vLookup.containsKey(_attr)) {
	    out = vLookup.get(_attr);
	}
	return out;
    }

    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_class");
        dump_AbstractSymbol(out, n + 2, name);
        dump_AbstractSymbol(out, n + 2, parent);
        out.print(Utilities.pad(n + 2) + "\"");
        Utilities.printEscapedString(out, filename.getString());
        out.println("\"\n" + Utilities.pad(n + 2) + "(");
        for (Enumeration e = features.getElements(); e.hasMoreElements();) {
	    ((Feature)e.nextElement()).dump_with_types(out, n + 2);
        }
        out.println(Utilities.pad(n + 2) + ")");
    }

    public void semant(SymbolTable st, ClassTable ct) {
	/*
	 * For each feature, if it is:
	 *   -An attribute : We check that there are no ancestors with the attribute name
	 *   -A method : We check that it is correctly inheriting if an ancestor as the same method name. 
	 *               This means checking argument length, argument type, etc
	 */
	for(int i = 0; i < features.getLength(); i++) {
	    Feature f = (Feature)(features.getNth(i));
	    if(f instanceof attr) {
		if( ((attr)f).name.equals(TreeConstants.self)  ) {
		    ct.semantError(getFilename(), f)
			.printf("'self' cannot be the name of an attribute.\n");
		} else if (checkAncAttrs( ((attr)f).name, ct, st)) {
		    ct.semantError(getFilename(), f)
			.println("Attribute " + ((attr)f).name + " is an attribute of an inherited class.");		    
		}
		if( !ct.containsClass( ((attr)f).type_decl.toString() ) )
		    ct.semantError(this.getFilename(), f)
			.println("Class " + ((attr)f).type_decl + " of attribute " +
				 ((attr)f).name + " is undefined.");
	    }
	    if(f instanceof method) {
		method oldestMethod = oldestAncestorMethod( ((method)f).name, ct, st);
		if(oldestMethod != f) { //We have some ancestor that has the same method name
		    method _f = (method)f;
		    if(!oldestMethod.return_type.equals(_f.return_type)) {
			ct.semantError(this.getFilename(), f)
			    .println("In redefined method " + _f.name + ", return type " 
				     + _f.return_type 
				     + " is different from original return type " 
				     + oldestMethod.return_type + ".");
		    }
		    else if(oldestMethod.formals.getLength() != _f.formals.getLength()) {
			ct.semantError(this.getFilename(), f)
			    .println("Incompatible number of formal parameters in redefined method " + _f.name + ".");
		    } else {
			for(int j = 0; j < _f.formals.getLength(); j++) {
			    formalc mine = (formalc)(_f.formals.getNth(j));
			    formalc theirs = (formalc)(oldestMethod.formals.getNth(j));
			    if(!mine.type_decl.equals(theirs.type_decl))
				ct.semantError(this.getFilename(), f)
				    .println("In redefined method " + _f.name + ", parameter type " 
					     + mine.type_decl + 
					     " is different from original type " 
					     + theirs.type_decl + ".");
			}
		    }
		}
		if( !ct.containsClass( ((method)f).return_type.toString() ) )
		    ct.semantError(this.getFilename(), f)
			.println("Undefined return type " + ((method)f).return_type + 
				 " in method " + ((method)f).name + ".");
	    }
	}
	//Have to run after the last for-loop so that the order of my errors matches ref-semant
	for(int i = 0; i < features.getLength(); i++) {
	    ((Feature)features.getNth(i)).semant(this, st, ct);
	}
    }

    public AbstractSymbol getName()     { return name; }
    public AbstractSymbol getParent()   { return parent; }
    public AbstractSymbol getFilename() { return filename; }
    public Features getFeatures()       { return features; }

}


/** Defines AST constructor 'method'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class method extends Feature {
    protected AbstractSymbol name;
    protected Formals formals;
    protected AbstractSymbol return_type;
    protected Expression expr;
    /** Creates "method" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for name
      * @param a1 initial value for formals
      * @param a2 initial value for return_type
      * @param a3 initial value for expr
      */
    public method(int lineNumber, AbstractSymbol a1, Formals a2, AbstractSymbol a3, Expression a4) {
        super(lineNumber);
        name = a1;
        formals = a2;
        return_type = a3;
        expr = a4;
    }
    public TreeNode copy() {
        return new method(lineNumber, copy_AbstractSymbol(name), (Formals)formals.copy(), copy_AbstractSymbol(return_type), (Expression)expr.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "method\n");
        dump_AbstractSymbol(out, n+2, name);
        formals.dump(out, n+2);
        dump_AbstractSymbol(out, n+2, return_type);
        expr.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_method");
        dump_AbstractSymbol(out, n + 2, name);
        for (Enumeration e = formals.getElements(); e.hasMoreElements();) {
	    ((Formal)e.nextElement()).dump_with_types(out, n + 2);
        }
        dump_AbstractSymbol(out, n + 2, return_type);
	expr.dump_with_types(out, n + 2);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	st.enterScope( new Hashtable((HashMap)(st.variableLookup().get(_class.name))) );

	//formalNames makes sure we don't repeat any argument names
	HashSet<AbstractSymbol> formalNames = new HashSet<AbstractSymbol>();
	for(int i = 0; i < formals.getLength(); i++) {
	    formalc next = (formalc)(formals.getNth(i));
	    if(next.name.equals(TreeConstants.self)) {
		ct.semantError(_class.getFilename(), this)
		    .printf("'self' cannot be the name of a formal parameter.\n");
	    } else if(formalNames.contains(next.name)) {
		ct.semantError(_class.getFilename(), this)
		    .printf("Formal parameter %s is multiply defined.\n", next.name);
	    } else {
		st.addId(next.name, next.type_decl);
	    }
	    if(next.type_decl.equals(TreeConstants.SELF_TYPE)) {
		ct.semantError(_class.getFilename(), next)
		    .printf("Formal parameter %s cannot have type SELF_TYPE.\n", next.name);
	    } else if(!ct.containsClass(next.type_decl.toString())) {
		ct.semantError(_class.getFilename(), next)
		    .printf("Class %s of formal parameter %s is undefined.\n", next.type_decl,
			    next.name);
	    }
	    formalNames.add(next.name);
	}

	expr.semant(_class, st, ct);
	AbstractSymbol t1 = return_type.equals(TreeConstants.SELF_TYPE) ? _class.name : return_type;
	AbstractSymbol t2 = expr.get_type().equals(TreeConstants.SELF_TYPE) ? _class.name : expr.get_type();
	
        if(!ct.isLEQ(t2,t1) && ct.containsClass(return_type.toString()))
	    ct.semantError(_class.getFilename(), this)
		.printf("Inferred return type %s of method %s does not conform to declared return type %s.\n", expr.get_type(), this.name, return_type);
	st.exitScope();
    }
}


/** Defines AST constructor 'attr'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class attr extends Feature {
    protected AbstractSymbol name;
    protected AbstractSymbol type_decl;
    protected Expression init;
    /** Creates "attr" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for name
      * @param a1 initial value for type_decl
      * @param a2 initial value for init
      */
    public attr(int lineNumber, AbstractSymbol a1, AbstractSymbol a2, Expression a3) {
        super(lineNumber);
        name = a1;
        type_decl = a2;
        init = a3;
    }
    public TreeNode copy() {
        return new attr(lineNumber, copy_AbstractSymbol(name), copy_AbstractSymbol(type_decl), (Expression)init.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "attr\n");
        dump_AbstractSymbol(out, n+2, name);
        dump_AbstractSymbol(out, n+2, type_decl);
        init.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_attr");
        dump_AbstractSymbol(out, n + 2, name);
        dump_AbstractSymbol(out, n + 2, type_decl);
	init.dump_with_types(out, n + 2);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	st.enterScope( new Hashtable((HashMap)(st.variableLookup().get(_class.name))) );
	init.semant(_class, st, ct);
	AbstractSymbol t1 = type_decl.equals(TreeConstants.SELF_TYPE) ? _class.name : type_decl;
	AbstractSymbol t2 = init.get_type().equals(TreeConstants.SELF_TYPE) ? _class.name : init.get_type();
        if(!ct.isLEQ(t2,t1))
	    ct.semantError(_class.getFilename(), this)
		.println("Inferred type " + init.get_type() + " of initialization of attribute"
			 + this.name + " does not conform to declared type " + this.type_decl);
	st.exitScope();
    }
}


/** Defines AST constructor 'formalc'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class formalc extends Formal {
    protected AbstractSymbol name;
    protected AbstractSymbol type_decl;
    /** Creates "formalc" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for name
      * @param a1 initial value for type_decl
      */
    public formalc(int lineNumber, AbstractSymbol a1, AbstractSymbol a2) {
        super(lineNumber);
        name = a1;
        type_decl = a2;
    }
    public TreeNode copy() {
        return new formalc(lineNumber, copy_AbstractSymbol(name), copy_AbstractSymbol(type_decl));
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "formalc\n");
        dump_AbstractSymbol(out, n+2, name);
        dump_AbstractSymbol(out, n+2, type_decl);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_formal");
        dump_AbstractSymbol(out, n + 2, name);
        dump_AbstractSymbol(out, n + 2, type_decl);
    }

    public void semant() {
	
    }
}


/** Defines AST constructor 'branch'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class branch extends Case {
    protected AbstractSymbol name;
    protected AbstractSymbol type_decl;
    protected Expression expr;
    
    protected AbstractSymbol type;
    /** Creates "branch" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for name
      * @param a1 initial value for type_decl
      * @param a2 initial value for expr
      */
    public branch(int lineNumber, AbstractSymbol a1, AbstractSymbol a2, Expression a3) {
        super(lineNumber);
        name = a1;
        type_decl = a2;
        expr = a3;
    }
    public TreeNode copy() {
        return new branch(lineNumber, copy_AbstractSymbol(name), copy_AbstractSymbol(type_decl), (Expression)expr.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "branch\n");
        dump_AbstractSymbol(out, n+2, name);
        dump_AbstractSymbol(out, n+2, type_decl);
        expr.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_branch");
        dump_AbstractSymbol(out, n + 2, name);
        dump_AbstractSymbol(out, n + 2, type_decl);
	expr.dump_with_types(out, n + 2);
    }
    public AbstractSymbol get_type() { 
	return type;
    }
    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	if(!ct.containsClass(type_decl.toString())) {
	    ct.semantError(_class.getFilename(), this)
		.printf("Class %s of case branch is undefined.\n", type_decl);
	} else if(type_decl.equals(TreeConstants.SELF_TYPE)) {
	    ct.semantError(_class.getFilename(), this)
		.printf("Identifier %s declared with type SELF_TYPE in case branch.\n", 
			name);
	}
	if(name.equals(TreeConstants.self))
	    ct.semantError(_class.getFilename(), this)
		.printf("'self' bound in 'case'.\n");
	else {
	    st.enterScope();
	    st.addId(name, type_decl);
	    expr.semant(_class, st, ct);
	    type = expr.get_type();
	    st.exitScope();
	}
	if(type == null)
	    type = TreeConstants.Object_; //Bottomed out...
    }
}


/** Defines AST constructor 'assign'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class assign extends Expression {
    protected AbstractSymbol name;
    protected Expression expr;
    /** Creates "assign" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for name
      * @param a1 initial value for expr
      */
    public assign(int lineNumber, AbstractSymbol a1, Expression a2) {
        super(lineNumber);
        name = a1;
        expr = a2;
    }
    public TreeNode copy() {
        return new assign(lineNumber, copy_AbstractSymbol(name), (Expression)expr.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "assign\n");
        dump_AbstractSymbol(out, n+2, name);
        expr.dump(out, n+2);
    }
    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_assign");
        dump_AbstractSymbol(out, n + 2, name);
	expr.dump_with_types(out, n + 2);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	expr.semant(_class, st, ct);
	if(!st.isInTable(name) && !_class.checkAncAttrs(name, ct, st)) {
	    ct.semantError(_class.getFilename(), this)
		.println("Assignment to undeclared variable " + this.name + ".");
	    set_type(TreeConstants.Object_);
	} else if(name.equals(TreeConstants.self)) {
	    ct.semantError(_class.getFilename(), this)
		.println("Cannot assign to 'self'.");
	    set_type(expr.get_type());
	} else {
	    AbstractSymbol receiverType = (AbstractSymbol)(st.lookup(name));
	    receiverType = (receiverType == null) ? 
		_class.oldestAncestorAttr(name, ct, st) : 
		receiverType;
	    if(!ct.isLEQ(expr.get_type(), receiverType)) {
		ct.semantError(_class.getFilename(), this)
		    .printf("Type %s of assigned expression does not conform to declared type %s of identifier %s.\n", expr.get_type(), receiverType, name);
	    }
	}

	set_type(expr.get_type());
    }
}


/** Defines AST constructor 'static_dispatch'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class static_dispatch extends Expression {
    protected Expression expr;
    protected AbstractSymbol type_name;
    protected AbstractSymbol name;
    protected Expressions actual;
    /** Creates "static_dispatch" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for expr
      * @param a1 initial value for type_name
      * @param a2 initial value for name
      * @param a3 initial value for actual
      */
    public static_dispatch(int lineNumber, Expression a1, AbstractSymbol a2, AbstractSymbol a3, Expressions a4) {
        super(lineNumber);
        expr = a1;
        type_name = a2;
        name = a3;
        actual = a4;
    }
    public TreeNode copy() {
        return new static_dispatch(lineNumber, (Expression)expr.copy(), copy_AbstractSymbol(type_name), copy_AbstractSymbol(name), (Expressions)actual.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "static_dispatch\n");
        expr.dump(out, n+2);
        dump_AbstractSymbol(out, n+2, type_name);
        dump_AbstractSymbol(out, n+2, name);
        actual.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_static_dispatch");
	expr.dump_with_types(out, n + 2);
        dump_AbstractSymbol(out, n + 2, type_name);
        dump_AbstractSymbol(out, n + 2, name);
        out.println(Utilities.pad(n + 2) + "(");
        for (Enumeration e = actual.getElements(); e.hasMoreElements();) {
	    ((Expression)e.nextElement()).dump_with_types(out, n + 2);
        }
        out.println(Utilities.pad(n + 2) + ")");
	dump_type(out, n);
    }
    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	for(int i = 0; i < actual.getLength(); i++)
	    ((Expression)actual.getNth(i)).semant(_class, st, ct);

	expr.semant(_class, st, ct);
	if(!ct.containsClass(type_name.toString())) {
	    ct.semantError(_class.getFilename(), this)
		.printf("Static dispatch to undefined class %s.\n", type_name);
	    set_type(TreeConstants.Object_);
	}
	else if(type_name.equals(TreeConstants.SELF_TYPE)) {
	    ct.semantError(_class.getFilename(), this)
		.printf("Static dispatch to SELF_TYPE.\n", type_name);
	    set_type(TreeConstants.Object_);
	}
	else if(!ct.isLEQ(  expr.get_type().equals(TreeConstants.SELF_TYPE) ? _class.name : expr.get_type()
			    , type_name)) {
	    ct.semantError(_class.getFilename(), this)
		.printf("Expression type %s does not conform to declared static dispatch type %s.\n", expr.get_type(), type_name);
	    set_type(TreeConstants.Object_);
	}
	else {
	    //If none of those errors above... we can continue with finding the dynamic method of the id
	    //Then we continue to check if our current dispatch arguments matches the ancestor method arguments
	    method ancestorMethod = (ct.getClass_c(type_name.toString())).oldestAncestorMethod(name, ct, st);
	    if(ancestorMethod.formals.getLength() != actual.getLength()) {
		ct.semantError(_class.getFilename(), this)
		    .printf("Method %s invoked with wrong number of arguments.\n", name);
	    } else {
		for(int i = 0; i < ancestorMethod.formals.getLength(); i++) {
		    Expression mine = (Expression)actual.getNth(i);
		    formalc next = (formalc)ancestorMethod.formals.getNth(i);
		    
		    AbstractSymbol a1 = (mine.get_type().equals(TreeConstants.SELF_TYPE)) ? 
			_class.name : mine.get_type();
		    AbstractSymbol a2 = (next.type_decl.equals(TreeConstants.SELF_TYPE)) ? 
			_class.name : next.type_decl;
		    
		    
		    if(!ct.isLEQ(a1,a2)) {
			ct.semantError(_class.getFilename(), this)
			    .printf("In call of method %s, type %s of parameter #%d does not conform to declared type %s.\n", name, mine.get_type(), i, next.type_decl);
		    }
		}
	    }

	    AbstractSymbol dispatchType = ancestorMethod.return_type;
	    set_type(dispatchType);
	}
    }
}


/** Defines AST constructor 'dispatch'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class dispatch extends Expression {
    protected Expression expr;
    protected AbstractSymbol name;
    protected Expressions actual;
    /** Creates "dispatch" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for expr
      * @param a1 initial value for name
      * @param a2 initial value for actual
      */
    public dispatch(int lineNumber, Expression a1, AbstractSymbol a2, Expressions a3) {
        super(lineNumber);
        expr = a1;
        name = a2;
        actual = a3;
    }
    public TreeNode copy() {
        return new dispatch(lineNumber, (Expression)expr.copy(), copy_AbstractSymbol(name), (Expressions)actual.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "dispatch\n");
        expr.dump(out, n+2);
        dump_AbstractSymbol(out, n+2, name);
        actual.dump(out, n+2);
    }

    private method earliestMethod(AbstractSymbol m, class_c _class, SymbolTable st, ClassTable ct) {
	for(class_c curr = _class; curr != null; curr = ct.getClass_c(curr.parent.toString())) {
	    if(curr != null) {
		HashMap<AbstractSymbol, method> tab = (HashMap<AbstractSymbol, method>)st.methodLookup().get(curr.name);
		if(tab.containsKey(m))
		     return tab.get(m);
	    }
	}
	return null;
    }
    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_dispatch");
	expr.dump_with_types(out, n + 2);
        dump_AbstractSymbol(out, n + 2, name);
        out.println(Utilities.pad(n + 2) + "(");
        for (Enumeration e = actual.getElements(); e.hasMoreElements();) {
	    ((Expression)e.nextElement()).dump_with_types(out, n + 2);
        }
        out.println(Utilities.pad(n + 2) + ")");
	dump_type(out, n);
    }
    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	expr.semant(_class, st, ct);

	for(int i = 0; i < actual.getLength(); i++)
	    ((Expression)actual.getNth(i)).semant(_class, st, ct);

	class_c baseClass = expr.get_type().equals(TreeConstants.SELF_TYPE) ? 
	    _class : ct.getClass_c(expr.get_type().toString());
	method earliest = earliestMethod(name, baseClass, st, ct);
	if(earliest == null) {
	    ct.semantError(_class.getFilename(), this)
		.printf("Dispatch to undefined method %s.\n", name);
	    set_type(TreeConstants.Object_);
	    return;
	}
	if(earliest.formals.getLength() != actual.getLength()) {
	    ct.semantError(_class.getFilename(), this)
		.printf("Method %s called with wrong number of arguments.\n", name);
	    set_type(TreeConstants.Object_);
	    return;
	} else {
	    //Then we continue to check if our current dispatch arguments matches the ancestor method arguments
	    for(int i = 0; i < actual.getLength(); i++) {
		Expression actualForm = (Expression)actual.getNth(i);
		formalc parentForm = (formalc)earliest.formals.getNth(i);
		
		AbstractSymbol a1 = (actualForm.get_type().equals(TreeConstants.SELF_TYPE)) ? 
		    _class.name : actualForm.get_type();
		AbstractSymbol a2 = (parentForm.type_decl.equals(TreeConstants.SELF_TYPE)) ? 
		    _class.name : parentForm.type_decl;

		
		if(!ct.isLEQ(a1,a2)) {
		    ct.semantError(_class.getFilename(), this)
			.printf("In call of method %s, type %s of parameter #%d does not conform to declared type %s.\n", name, parentForm.name, i, parentForm.type_decl);
		}
	    }
	}
	if(earliest.return_type.equals(TreeConstants.SELF_TYPE)) {
	    set_type(expr.get_type());
	} else {
	    set_type(earliest.return_type);
	}

    }
}


/** Defines AST constructor 'cond'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class cond extends Expression {
    protected Expression pred;
    protected Expression then_exp;
    protected Expression else_exp;
    /** Creates "cond" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for pred
      * @param a1 initial value for then_exp
      * @param a2 initial value for else_exp
      */
    public cond(int lineNumber, Expression a1, Expression a2, Expression a3) {
        super(lineNumber);
        pred = a1;
        then_exp = a2;
        else_exp = a3;
    }
    public TreeNode copy() {
        return new cond(lineNumber, (Expression)pred.copy(), (Expression)then_exp.copy(), (Expression)else_exp.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "cond\n");
        pred.dump(out, n+2);
        then_exp.dump(out, n+2);
        else_exp.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_cond");
	pred.dump_with_types(out, n + 2);
	then_exp.dump_with_types(out, n + 2);
	else_exp.dump_with_types(out, n + 2);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	pred.semant(_class, st, ct);
	then_exp.semant(_class, st, ct);
	else_exp.semant(_class, st, ct);

	if(!pred.get_type().equals(TreeConstants.Bool))
	    ct.semantError(_class.getFilename(), this)
		.println("Predicate of 'if' does not have type Bool.");

	AbstractSymbol t1 = then_exp.get_type();
	AbstractSymbol t2 = else_exp.get_type();

	set_type(ct.LUB(then_exp.get_type(), else_exp.get_type(), _class, _class));
    }


}


/** Defines AST constructor 'loop'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class loop extends Expression {
    protected Expression pred;
    protected Expression body;
    /** Creates "loop" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for pred
      * @param a1 initial value for body
      */
    public loop(int lineNumber, Expression a1, Expression a2) {
        super(lineNumber);
        pred = a1;
        body = a2;
    }
    public TreeNode copy() {
        return new loop(lineNumber, (Expression)pred.copy(), (Expression)body.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "loop\n");
        pred.dump(out, n+2);
        body.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_loop");
	pred.dump_with_types(out, n + 2);
	body.dump_with_types(out, n + 2);
	dump_type(out, n);
    }
    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	pred.semant(_class, st, ct);
	body.semant(_class, st, ct);
	
	if(!pred.get_type().equals(TreeConstants.Bool))
	    ct.semantError(_class.getFilename(), this)
		.println("Loop condition does not have type Bool.");

	set_type(TreeConstants.Object_);
    }

}


/** Defines AST constructor 'typcase'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class typcase extends Expression {
    protected Expression expr;
    protected Cases cases;
    /** Creates "typcase" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for expr
      * @param a1 initial value for cases
      */
    public typcase(int lineNumber, Expression a1, Cases a2) {
        super(lineNumber);
        expr = a1;
        cases = a2;
    }
    public TreeNode copy() {
        return new typcase(lineNumber, (Expression)expr.copy(), (Cases)cases.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "typcase\n");
        expr.dump(out, n+2);
        cases.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_typcase");
	expr.dump_with_types(out, n + 2);
        for (Enumeration e = cases.getElements(); e.hasMoreElements();) {
	    ((Case)e.nextElement()).dump_with_types(out, n + 2);
        }
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	expr.semant(_class, st, ct);
	HashSet<AbstractSymbol> typesSeen = new HashSet<AbstractSymbol>();
	AbstractSymbol type = null;
	for(int i = 0; i < cases.getLength(); i++) {
	    branch next = (branch)(cases.getNth(i));
	    if(typesSeen.contains(next.type_decl))
		ct.semantError(_class.getFilename(), this)
		    .printf("Duplicate branch %s in case statement.\n", next.type_decl);
	    typesSeen.add(next.type_decl);
	    next.semant(_class, st, ct);
	    type = ct.LUB(type, next.get_type(), _class, _class);
	}
	set_type(type);
    }

}


/** Defines AST constructor 'block'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class block extends Expression {
    protected Expressions body;
    /** Creates "block" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for body
      */
    public block(int lineNumber, Expressions a1) {
        super(lineNumber);
        body = a1;
    }
    public TreeNode copy() {
        return new block(lineNumber, (Expressions)body.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "block\n");
        body.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_block");
        for (Enumeration e = body.getElements(); e.hasMoreElements();) {
	    ((Expression)e.nextElement()).dump_with_types(out, n + 2);
        }
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	for(int i = 0; i < body.getLength(); i++) {
	    Expression next = (Expression)(body.getNth(i));
	    next.semant(_class, st, ct);
	}
	//Type is the type of the last expression in the block
	set_type( ((Expression)body.getNth(body.getLength()-1)).get_type() );
    }

}


/** Defines AST constructor 'let'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class let extends Expression {
    protected AbstractSymbol identifier;
    protected AbstractSymbol type_decl;
    protected Expression init;
    protected Expression body;
    /** Creates "let" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for identifier
      * @param a1 initial value for type_decl
      * @param a2 initial value for init
      * @param a3 initial value for body
      */
    public let(int lineNumber, AbstractSymbol a1, AbstractSymbol a2, Expression a3, Expression a4) {
        super(lineNumber);
        identifier = a1;
        type_decl = a2;
        init = a3;
        body = a4;
    }
    public TreeNode copy() {
        return new let(lineNumber, copy_AbstractSymbol(identifier), copy_AbstractSymbol(type_decl), (Expression)init.copy(), (Expression)body.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "let\n");
        dump_AbstractSymbol(out, n+2, identifier);
        dump_AbstractSymbol(out, n+2, type_decl);
        init.dump(out, n+2);
        body.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_let");
	dump_AbstractSymbol(out, n + 2, identifier);
	dump_AbstractSymbol(out, n + 2, type_decl);
	init.dump_with_types(out, n + 2);
	body.dump_with_types(out, n + 2);
	dump_type(out, n);
    }
    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	init.semant(_class, st, ct);
	if(!ct.containsClass(type_decl.toString())) {
	    ct.semantError(_class.getFilename(), this)
		.printf("Class %s of let-bound identifier %s is undefined.\n",
			type_decl, identifier);
	} else {
	    AbstractSymbol t1 = type_decl.equals(TreeConstants.SELF_TYPE) ? _class.name : type_decl;
	    AbstractSymbol t2 = init.get_type().equals(TreeConstants.SELF_TYPE) ? _class.name : init.get_type();
	    if(!ct.isLEQ(t2,t1))
		ct.semantError(_class.getFilename(), this)
		    .printf("Inferred type %s of initialization of %s does not conform to identifier's declared type %s.\n", init.get_type(), identifier, type_decl);
	    
	}
	st.enterScope();
	if(identifier.equals(TreeConstants.self))
	    ct.semantError(_class.getFilename(), this)
		.printf("'self' cannot be bound in a 'let' expression.\n");
	else {
	    st.addId(identifier, type_decl);	    
	}
	body.semant(_class, st, ct);
	st.exitScope();
	set_type(body.get_type());
    }
}

/** Defines AST constructor 'plus'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class plus extends Expression {
    protected Expression e1;
    protected Expression e2;
    /** Creates "plus" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for e1
      * @param a1 initial value for e2
      */
    public plus(int lineNumber, Expression a1, Expression a2) {
        super(lineNumber);
        e1 = a1;
        e2 = a2;
    }
    public TreeNode copy() {
        return new plus(lineNumber, (Expression)e1.copy(), (Expression)e2.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "plus\n");
        e1.dump(out, n+2);
        e2.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_plus");
	e1.dump_with_types(out, n + 2);
	e2.dump_with_types(out, n + 2);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	e1.semant(_class, st, ct);
	e2.semant(_class, st, ct);

	if(!e1.get_type().equals(TreeConstants.Int) ||
	   !e2.get_type().equals(TreeConstants.Int)) {
	    ct.semantError(_class.getFilename(), this)
		.printf("non-Int arguments : %s + %s.\n", e1.get_type(), e2.get_type());
	}
	set_type(TreeConstants.Int);
    }


}


/** Defines AST constructor 'sub'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class sub extends Expression {
    protected Expression e1;
    protected Expression e2;
    /** Creates "sub" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for e1
      * @param a1 initial value for e2
      */
    public sub(int lineNumber, Expression a1, Expression a2) {
        super(lineNumber);
        e1 = a1;
        e2 = a2;
    }
    public TreeNode copy() {
        return new sub(lineNumber, (Expression)e1.copy(), (Expression)e2.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "sub\n");
        e1.dump(out, n+2);
        e2.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_sub");
	e1.dump_with_types(out, n + 2);
	e2.dump_with_types(out, n + 2);
	dump_type(out, n);
    }
    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	e1.semant(_class, st, ct);
	e2.semant(_class, st, ct);

	if(!e1.get_type().equals(TreeConstants.Int) ||
	   !e2.get_type().equals(TreeConstants.Int)) {
	    ct.semantError(_class.getFilename(), this)
		.printf("non-Int arguments : %s - %s.\n", e1.get_type(), e2.get_type());
	}
	set_type(TreeConstants.Int);
    }

}


/** Defines AST constructor 'mul'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class mul extends Expression {
    protected Expression e1;
    protected Expression e2;
    /** Creates "mul" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for e1
      * @param a1 initial value for e2
      */
    public mul(int lineNumber, Expression a1, Expression a2) {
        super(lineNumber);
        e1 = a1;
        e2 = a2;
    }
    public TreeNode copy() {
        return new mul(lineNumber, (Expression)e1.copy(), (Expression)e2.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "mul\n");
        e1.dump(out, n+2);
        e2.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_mul");
	e1.dump_with_types(out, n + 2);
	e2.dump_with_types(out, n + 2);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	e1.semant(_class, st, ct);
	e2.semant(_class, st, ct);

	if(!e1.get_type().equals(TreeConstants.Int) ||
	   !e2.get_type().equals(TreeConstants.Int)) {
	    ct.semantError(_class.getFilename(), this)
		.printf("non-Int arguments : %s * %s.\n", e1.get_type(), e2.get_type());
	}
	set_type(TreeConstants.Int);
    }


}


/** Defines AST constructor 'divide'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class divide extends Expression {
    protected Expression e1;
    protected Expression e2;
    /** Creates "divide" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for e1
      * @param a1 initial value for e2
      */
    public divide(int lineNumber, Expression a1, Expression a2) {
        super(lineNumber);
        e1 = a1;
        e2 = a2;
    }
    public TreeNode copy() {
        return new divide(lineNumber, (Expression)e1.copy(), (Expression)e2.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "divide\n");
        e1.dump(out, n+2);
        e2.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_divide");
	e1.dump_with_types(out, n + 2);
	e2.dump_with_types(out, n + 2);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	e1.semant(_class, st, ct);
	e2.semant(_class, st, ct);

	if(!e1.get_type().equals(TreeConstants.Int) ||
	   !e2.get_type().equals(TreeConstants.Int)) {
	    ct.semantError(_class.getFilename(), this)
		.printf("non-Int arguments : %s / %s.\n", e1.get_type(), e2.get_type());
	}
	set_type(TreeConstants.Int);
    }


}


/** Defines AST constructor 'neg'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class neg extends Expression {
    protected Expression e1;
    /** Creates "neg" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for e1
      */
    public neg(int lineNumber, Expression a1) {
        super(lineNumber);
        e1 = a1;
    }
    public TreeNode copy() {
        return new neg(lineNumber, (Expression)e1.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "neg\n");
        e1.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_neg");
	e1.dump_with_types(out, n + 2);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	e1.semant(_class, st, ct);

	if(!e1.get_type().equals(TreeConstants.Int)) {
	    ct.semantError(_class.getFilename(), this)
		.printf("Argument of '~' has type %s instead of Int.\n", e1.get_type());
	}
	set_type(TreeConstants.Int);
    }
}


/** Defines AST constructor 'lt'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class lt extends Expression {
    protected Expression e1;
    protected Expression e2;
    /** Creates "lt" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for e1
      * @param a1 initial value for e2
      */
    public lt(int lineNumber, Expression a1, Expression a2) {
        super(lineNumber);
        e1 = a1;
        e2 = a2;
    }
    public TreeNode copy() {
        return new lt(lineNumber, (Expression)e1.copy(), (Expression)e2.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "lt\n");
        e1.dump(out, n+2);
        e2.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_lt");
	e1.dump_with_types(out, n + 2);
	e2.dump_with_types(out, n + 2);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	e1.semant(_class, st, ct);
	e2.semant(_class, st, ct);

	if(!e1.get_type().equals(TreeConstants.Int) ||
	   !e2.get_type().equals(TreeConstants.Int)) {
	    ct.semantError(_class.getFilename(), this)
		.printf("non-Int arguments : %s < %s.\n", e1.get_type(), e2.get_type());
	}
	set_type(TreeConstants.Bool);
    }


}


/** Defines AST constructor 'eq'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class eq extends Expression {
    protected Expression e1;
    protected Expression e2;
    /** Creates "eq" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for e1
      * @param a1 initial value for e2
      */
    public eq(int lineNumber, Expression a1, Expression a2) {
        super(lineNumber);
        e1 = a1;
        e2 = a2;
    }
    public TreeNode copy() {
        return new eq(lineNumber, (Expression)e1.copy(), (Expression)e2.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "eq\n");
        e1.dump(out, n+2);
        e2.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_eq");
	e1.dump_with_types(out, n + 2);
	e2.dump_with_types(out, n + 2);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	e1.semant(_class, st, ct);
	e2.semant(_class, st, ct);

	if( (!e1.get_type().equals(TreeConstants.Int) && e2.get_type().equals(TreeConstants.Int)) ||
	    (e1.get_type().equals(TreeConstants.Int) && !e2.get_type().equals(TreeConstants.Int)) || 
	    (!e1.get_type().equals(TreeConstants.Bool) && e2.get_type().equals(TreeConstants.Bool)) || 
	    (e1.get_type().equals(TreeConstants.Bool) && !e2.get_type().equals(TreeConstants.Bool)) || 
	    (!e1.get_type().equals(TreeConstants.Str) && e2.get_type().equals(TreeConstants.Str)) || 
	    (e1.get_type().equals(TreeConstants.Str) && !e2.get_type().equals(TreeConstants.Str))) {
	    ct.semantError(_class.getFilename(), this)
		.println("Illegal comparison with a basic type.");
	}
	set_type(TreeConstants.Bool);
    }


}


/** Defines AST constructor 'leq'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class leq extends Expression {
    protected Expression e1;
    protected Expression e2;
    /** Creates "leq" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for e1
      * @param a1 initial value for e2
      */
    public leq(int lineNumber, Expression a1, Expression a2) {
        super(lineNumber);
        e1 = a1;
        e2 = a2;
    }
    public TreeNode copy() {
        return new leq(lineNumber, (Expression)e1.copy(), (Expression)e2.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "leq\n");
        e1.dump(out, n+2);
        e2.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_leq");
	e1.dump_with_types(out, n + 2);
	e2.dump_with_types(out, n + 2);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	e1.semant(_class, st, ct);
	e2.semant(_class, st, ct);

	if(!e1.get_type().equals(TreeConstants.Int) ||
	   !e2.get_type().equals(TreeConstants.Int)) {
	    ct.semantError(_class.getFilename(), this)
		.printf("non-Int arguments : %s <= %s.\n", e1.get_type(), e2.get_type());
	    set_type(TreeConstants.Object_);
	}
	set_type(TreeConstants.Bool);
    }


}


/** Defines AST constructor 'comp'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class comp extends Expression {
    protected Expression e1;
    /** Creates "comp" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for e1
      */
    public comp(int lineNumber, Expression a1) {
        super(lineNumber);
        e1 = a1;
    }
    public TreeNode copy() {
        return new comp(lineNumber, (Expression)e1.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "comp\n");
        e1.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_comp");
	e1.dump_with_types(out, n + 2);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	e1.semant(_class, st, ct);
	if(!e1.get_type().equals(TreeConstants.Bool)) {
	    ct.semantError(_class.getFilename(), this)
		.printf("Argument of 'not' has type %s instead of Bool.\n", e1.get_type());
	    set_type(TreeConstants.Object_);
	}
	set_type(TreeConstants.Bool);
    }


}


/** Defines AST constructor 'int_const'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class int_const extends Expression {
    protected AbstractSymbol token;
    /** Creates "int_const" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for token
      */
    public int_const(int lineNumber, AbstractSymbol a1) {
        super(lineNumber);
        token = a1;
    }
    public TreeNode copy() {
        return new int_const(lineNumber, copy_AbstractSymbol(token));
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "int_const\n");
        dump_AbstractSymbol(out, n+2, token);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_int");
	dump_AbstractSymbol(out, n + 2, token);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	set_type(TreeConstants.Int);
    }


}


/** Defines AST constructor 'bool_const'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class bool_const extends Expression {
    protected Boolean val;
    /** Creates "bool_const" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for val
      */
    public bool_const(int lineNumber, Boolean a1) {
        super(lineNumber);
        val = a1;
    }
    public TreeNode copy() {
        return new bool_const(lineNumber, copy_Boolean(val));
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "bool_const\n");
        dump_Boolean(out, n+2, val);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_bool");
	dump_Boolean(out, n + 2, val);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	set_type(TreeConstants.Bool);
    }


}


/** Defines AST constructor 'string_const'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class string_const extends Expression {
    protected AbstractSymbol token;
    /** Creates "string_const" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for token
      */
    public string_const(int lineNumber, AbstractSymbol a1) {
        super(lineNumber);
        token = a1;
    }
    public TreeNode copy() {
        return new string_const(lineNumber, copy_AbstractSymbol(token));
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "string_const\n");
        dump_AbstractSymbol(out, n+2, token);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_string");
	out.print(Utilities.pad(n + 2) + "\"");
	Utilities.printEscapedString(out, token.getString());
	out.println("\"");
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	set_type(TreeConstants.Str);
    }


}


/** Defines AST constructor 'new_'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class new_ extends Expression {
    protected AbstractSymbol type_name;
    /** Creates "new_" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for type_name
      */
    public new_(int lineNumber, AbstractSymbol a1) {
        super(lineNumber);
        type_name = a1;
    }
    public TreeNode copy() {
        return new new_(lineNumber, copy_AbstractSymbol(type_name));
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "new_\n");
        dump_AbstractSymbol(out, n+2, type_name);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_new");
	dump_AbstractSymbol(out, n + 2, type_name);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	if(!ct.containsClass(type_name.toString())) {
	    ct.semantError(_class.getFilename(), this)
		.printf("'new' used with undefined class %s.\n", type_name);
	    set_type(TreeConstants.Object_);
	} else {
	    set_type(type_name);
	}
    }


}


/** Defines AST constructor 'isvoid'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class isvoid extends Expression {
    protected Expression e1;
    /** Creates "isvoid" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for e1
      */
    public isvoid(int lineNumber, Expression a1) {
        super(lineNumber);
        e1 = a1;
    }
    public TreeNode copy() {
        return new isvoid(lineNumber, (Expression)e1.copy());
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "isvoid\n");
        e1.dump(out, n+2);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_isvoid");
	e1.dump_with_types(out, n + 2);
	dump_type(out, n);
    }

    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	e1.semant(_class, st, ct);
	set_type(TreeConstants.Bool);
    }


}


/** Defines AST constructor 'no_expr'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class no_expr extends Expression {
    /** Creates "no_expr" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      */
    public no_expr(int lineNumber) {
        super(lineNumber);
    }
    public TreeNode copy() {
        return new no_expr(lineNumber);
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "no_expr\n");
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_no_expr");
	dump_type(out, n);
    }
    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	set_type(TreeConstants.No_type);
    }
}


/** Defines AST constructor 'object'.
    <p>
    See <a href="TreeNode.html">TreeNode</a> for full documentation. */
class object extends Expression {
    protected AbstractSymbol name;
    /** Creates "object" AST node. 
      *
      * @param lineNumber the line in the source file from which this node came.
      * @param a0 initial value for name
      */
    public object(int lineNumber, AbstractSymbol a1) {
        super(lineNumber);
        name = a1;
    }
    public TreeNode copy() {
        return new object(lineNumber, copy_AbstractSymbol(name));
    }
    public void dump(PrintStream out, int n) {
        out.print(Utilities.pad(n) + "object\n");
        dump_AbstractSymbol(out, n+2, name);
    }

    
    public void dump_with_types(PrintStream out, int n) {
        dump_line(out, n);
        out.println(Utilities.pad(n) + "_object");
	dump_AbstractSymbol(out, n + 2, name);
	dump_type(out, n);
    }
    public void semant(class_c _class, SymbolTable st, ClassTable ct) {
	if(name.equals(TreeConstants.self)) {
	    set_type(TreeConstants.SELF_TYPE);
	} else if(!st.isInTable(name) && !_class.checkAncAttrs(name, ct, st)) {
	    ct.semantError(_class.getFilename(), this)
		.printf("Undeclared identifier %s.\n", name);
	    set_type(TreeConstants.Object_);
	} else {
	    AbstractSymbol type = (AbstractSymbol)st.lookup(name);
	    if(type == null) {
		type = _class.oldestAncestorAttr(name, ct, st);
	    }
	    if(!ct.containsClass(type.toString())) {
		ct.semantError(_class.getFilename(), this)
		    .printf("Invalid type %s for %s.\n", type, name);
		set_type(TreeConstants.Object_);
	    } else {
		set_type(type);
	    }
	}
    }
}
