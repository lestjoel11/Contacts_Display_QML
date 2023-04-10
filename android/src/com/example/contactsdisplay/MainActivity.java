package com.example.contactsdisplay;

import org.qtproject.qt.android.bindings.QtActivity;

import android.database.Cursor;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.util.Log;
import android.database.Cursor;
import android.database.ContentObserver;
import android.os.Handler;
import android.os.HandlerThread;

import android.Manifest;

import java.util.HashMap;
import java.util.Map;
import java.lang.reflect.Field;

import org.json.JSONObject;
import org.json.JSONArray;

import androidx.core.content.ContextCompat;
import androidx.core.app.ActivityCompat;
import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import android.content.pm.PackageManager;

public  class MainActivity extends QtActivity implements ActivityCompat.OnRequestPermissionsResultCallback{
    public long pointer;
    public native void onContactChangedNative(long pointer);

    public void readPointer(long nativePointer) {
        pointer = nativePointer;
        onContactChangedNative(nativePointer);
        Log.d("Pointer: ",pointer+"");
    }

    // Helper method to request the necessary permissions
    private static final int PERMISSIONS_REQUEST_CODE = 1;

    private void requestAppPermissions() {
        String[] permissions = new String[]{
                Manifest.permission.READ_CONTACTS,
                Manifest.permission.WRITE_CONTACTS
        };

        boolean permissionsGranted = true;
        for (String permission : permissions) {
            if (ContextCompat.checkSelfPermission(this, permission) != PackageManager.PERMISSION_GRANTED) {
                permissionsGranted = false;
                break;
            }
        }

        if (!permissionsGranted) {
            ActivityCompat.requestPermissions(this, permissions, PERMISSIONS_REQUEST_CODE);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults){
        if (requestCode == PERMISSIONS_REQUEST_CODE) {
            boolean allPermissionsGranted = true;
            for (int result : grantResults) {
                if (result != PackageManager.PERMISSION_GRANTED) {
                    allPermissionsGranted = false;
                    break;
                }
            }
            if (!allPermissionsGranted) {
                // handle the case where permissions were not granted
            }
        }
    }



    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestAppPermissions();
        Log.d("Activity Started", "Oncreate");
        HandlerThread handlerThread = new HandlerThread("contentObserverThread");
        handlerThread.start();
        Handler contentObserverHandler = new Handler(handlerThread.getLooper());
        MyContentObserver contentObserver = new MyContentObserver(contentObserverHandler);
        getApplicationContext().getContentResolver().registerContentObserver(ContactsContract.Contacts.CONTENT_URI, true, contentObserver);

    }
//    @Override
//    protected void onDestroy() {
//        super.onDestroy();
//        getApplicationContext().getContentResolver().unregisterContentObserver(contentObserver);
//    }
    private class MyContentObserver extends ContentObserver {
        public MyContentObserver(Handler contentObserverHandler) {
            super(contentObserverHandler);
        }
        @Override
        public void onChange(boolean selfChange) {
            // Use the uri and collection of URIs, do the lookup using the cursor and send back the changes
            super.onChange(selfChange);
            Log.d("Change Recognised", "In Contact");
            onContactChangedNative(pointer);
            Log.d("Change Recognised", "After Contact");

        }
    }

    public String loadContactDetails() {
        //Convert to Json String
        String[] projection = new String[] { ContactsContract.Contacts.LOOKUP_KEY, ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME, ContactsContract.CommonDataKinds.Phone.NUMBER, ContactsContract.CommonDataKinds.Email.ADDRESS };
        Cursor cursor = getContentResolver().query(ContactsContract.CommonDataKinds.Phone.CONTENT_URI, projection, null, null, ContactsContract.Contacts.SORT_KEY_PRIMARY + " ASC");
//        Map<String, String>[] contactData = new HashMap[cursor.getCount()];
        JSONArray contactData = new JSONArray();

        int currContactCount = 0;
        while (cursor.moveToNext()) {
            //TODO:Get Sorted Results A-Z
            //Lookup key: To retrieve all the details for a contact, search the ContactsContract.Data table for any rows that contain the contact's LOOKUP_KEY.
            Map<String, String> currentContact = new HashMap<>();
            currentContact.put("LOOKUP_KEY",cursor.getString(cursor.getColumnIndex(ContactsContract.Contacts.LOOKUP_KEY)));
            currentContact.put("ContactName",cursor.getString(cursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME))) ;
            currentContact.put("ContactEmail",cursor.getString(cursor.getColumnIndex(ContactsContract.CommonDataKinds.Email.ADDRESS)));
            currentContact.put("ContactPhone",cursor.getString(cursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER)));
            JSONObject jsonObject = new JSONObject(currentContact);
            contactData.put(jsonObject);
            currContactCount++;
        }
        cursor.close();

        return contactData.toString();
    }
}
