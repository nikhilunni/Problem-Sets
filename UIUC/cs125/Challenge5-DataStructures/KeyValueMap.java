//UIUC CS125 FALL 2013 MP. File: KeyValueMap.java, CS125 Project: Challenge5-DataStructures, Version: 2013-10-14T15:32:35-0500.796362776
/**
 *@author nunni2
 */


import java.awt.Color;

public class KeyValueMap { // aka Dictionary or Map

	private String[] keys = new String[10];
	private Color[] values = new Color[10];
	private int size = 0;
	
	/**
	 * Adds a key and value. If the key already exists, it replaces the original
	 * entry.
	 */

	public void add(String key, Color value) {
		boolean exists = false;
		for(int i = 0; i < keys.length; i++) {
			if(keys[i] != null) {
				if(keys[i].equals(key)) {
					exists = true;
					values[i] = value;
				}
					
			}
		}
		if(!exists) {
			size++;
			if (size > keys.length) {
				String[] oldKeys = keys;
				Color[] oldValues = values;				
				keys = new String[size*2];
				values = new Color[size*2];
				for(int i = 0; i < oldKeys.length; i++) {
					keys[i] = oldKeys[i];
					values[i] = oldValues[i];
				}
			}
			keys[size-1] = key;
			values[size-1] = value;
		}

	}

	/**
	 * Returns particular Color object previously added to this map.
	 */
	public Color find(String key) {
		int index = -1;
		for(int i = 0; i < keys.length; i++) {
			String s = keys[i];
			if(s != null) {
				if(s.equals(key))
					index = i;
			}
		}
		return (index >= 0) ? values[index] : null;
	}

	/**
	 * Returns true if the key exists in this map.
	 */
	public boolean exists(String key) {
		for(int i = 0; i < keys.length; i++) {
			String s = keys[i];
			if(s != null) {
				if(s.equals(key))
					return true;
			}
		}
		return false;
	}

	/**
	 * Removes the key (and the color) from this map.
	 */
	public void remove(String key) {
		for(int i = 0; i < keys.length; i++) {
			String s = keys[i];
			if(s != null) {
				if(s.equals(key)) {
					keys[i] = null;
					values[i] = null;
				}
			}
		}
	}

}
