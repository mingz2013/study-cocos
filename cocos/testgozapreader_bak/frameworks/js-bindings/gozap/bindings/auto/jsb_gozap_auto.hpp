#ifndef __gozap_h__
#define __gozap_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_GameLayer_class;
extern JSObject *jsb_GameLayer_prototype;

bool js_gozap_GameLayer_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_gozap_GameLayer_finalize(JSContext *cx, JSObject *obj);
void js_register_gozap_GameLayer(JSContext *cx, JSObject *global);
void register_all_gozap(JSContext* cx, JSObject* obj);
bool js_gozap_GameLayer_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_GameLayer_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_gozap_GameLayer_createScene(JSContext *cx, uint32_t argc, jsval *vp);
#endif

