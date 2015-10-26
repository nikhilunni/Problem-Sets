//UIUC CS125 FALL 2013 MP. File: GeocacheList.java, CS125 Project: Challenge5-DataStructures, Version: 2013-10-14T15:32:35-0500.796362776
/**
 * Complete the following GeocacheList, to ensure all unit tests pass.
 * There are several errors in the code below
 *
 * Hint: Get the Geocache class working and passing its tests first.
 * @author nunni2
 */
public class GeocacheList {
	private Geocache[] data = new Geocache[10];
	private int size = 0;

	public Geocache getGeocache(int i) {
		return data[i];
	}

	public int getSize() {
		return size;
	}

	public GeocacheList() {
	}

	public GeocacheList(GeocacheList other, boolean deepCopy) {
		data = new Geocache[other.data.length];
		if(deepCopy) {
			for(int i = 0; i < data.length; i++) {
				if(other.getData()[i] != null)
					data[i] = new Geocache(other.getData()[i]);
			}
		}
		else {
			for(int i = 0; i < data.length; i++)
				data[i] = other.getData()[i];
		}
		size = other.size;		
	}

	public void add(Geocache p) {
		size++;
		if (size > data.length) {
			Geocache[] old = data;
			data = new Geocache[size * 2];
			for (int i = 0; i < old.length; i++)
				data[i] = old[i];
		}
		data[size-1] = p;
	}

	public Geocache removeFromTop() {
		Geocache output = data[size-1];
		size--;		
		Geocache[] temp = new Geocache[size];
		for(int i = 0; i < size; i++) {
			temp[i] = data[i];
		}
		data = temp;
		return output;
	}
	
	public Geocache[] getData() {
		return data;
	}

	public String toString() {
		StringBuffer s = new StringBuffer("GeocacheList:");
		for (int i = 0; i < size; i++) {
			if (i > 0)
				s.append(',');
			s.append(data[i]);
		}
		return s.toString();
	}
	
}
