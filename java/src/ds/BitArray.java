package ds;

import java.io.Serializable;
import java.util.Arrays;
import java.util.Random;
@SuppressWarnings(value = { "serial" })
public class BitArray implements Serializable{
	// STATIC class VARIABLES
	final static long BITS_IN_INT = Integer.BYTES * 8;

	// PRIVATE VARIABLES
	private int[] _inner_arr; // int is chosen since random long does not cover all possibilities
	private long _size;

	// PUBLIC CONSTRUCTORS

	public BitArray(long size) {
		assert size > 0;
		_size = size;
		_inner_arr = new int[1 + (int) ((_size - 1) / BITS_IN_INT)];
	}

	// copy constructor
	public BitArray(BitArray src) {
		if (src == null)
			throw new NullPointerException();
		_size = src.GetSize();
		_inner_arr = src.GetArrProxy();
	}

	// PUBLIC STATIC FUNCTIONS

	public static BitArray Generate(long size) {
		BitArray newBitArr = new BitArray(size);
		Random random = new Random();
		int innerArrSize = newBitArr._GetInnerArrSize();
		for (int i = 0; i < innerArrSize; ++i) {
			newBitArr._inner_arr[i] = random.nextInt();
		}
		newBitArr._inner_arr[innerArrSize - 1] >>>= newBitArr._GetBitsToRightShift();
		return newBitArr;
	}

	// PUBLIC FUNCTIONS
	public long GetSize() {
		return _size;
	}

	public int[] GetArrProxy() {
		return _inner_arr.clone();
	}

	public void SetAllBitsOn() {
		_setAllInnerArrCellsTo(-1);
		_inner_arr[_inner_arr.length - 1] >>>= _GetBitsToRightShift();
	}

	public void SetAllBitsOff() {
		_setAllInnerArrCellsTo(0);
	}

	public void SetBitValue(long index, boolean value) {
		assert index < _size && index >= 0;
		int mask = 1;
		IndexLocation indLocation = new IndexLocation(index);
		if (value)
			_inner_arr[indLocation._CELL] |= mask << indLocation._CELL_INDEX;
		else
			_inner_arr[indLocation._CELL] &= ~(mask << indLocation._CELL_INDEX);
	}

	public void SetBitOn(long index) {
		SetBitValue(index, true);
	}

	public void SetBitOff(long index) {
		SetBitValue(index, false);
	}

	public boolean BitIsOn(long index) {
		assert index < _size && index >= 0;
		int mask = 1;
		IndexLocation indLocation = new IndexLocation(index);
		mask <<= indLocation._CELL_INDEX;
		return ((_inner_arr[indLocation._CELL] & mask) != 0) ? true : false;
	}

	public boolean BitIsOff(long index) {
		assert index < _size && index >= 0;
		return !BitIsOn(index);
	}

	public void FlipBit(long index) {
		assert index < _size && index >= 0;
		SetBitValue(index, BitIsOff(index));
	}

	public int CountBits() {
		int[] arrProxy = GetArrProxy();
		int cnt = 0;
		for (int i = 0; i < arrProxy.length; ++i) {
			while (arrProxy[i] != 0) {
				++cnt;
				arrProxy[i] &= arrProxy[i] - 1;
			}
		}
		return cnt;
	}

	public void Mirror() {
		long midBarrInd, ind1, ind2;
		midBarrInd = _size >> 1;
		ind1 = midBarrInd - 1;
		ind2 = ((_size & 1L) == 1) ? midBarrInd + 1 : midBarrInd;
		for(; ind2<_size; ++ind2, --ind1) {
			_SwapBits(ind1,ind2);
		}
	}
	
	public void RotateLeft(long steps) {
		long i,k,m,gcd;
		boolean stateToKeep;
		steps %= _size;
		gcd = GCD(_size, steps);
		for(i = 0; i < gcd; ++i) {
			stateToKeep = BitIsOn(i);
			k = i;
			m = (k + steps < _size) ? (k + steps) : (k + steps - _size);
			do {
	            SetBitValue(k, BitIsOn(m));
	            k = m;
	            m = (k + steps < _size) ? (k + steps) : (k + steps - _size);
			} while (m!=i);
			SetBitValue(k, stateToKeep);
		}
	}
	
	public void RotateRight(long steps) {
	    long equivalent_left_step;
	    steps %= _size;
	    equivalent_left_step = _size - steps;
	    RotateLeft(equivalent_left_step);
	}

	// OVERRIDE FUNCTIONS

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + Arrays.hashCode(_inner_arr);
		result = prime * result + (int) (_size ^ (_size >>> 32));
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
		BitArray other = (BitArray) obj;
		if (!Arrays.equals(_inner_arr, other._inner_arr))
			return false;
		if (_size != other._size)
			return false;
		return true;
	}
	
	// PRIVATE STATIC FUNCTIONS //
	private static long GCD(long a, long b) {
		if (b == 0)
			return a;
		else if (a == 0)
			return b;
		return GCD(b, a % b);
	}
	
	// PRIVATE FUNCTIONS //

	private int _GetInnerArrSize() {
		return 1 + (int) ((_size - 1) / BITS_IN_INT);
	}

	private int _GetBitsToRightShift() {
		return (int) (_GetInnerArrSize() * BITS_IN_INT - GetSize());
	}

	private void _setAllInnerArrCellsTo(int value) {
		for (int i = 0; i < _inner_arr.length; ++i) {
			_inner_arr[i] = value; // to put all bits on "on"
		}
	}
	
	private void _SwapBits(long ind1,long ind2) {
		boolean ind1State = BitIsOn(ind1);
		boolean ind2State = BitIsOn(ind2);
		SetBitValue(ind1, ind2State);
		SetBitValue(ind2, ind1State);		
	}

	// PRIVATE CLASSES
	private static class IndexLocation {
		final int _CELL;
		final int _CELL_INDEX;

		public IndexLocation(long index) {
			_CELL = (int) (index / BITS_IN_INT);
			_CELL_INDEX = (int) (index % BITS_IN_INT);
		}
	}
}
