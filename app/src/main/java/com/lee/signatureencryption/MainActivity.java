package com.lee.signatureencryption;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        getSignature(this);

        SingatureClass singatureClass = new SingatureClass();
        String packageResult = singatureClass.verificationPackage(this);
        String SignResult = singatureClass.verificationSign(this);
        TextView textView = (TextView) findViewById(R.id.text);
        textView.setText(packageResult + "\n" + SignResult);
        
    }

    /**
     * 获取应用签名，获取签名成功后删除该方法,
     * 将获取到签名打印出来，复制到.c++文件中
     * 
     * 注意 debug包和 release包的签名值是不一样的，
     * 如果要获取release包的签名值，则需要把该方法生成的签名值先写入本地日志，
     * 然后从日志中获取签名值，将获取到的签名值复制到.c++文件中
     * @param context
     * @return
     */
    public static String getSignature(Context context) {
        try {
            /** 通过包管理器获得指定包名包含签名的包信息 **/
            PackageInfo packageInfo = context.getPackageManager().getPackageInfo(context.getPackageName(), PackageManager.GET_SIGNATURES);
            /******* 通过返回的包信息获得签名数组 *******/
            Signature[] signatures = packageInfo.signatures;
            /******* 循环遍历签名数组拼接应用签名 *******/
            return signatures[0].toCharsString();
            /************** 得到应用签名 **************/
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }
        return null;
    }
}
