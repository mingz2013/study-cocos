#include "jsb_gozap_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "gozap.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        JS_AddObjectRoot(cx, &pp->obj);
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    vp.set(BOOLEAN_TO_JSVAL(true));
    return true;    
}
JSClass  *jsb_GameLayer_class;
JSObject *jsb_GameLayer_prototype;

bool js_gozap_GameLayer_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameLayer* cobj = (GameLayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_GameLayer_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_gozap_GameLayer_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_gozap_GameLayer_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        GameLayer* ret = GameLayer::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<GameLayer>(cx, (GameLayer*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    JS_ReportError(cx, "js_gozap_GameLayer_create : wrong number of arguments");
    return false;
}

bool js_gozap_GameLayer_createScene(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        cocos2d::Scene* ret = GameLayer::createScene();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Scene>(cx, (cocos2d::Scene*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    JS_ReportError(cx, "js_gozap_GameLayer_createScene : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Layer_prototype;

void js_GameLayer_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GameLayer)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        GameLayer *nobj = static_cast<GameLayer *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_gozap_GameLayer(JSContext *cx, JSObject *global) {
    jsb_GameLayer_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameLayer_class->name = "GameLayer";
    jsb_GameLayer_class->addProperty = JS_PropertyStub;
    jsb_GameLayer_class->delProperty = JS_DeletePropertyStub;
    jsb_GameLayer_class->getProperty = JS_PropertyStub;
    jsb_GameLayer_class->setProperty = JS_StrictPropertyStub;
    jsb_GameLayer_class->enumerate = JS_EnumerateStub;
    jsb_GameLayer_class->resolve = JS_ResolveStub;
    jsb_GameLayer_class->convert = JS_ConvertStub;
    jsb_GameLayer_class->finalize = js_GameLayer_finalize;
    jsb_GameLayer_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("init", js_gozap_GameLayer_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_gozap_GameLayer_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createScene", js_gozap_GameLayer_createScene, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_GameLayer_prototype = JS_InitClass(
        cx, global,
        jsb_cocos2d_Layer_prototype,
        jsb_GameLayer_class,
        dummy_constructor<GameLayer>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "GameLayer", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<GameLayer> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_GameLayer_class;
        p->proto = jsb_GameLayer_prototype;
        p->parentProto = jsb_cocos2d_Layer_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_gozap(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, obj, "gozap", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "gozap", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_gozap_GameLayer(cx, obj);
}

