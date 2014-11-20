package com.knowmore.cimginandroid.act;

public class ImageUtil {

	static {
		System.loadLibrary("CimgInAndroid");
	}
	
	public static native void blurrImage(String sourceImageFilepath);

}
