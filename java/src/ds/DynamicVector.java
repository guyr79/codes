package ds;

import java.io.Serializable;
import java.util.Arrays; //copyOf

@SuppressWarnings("serial")
public class DynamicVector<E> implements Serializable {
	// STATIC CLASS VARIABLES
	final static int DV_MIN_CAPACITY = 16;
	final static int DV_RESIZE_FACTOR = 2;
	final static int DV_DECREASE_THRESHOLD = 4;
	// PRIVATE VARIABLES
	private int _capacity = DV_MIN_CAPACITY;
	private int _size;
	private Object[] _dataElements;

	// PUBLIC CONSTRUCTORS
	public DynamicVector () {
		this(DV_MIN_CAPACITY);
	}
	
	public DynamicVector(int capacity) {
		this._size = 0;
		while (capacity > this._capacity) {
			this._capacity <<= 1;
		}
		this._dataElements = new Object[this._capacity];
	}

	public DynamicVector(DynamicVector<E> other) {
		this._size = other._size;
		this._capacity = other._capacity;
		this._dataElements = Arrays.copyOf(other._dataElements, other._capacity);
	}

	// PUBLIC FUNCTIONS
	public boolean isEmpty() {
		return _size == 0;
	}
	
	public int getSize() {
		return _size;
	}
	
	public void push(E element) {
		if (this._size == this._capacity) {
			this._dataElements = Arrays.copyOf(this._dataElements, (this._capacity *= DV_RESIZE_FACTOR));
		}
		this._dataElements[this._size] = element;
		this._size++; 
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + _capacity;
		result = prime * result + Arrays.deepHashCode(_dataElements);
		result = prime * result + _size;
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		@SuppressWarnings("unchecked") DynamicVector<E> other = (DynamicVector<E>) obj;
		if (_capacity != other._capacity)
			return false;
		if (!Arrays.deepEquals(_dataElements, other._dataElements))
			return false;
		if (_size != other._size)
			return false;
		return true;
	}

	public void replace(E element, int index) throws IndexOutOfBoundsException{
		if (this._size <= index) {
			throw new IndexOutOfBoundsException(index);
		}
		this._dataElements[index] = element;
	}	
	
	public E getTop() {
		return get(this._size - 1);
	}
	
	public E get(int index) {
		if (this._size <= index) {
			throw new IndexOutOfBoundsException(index);
		}
		@SuppressWarnings("unchecked") E e = (E)this._dataElements[index];
		return e;
	}
	
	public void pop()
	{
		this._dataElements[--this._size] = null;
	}
	
	public void clear() {
		this._dataElements = new Object[DV_MIN_CAPACITY];
		this._size = 0;
	}
}
