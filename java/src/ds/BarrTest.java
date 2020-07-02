package ds;

import static ds.BitArray.BITS_IN_INT;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

class BarrTest {
	private static final long DEF_TEST_SIZE = 1000;
	BitArray barr;
	BitArray barr2;

	@Test
	void CopyConstructorTest() {
		for (long k = 1; k <= DEF_TEST_SIZE; k++) {
			barr = BitArray.Generate(k);
			BitArray copyBarr = new BitArray(barr);
			assertTrue(barr.equals(copyBarr));
			assertTrue(copyBarr.hashCode() == barr.hashCode());
		}
	}

	@Test
	void SetAllBitsOnTest() {
		for (long k = 1; k <= DEF_TEST_SIZE; k++) {
			barr = BitArray.Generate(k);
			boolean flag = true;
			barr.SetAllBitsOn();
			int[] arr = barr.GetArrProxy();
			for (int i = 0; i < arr.length - 1 && flag; ++i) {
				flag &= (arr[i] == -1);
			}
			flag &= arr[arr.length - 1] == -1 >>> (arr.length * BITS_IN_INT - barr.GetSize());
			assertTrue(flag);
		}
	}

	@Test
	void SetAllBitsOffTest() {
		for (long k = 1; k <= DEF_TEST_SIZE; k++) {
			barr = BitArray.Generate(k);
			barr.SetAllBitsOff();
			boolean flag = true;
			int[] arr = barr.GetArrProxy();
			for (int i = 0; i < arr.length && flag; ++i) {
				flag &= (arr[i] == 0);
			}
			assertTrue(flag);
		}
	}

	@Test
	void SetBitOnTest() {
		for (long k = 1; k <= DEF_TEST_SIZE; k++) {
			barr = new BitArray(k);
			barr2 = new BitArray(k);
			barr.SetAllBitsOff();
			barr2.SetAllBitsOff();
			assertTrue(barr.equals(barr2));
			for (long i = 0; i < k; ++i) {
				assertTrue(barr.equals(barr2));
				barr.SetBitOn(i);
				assertFalse(barr.equals(barr2));
				barr2.SetBitOn(i);
				assertTrue(barr.equals(barr2));
			}
		}
	}

	@Test
	void SetBitOffTest() {
		for (long k = 1; k <= DEF_TEST_SIZE; k++) {
			barr = new BitArray(k);
			barr2 = new BitArray(k);
			barr.SetAllBitsOn();
			assertFalse(barr.equals(barr2));
			barr2.SetAllBitsOn();
			assertTrue(barr.equals(barr2));
			for (long i = 0; i < k; ++i) {
				assertTrue(barr.equals(barr2));
				barr.SetBitOff(i);
				assertFalse(barr.equals(barr2));
				barr2.SetBitOff(i);
				assertTrue(barr.equals(barr2));
			}
		}
	}

	@Test
	void BitIsOnTest() {
		for (long k = 1; k <= DEF_TEST_SIZE; k++) {
			barr = new BitArray(k);
			barr.SetAllBitsOff();
			for (long i = 0; i < k; ++i) {
				assertFalse(barr.BitIsOn(i));
				barr.SetBitOn(i);
				assertTrue(barr.BitIsOn(i));
			}
		}
	}

	@Test
	void BitIsOffTest() {
		for (long k = 1; k <= DEF_TEST_SIZE; k++) {
			barr = new BitArray(k);
			barr.SetAllBitsOn();
			for (long i = 0; i < k; ++i) {
				assertFalse(barr.BitIsOff(i));
				barr.SetBitOff(i);
				assertTrue(barr.BitIsOff(i));
			}
		}
	}

	@Test
	void FlipBitTest() {
		for (long k = 1; k <= DEF_TEST_SIZE; k++) {
			barr = new BitArray(k);
			barr2 = new BitArray(k);
			barr.SetAllBitsOn();
			barr2.SetAllBitsOff();
			for (long i = 0; i < k; ++i) {
				assertFalse(barr.BitIsOff(i));
				barr.FlipBit(i);
				assertTrue(barr.BitIsOff(i));
			}
			for (long i = 0; i < k; ++i) {
				assertFalse(barr2.BitIsOn(i));
				barr2.FlipBit(i);
				assertTrue(barr2.BitIsOn(i));
			}
		}
	}

	@Test
	void CountOnBitsTest() {
		for (long k = 1; k <= DEF_TEST_SIZE; k++) {
			barr = new BitArray(k);
			barr.SetAllBitsOff();
			int stop1 = 100, stop2 = 1000, inc1 = 1, inc7 = 7, inc13 = 13;
			int expected_cnt = 0;
			long i = 0;
			for (; i < stop1 && i < k; i += inc1) {
				barr.SetBitOn(i);
				++expected_cnt;
			}
			for (; i < stop2 && i < k; i += inc7) {
				barr.SetBitOn(i);
				++expected_cnt;
			}
			for (; i < k; i += inc13) {
				barr.SetBitOn(i);
				++expected_cnt;
			}
			assertEquals(expected_cnt, barr.CountBits());
		}
	}

	@Test
	void MirrorTest() {
		for (long k = 1; k <= DEF_TEST_SIZE; k++) {
			barr = BitArray.Generate(k);
			barr2 = new BitArray(barr);
			barr.Mirror();
			long barrInd = 0, barr2Ind = barr2.GetSize() - 1;
			for (; barrInd < barr.GetSize(); ++barrInd, --barr2Ind) {
				assertEquals(barr.BitIsOn(barrInd), barr2.BitIsOn(barr2Ind));
			}
		}
	}

	@Test
	void RotateLeftTest() {
		for (int k = 1; k < DEF_TEST_SIZE; ++k) {
			for (long steps = 1; steps < k+20; ++steps) {
				long i_b, i_b2;
				long act_steps = steps % k;
				barr = BitArray.Generate(k);
				barr2 = new BitArray(k);

				for (i_b2 = 0, i_b = act_steps; i_b < barr.GetSize(); ++i_b, ++i_b2) {
					barr2.SetBitValue(i_b2, barr.BitIsOn(i_b));
				}

				for (i_b = 0; i_b2 < k; ++i_b, ++i_b2) {
					barr2.SetBitValue(i_b2, barr.BitIsOn(i_b));
				}

				barr.RotateLeft(steps);
				assertTrue(barr.equals(barr2));
			}
		}
	}
}
