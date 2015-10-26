//UIUC CS125 FALL 2013 MP. File: RGBUtilitiesTest.java, CS125 Project: Challenge4-Photoscoop, Version: 2013-10-05T05:38:13-0500.017648101
import junit.framework.TestCase;

/**
 * Tests RGBUtilities.
 * You do not need to modify this file, however it may be useful
 * to read how each test works.
 * @author angrave
 *
 */
public class RGBUtilitiesTest extends TestCase {

	public void testToComponents() {
		assertEquals( 0x33, RGBUtilities.toRed(0x44332211));
		assertEquals( 0x22, RGBUtilities.toGreen(0x44332211));
		assertEquals( 0x11, RGBUtilities.toBlue(0x44332211));
	}

	public void testToRGB() {
		assertEquals( 0x112233, RGBUtilities.toRGB(0x11, 0x22, 0x33));
	}

	public void testAuthorship() {
		boolean success = CheckInputOutput.checkAuthorship("RGBUtilities.java");
		if (!success)
			fail("Fix authorship");
	}

	public void tearDown() {
		CheckInputOutput.resetInputOutput();
	}

	public void setUp() throws Exception {
		super.setUp();
		CheckInputOutput.setUp();
	}
}
