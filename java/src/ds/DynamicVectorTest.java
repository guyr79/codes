package ds;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class DynamicVectorTest {
	DynamicVector<String> dvs = new DynamicVector<>(40);
	DynamicVector<Integer> dvi = new DynamicVector<>();
	DynamicVector<?> dvq;

	@Test
	void creatAndGetSizeAndIsEmptyAndPushAndGetTopTest() {
		assertTrue(dvs.getSize() == 0);
		assertEquals(true, dvs.isEmpty());
		assertEquals(true, dvi.isEmpty());
		dvs.push("shalosh");
		dvs.push("shaloshim");
		dvs.push("3rd element");
		assertTrue(dvs.getSize() == 3);
		for (int i = 0; i < 1000; ++i) {
			dvi.push(i);
			assertTrue(dvi.getSize() == i + 1);
			assertTrue(dvi.getTop() == i);
			if (i > 5) {
				assertTrue(dvi.get(i - 5) == i - 5);
			}
		}
	}

	@Test
	void popTest() {
		dvi.clear();
		assertTrue(dvi.isEmpty());
		for (int i = 0; i < 1000; ++i) {
			dvi.push(i);
		}
		for (int i = 0; i < 1000; ++i) {
			dvi.pop();
			assertTrue(dvi.getSize() == 1000 - 1 - i);
		}
	}

	@Test
	void assertTest() {
		dvi.clear();
		@SuppressWarnings("unused") IndexOutOfBoundsException e = assertThrows(IndexOutOfBoundsException.class, () -> {
			dvi.pop();
		});
		@SuppressWarnings("unused") IndexOutOfBoundsException j = assertThrows(IndexOutOfBoundsException.class, () -> {
			dvi.get(5);
		});		
	}
}
