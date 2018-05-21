//
// Created by Lee on 2018/5/21.
//
#include "com_lee_signatureencryption_SingatureClass.h"
#include <jni.h> 
#include <string.h>  
#include <unistd.h>  

/**
 * 发布的app 签名,只有和本签名一致的app 才会返回 AUTH_KEY
 * 这个RELEASE_SIGN的值是上一步用java代码获取的值
 */
const char* RELEASE_SIGN = "********92a864886f70d01010b0500305a310d300b0603550406130474657374310d300b0603550408130474657374310d300b0603550407130474657374310d300b060355040a130474657374310d300b060355040b130474657374310d300b0603550403130474657374301e170d3138303531373038353134395a170d3433303531313038353134395a305a310d300b0603550406130474657374310d300b0603550408130474657374310d300b0603550407130474657374310d300b060355040a130474657374310d300b060355040b130474657374310d300b060355040313047465737430820122300d06092a864886f70d01010105000382010f003082010a028201010099ce390f722f249af5176e589788db578e9ab76235a61a85eb7f7e7d2eb0cf65af74a5a0583726b3707cb91dac20e61fee98597e784c6c6a75519abe5d5749ec2747699093c2b4064a459b8defd2e558b3c318a9e7473a9735ed5f7bc701a48332ed24bdfa98078069cf6709316586f118a8de49d0a2ffee51db8196c6b3751c72aecbf12984c483c702bc92684149a412fafc60d1ef63ce3a64e14c19d78ea55845717b6a4c55102df739f4232408f0b2d3bae7fafbd2f116acd4673f6d813ad2cb10531a27a165a97ffd2aa599a84f15ac1414b0e64a14579dbc1f02636efed73be8de3eefd72d3c9478e44d4389413398e68e4f931954efdfb4988f7a747d0203010001a321301f301d0603551d0e04160414ce51752587d7ccb8c820878db07a63eb1aca4ce0300d06092a864886f70d01010b050003820101001f8ccb8f29b1461e09eb60bbcfad6b9f0c50855ea01f81180e1a8be8edacaf5d7a9a284cf2918c4316b9ecec3f185fe789957788ddf631e6fb53df53d1b038c7ca710be7b904183fe9137d5dad8ddbf89f37679148c166fbe05eddc62629aa04a9b140f4ad760c45111fd96bdffd776766a6d80088b97d53d7a096a1a260b5d70436bc9eaa474e4559f87e807d1b88b7eb61e380951766efbec39f3cb0776a013c2cba8dcc4dbc5b1b7097924bb788ba96bb99a861d930a049d38d83de09faa8128de06f3f0af69365082e0f288263c654206ca5cc21ba44489a22bf0e3352d9ce61d6ed0d8808b2b56be4e22d5fb2067b899b25b4bdce37b7f17f9ed053eb60";
const char* RELEASE_PACKAGE = "com.lee.signatureencryption";

JNIEXPORT jstring JNICALL Java_com_lee_signatureencryption_SingatureClass_verificationPackage
  (JNIEnv *env, jobject jobj, jobject context_object){
  
      jclass context_class = env->GetObjectClass(context_object);  
        
      //context.getPackageManager()  
      jmethodID methodId = env->GetMethodID(context_class, "getPackageManager", "()Landroid/content/pm/PackageManager;");  
      jobject package_manager_object = env->CallObjectMethod(context_object, methodId);  
      if (package_manager_object == NULL) {  
         
          return NULL;  
      }  

      //context.getPackageName()  
      methodId = env->GetMethodID(context_class, "getPackageName", "()Ljava/lang/String;");  
      jstring package_name_string = (jstring)env->CallObjectMethod(context_object, methodId);  
      if (package_name_string == NULL) {  
          
          return NULL;  
      }  
       
      const char* c_package = (char*)env->GetStringUTFChars(package_name_string, 0);
      if(strcmp(c_package, RELEASE_PACKAGE) == 0) {
                      
          return (env)->NewStringUTF("package true");
      } else {
      
          return (env)->NewStringUTF("package error");
      }
  }
  
  
  
JNIEXPORT jstring JNICALL Java_com_lee_signatureencryption_SingatureClass_verificationSign
  (JNIEnv *env, jobject jobj, jobject context_object){
      
        jclass context_class = env->GetObjectClass(context_object);  
          
                //context.getPackageManager()  
                jmethodID methodId = env->GetMethodID(context_class, "getPackageManager", "()Landroid/content/pm/PackageManager;");  
                jobject package_manager_object = env->CallObjectMethod(context_object, methodId);  
                if (package_manager_object == NULL) {  
                    return NULL;  
                }  
          
                //context.getPackageName()  
                methodId = env->GetMethodID(context_class, "getPackageName", "()Ljava/lang/String;");  
                jstring package_name_string = (jstring)env->CallObjectMethod(context_object, methodId);  
                if (package_name_string == NULL) {  
                    return NULL;  
                }  
          
                env->DeleteLocalRef(context_class);  
          
                //PackageManager.getPackageInfo(Sting, int)  
                jclass pack_manager_class = env->GetObjectClass(package_manager_object);  
                methodId = env->GetMethodID(pack_manager_class, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");  
                env->DeleteLocalRef(pack_manager_class);  
                jobject package_info_object = env->CallObjectMethod(package_manager_object, methodId, package_name_string, 64);  
                if (package_info_object == NULL) {  
                    return NULL;  
                }  
          
                env->DeleteLocalRef(package_manager_object);  
          
                //PackageInfo.signatures[0]  
                jclass package_info_class = env->GetObjectClass(package_info_object);  
                jfieldID fieldId = env->GetFieldID(package_info_class, "signatures", "[Landroid/content/pm/Signature;");  
                env->DeleteLocalRef(package_info_class);  
                jobjectArray signature_object_array = (jobjectArray)env->GetObjectField(package_info_object, fieldId);  
                if (signature_object_array == NULL) {  
                    return NULL;  
                }  
                jobject signature_object = env->GetObjectArrayElement(signature_object_array, 0);  
          
                env->DeleteLocalRef(package_info_object);  
          
                //Signature.toCharsString()  
                jclass signature_class = env->GetObjectClass(signature_object);  
                methodId = env->GetMethodID(signature_class, "toCharsString", "()Ljava/lang/String;");  
                env->DeleteLocalRef(signature_class);  
                jstring signature_string = (jstring) env->CallObjectMethod(signature_object, methodId);  
                
                const char* c_sign = (char*)env->GetStringUTFChars(signature_string, 0);
                
                //签名一致  返回合法的 api key，否则返回错误
                if(strcmp(c_sign, RELEASE_SIGN)==0) {
                 
                     return (env)->NewStringUTF("sign true");
                } else {
                
                  return (env)->NewStringUTF("sign error");
                  
               }
  }
