#ifndef __gozap_h__
#define __gozap_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_SimpleNativeClass_class;
extern JSObject *jsb_SimpleNativeClass_prototype;

bool js_gozap_SimpleNativeClass_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_gozap_SimpleNativeClass_finalize(JSContext *cx, JSObject *obj);
void js_register_gozap_SimpleNativeClass(JSContext *cx, JSObject *global);
void register_all_gozap(JSContext* cx, JSObject* obj);
bool js_gozap_SimpleNativeClass_getAnotherMoreComplexField(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_SimpleNativeClass_setSomeField(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_SimpleNativeClass_receivesLongLong(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_SimpleNativeClass_thisReturnsALongLong(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_SimpleNativeClass_getObjectType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_SimpleNativeClass_setAnotherMoreComplexField(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_SimpleNativeClass_setSomeOtherField(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_SimpleNativeClass_getSomeOtherField(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_SimpleNativeClass_returnsACString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_SimpleNativeClass_doSomeProcessing(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_SimpleNativeClass_getSomeField(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_SimpleNativeClass_returnsAString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_SimpleNativeClass_func(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_SimpleNativeClass_SimpleNativeClass(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_HelloWorld_class;
extern JSObject *jsb_HelloWorld_prototype;

bool js_gozap_HelloWorld_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_gozap_HelloWorld_finalize(JSContext *cx, JSObject *obj);
void js_register_gozap_HelloWorld(JSContext *cx, JSObject *global);
void register_all_gozap(JSContext* cx, JSObject* obj);
bool js_gozap_HelloWorld_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_HelloWorld_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_HelloWorld_createScene(JSContext *cx, uint32_t argc, jsval *vp);
#endif

