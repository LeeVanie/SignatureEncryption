package com.lee.signatureencryption;

import android.content.Context;

/**
 * @类名: ${type_name}
 * @功能描述:
 * @作者: ${user}
 * @时间: ${date}
 * @最后修改者:
 * @最后修改内容:
 */
public class SingatureClass {

    static
    {
        System.loadLibrary("signature");
    }
    
    //验证包名
    public native String verificationPackage(Object context); 

    //验证签名
    public native String verificationSign(Object context);
}
