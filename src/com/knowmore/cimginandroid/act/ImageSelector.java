package com.knowmore.cimginandroid.act;

import com.knowmore.cimginandroid.R;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class ImageSelector extends Activity implements OnClickListener {

	private Button mSelectorButton = null;
	private static final int LOAD_IMAGE = 10;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.activity_image_selector);
		mSelectorButton = (Button) findViewById(R.id.button_to_select);
		mSelectorButton.setOnClickListener(this);
		
	}

	@Override
	public void onClick(View v) {
		if (v == mSelectorButton) {
			Intent intent = new Intent(
					Intent.ACTION_PICK,
					android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
			startActivityForResult(intent, LOAD_IMAGE);
		}

	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {

		if (requestCode == LOAD_IMAGE && resultCode == RESULT_OK) {
			
			if (data != null) {
				
				Uri pickedImageUri = data.getData();
				String[] filePath = { MediaStore.Images.Media.DATA };
				Cursor cursor = getContentResolver().query(pickedImageUri,
						filePath, null, null, null);
				
				if (cursor != null) {
					
					cursor.moveToFirst();
					String pickedIagePath = cursor.getString(cursor
							.getColumnIndex(filePath[0]));
					ImageUtil.blurrImage(pickedIagePath);
					cursor.close();
					
				}

			}
			
			super.onActivityResult(requestCode, resultCode, data);
		}
	}
	
	}
