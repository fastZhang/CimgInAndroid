/*
 * ImageProcessingClass.cpp
 *
 *  Created on: 19-Nov-2014
 *      Author: dev
 */

#define cimg_display 0
#define cimg_use_jpeg
#define cimg_use_png
#include "CImg.h"
#include <jni.h>
#include <android/log.h>

#define LOG_TAG "com.knowmore.cimglibrary"

using namespace cimg_library;

#ifdef __cplusplus
extern "C" {
#endif

void cBlurrImage(JNIEnv *env, const char* imageFilePath);
void throwJavaException(JNIEnv *env, const char *msg);
void getFilePath(const char* filePath);

JNIEXPORT void JNICALL Java_com_knowmore_cimginandroid_act_ImageUtil_blurrImage(
		JNIEnv *env, jobject obj, jstring imageFilePath) {

	const char* sourceFilePath = env->GetStringUTFChars(imageFilePath,
			JNI_FALSE);

	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "sourceFilePath: %s",
			sourceFilePath);

	cBlurrImage(env, sourceFilePath);

}

void cBlurrImage(JNIEnv *env, const char* imageFilePath) {

	CImg<unsigned char> imageToChange;
	CImg<unsigned char> imageToSave;

	try {

		imageToChange.assign(imageFilePath);
		imageToSave.fill(0); // initialize image pixels to zero [We may instead use a 5 parameter constructor]
		imageToSave = imageToChange.get_blur(5);
		imageToSave.save(imageFilePath, 2, 2);

		getFilePath(imageFilePath);

	} catch (CImgArgumentException e) {
		throwJavaException(env, e.what());
	} catch (CImgIOException e) {
		throwJavaException(env, e.what());
	}

}
void throwJavaException(JNIEnv *env, const char *msg) {
	// You can put your own exception here
	jclass c = env->FindClass("java/lang/RuntimeException");

	if (NULL == c) {
		//B plan: null pointer ...
		c = env->FindClass("java/lang/NullPointerException");
	}

	env->ThrowNew(c, msg);
}

#ifdef __cplusplus
}
#endif

