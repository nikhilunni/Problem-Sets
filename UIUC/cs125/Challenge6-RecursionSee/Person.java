//UIUC CS125 FALL 2013 MP. File: Person.java, CS125 Project: Challenge6-RecursionSee, Version: 2013-11-05T17:19:55-0600.019560079
/**
 * @author nunni2
 *
 */
public class Person
{
private final String name;
private final int age;
private final char gender;
private final Person child1; //left child
private final Person child2; //right child

public Person(String name, int age, char gender, Person c1, Person c2)
{
    this.name=name;
    this.age=age;
    this.gender=gender;
    this.child1 = c1;
    this.child2 = c2;
}

public String toString()
{
    return name+"*"+age+"*"+gender;
}

public String getName() 
{
	return name;
}

public int getAge() 
{
	return age;
}

public char getGender() 
{
	return gender;
}

public boolean equals(Person p)
{
	return (this.name.equals(p.name)) &&
			(this.age==p.age) &&
			(this.gender==p.gender);
}


public void print() 
{
   System.out.println(this);
   if(child1 != null)
       child1.print();
   if(child2 != null)
       child2.print();
   
}

public int count() // total person count including this object
{
	if(child1 == null && child2 != null)
		return 1 + child2.count();
	if(child2 == null && child1 != null)
		return 1 + child1.count();
	if(child1 == null && child2 == null)
		return 1;
	return 1+ child1.count() + child2.count();
}
public int countGrandChildren() // but not greatGrandChildren
{
	int count = 0;
	if (child1 != null)
		count += child1.countChildren();
	if (child2 != null) 
		count += child2.countChildren();
	return count;
}
private int countChildren() {
	int count = 0;
	if(child1 != null) {
		count++;
		System.out.println(child1.name);
	}
		
	if(child2 != null) {
		count++;
		System.out.println(child2.name);
	}
	return count;
}

public int countMaxGenerations()
{
	if(child1 == null && child2 != null) {
		return child2.countMaxGenerations();
	}
	if(child2 == null && child1 != null) {
		return child1.countMaxGenerations();
	}
	if(child1 == null && child2 == null)
		return 1;
	return Math.max(1+child1.countMaxGenerations(), 1+child2.countMaxGenerations());
}


public int countGender(char gen)
{
	if(child1 == null && child2 != null)
		return (gen == getGender() ? 1 : 0) + child2.countGender(gen);
	if(child2 == null && child1 != null)
		return (gen == getGender() ? 1 : 0) + child1.countGender(gen);
	if(child1 == null && child2 == null)
		return (gen == getGender() ? 1 : 0);
	return (gen == getGender() ? 1 : 0) + child1.countGender(gen) + child2.countGender(gen);
}


public Person search(String name, int maxGeneration)
{
	if(getName().equals(name))
		return this;
	if(child1 == null || child2 == null || maxGeneration <= 0)
		return null;
	Person person1 = child1.search(name, maxGeneration-1);
	Person person2 = child2.search(name, maxGeneration-1);
	if(person1 != null)
		return person1;
	if(person2 != null)
		return person2;
	return null;
}

} // end of class
