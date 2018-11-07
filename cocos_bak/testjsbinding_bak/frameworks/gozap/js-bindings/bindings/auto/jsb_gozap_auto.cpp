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
JSClass  *jsb_SimpleNativeClass_class;
JSObject *jsb_SimpleNativeClass_prototype;

bool js_gozap_SimpleNativeClass_getAnotherMoreComplexField(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_SimpleNativeClass_getAnotherMoreComplexField : Invalid Native Object");
    if (argc == 0) {
        const char* ret = cobj->getAnotherMoreComplexField();
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_gozap_SimpleNativeClass_getAnotherMoreComplexField : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_gozap_SimpleNativeClass_setSomeField(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;

    JSObject *obj = NULL;
    SimpleNativeClass* cobj = NULL;
    obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_SimpleNativeClass_setSomeField : Invalid Native Object");
    do {
        if (argc == 0) {
            cobj->setSomeField();
            JS_SET_RVAL(cx, vp, JSVAL_VOID);
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            int arg0;
            ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            cobj->setSomeField(arg0);
            JS_SET_RVAL(cx, vp, JSVAL_VOID);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_gozap_SimpleNativeClass_setSomeField : wrong number of arguments");
    return false;
}
bool js_gozap_SimpleNativeClass_receivesLongLong(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_SimpleNativeClass_receivesLongLong : Invalid Native Object");
    if (argc == 1) {
        long long arg0;
        ok &= jsval_to_long_long(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_gozap_SimpleNativeClass_receivesLongLong : Error processing arguments");
        long long ret = cobj->receivesLongLong(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = long_long_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_gozap_SimpleNativeClass_receivesLongLong : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_gozap_SimpleNativeClass_thisReturnsALongLong(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_SimpleNativeClass_thisReturnsALongLong : Invalid Native Object");
    if (argc == 0) {
        long long ret = cobj->thisReturnsALongLong();
        jsval jsret = JSVAL_NULL;
        jsret = long_long_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_gozap_SimpleNativeClass_thisReturnsALongLong : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_gozap_SimpleNativeClass_getObjectType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_SimpleNativeClass_getObjectType : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getObjectType();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_gozap_SimpleNativeClass_getObjectType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_gozap_SimpleNativeClass_setAnotherMoreComplexField(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_SimpleNativeClass_setAnotherMoreComplexField : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_gozap_SimpleNativeClass_setAnotherMoreComplexField : Error processing arguments");
        cobj->setAnotherMoreComplexField(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_gozap_SimpleNativeClass_setAnotherMoreComplexField : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_gozap_SimpleNativeClass_setSomeOtherField(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_SimpleNativeClass_setSomeOtherField : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_gozap_SimpleNativeClass_setSomeOtherField : Error processing arguments");
        cobj->setSomeOtherField(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_gozap_SimpleNativeClass_setSomeOtherField : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_gozap_SimpleNativeClass_getSomeOtherField(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_SimpleNativeClass_getSomeOtherField : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getSomeOtherField();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_gozap_SimpleNativeClass_getSomeOtherField : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_gozap_SimpleNativeClass_returnsACString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_SimpleNativeClass_returnsACString : Invalid Native Object");
    if (argc == 0) {
        const char* ret = cobj->returnsACString();
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_gozap_SimpleNativeClass_returnsACString : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_gozap_SimpleNativeClass_doSomeProcessing(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_SimpleNativeClass_doSomeProcessing : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_gozap_SimpleNativeClass_doSomeProcessing : Error processing arguments");
        int ret = cobj->doSomeProcessing(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_gozap_SimpleNativeClass_doSomeProcessing : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_gozap_SimpleNativeClass_getSomeField(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_SimpleNativeClass_getSomeField : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getSomeField();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_gozap_SimpleNativeClass_getSomeField : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_gozap_SimpleNativeClass_returnsAString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SimpleNativeClass* cobj = (SimpleNativeClass *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_SimpleNativeClass_returnsAString : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->returnsAString();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_gozap_SimpleNativeClass_returnsAString : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_gozap_SimpleNativeClass_func(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            int arg0;
            ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            SimpleNativeClass::func(arg0);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            SimpleNativeClass::func();
            return true;
        }
    } while (0);
    
    do {
        if (argc == 2) {
            int arg0;
            ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            double arg1;
            ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[1]), &arg1);
            if (!ok) { ok = true; break; }
            SimpleNativeClass::func(arg0, arg1);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_gozap_SimpleNativeClass_func : wrong number of arguments");
    return false;
}
bool js_gozap_SimpleNativeClass_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;

    JSObject *obj = NULL;
    SimpleNativeClass* cobj = NULL;
    do {
        if (argc == 1) {
            int arg0;
            ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            cobj = new (std::nothrow) SimpleNativeClass(arg0);
            TypeTest<SimpleNativeClass> t;
            js_type_class_t *typeClass = nullptr;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
            typeClass = typeMapIter->second;
            CCASSERT(typeClass, "The value is null.");
            obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            js_proxy_t* p = jsb_new_proxy(cobj, obj);
        }
    } while(0);

    do {
        if (argc == 0) {
            cobj = new (std::nothrow) SimpleNativeClass();
            TypeTest<SimpleNativeClass> t;
            js_type_class_t *typeClass = nullptr;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
            typeClass = typeMapIter->second;
            CCASSERT(typeClass, "The value is null.");
            obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            js_proxy_t* p = jsb_new_proxy(cobj, obj);
        }
    } while(0);

    do {
        if (argc == 2) {
            int arg0;
            ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            int arg1;
            ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            cobj = new (std::nothrow) SimpleNativeClass(arg0, arg1);
            TypeTest<SimpleNativeClass> t;
            js_type_class_t *typeClass = nullptr;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
            typeClass = typeMapIter->second;
            CCASSERT(typeClass, "The value is null.");
            obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            js_proxy_t* p = jsb_new_proxy(cobj, obj);
        }
    } while(0);

    if (cobj) {
        if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
                ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);

        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
        return true;
    }
    JS_ReportError(cx, "js_gozap_SimpleNativeClass_constructor : wrong number of arguments");
    return false;
}



void js_SimpleNativeClass_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SimpleNativeClass)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        SimpleNativeClass *nobj = static_cast<SimpleNativeClass *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_gozap_SimpleNativeClass(JSContext *cx, JSObject *global) {
    jsb_SimpleNativeClass_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SimpleNativeClass_class->name = "SimpleNativeClass";
    jsb_SimpleNativeClass_class->addProperty = JS_PropertyStub;
    jsb_SimpleNativeClass_class->delProperty = JS_DeletePropertyStub;
    jsb_SimpleNativeClass_class->getProperty = JS_PropertyStub;
    jsb_SimpleNativeClass_class->setProperty = JS_StrictPropertyStub;
    jsb_SimpleNativeClass_class->enumerate = JS_EnumerateStub;
    jsb_SimpleNativeClass_class->resolve = JS_ResolveStub;
    jsb_SimpleNativeClass_class->convert = JS_ConvertStub;
    jsb_SimpleNativeClass_class->finalize = js_SimpleNativeClass_finalize;
    jsb_SimpleNativeClass_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getAnotherMoreComplexField", js_gozap_SimpleNativeClass_getAnotherMoreComplexField, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSomeField", js_gozap_SimpleNativeClass_setSomeField, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("receivesLongLong", js_gozap_SimpleNativeClass_receivesLongLong, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("thisReturnsALongLong", js_gozap_SimpleNativeClass_thisReturnsALongLong, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getObjectType", js_gozap_SimpleNativeClass_getObjectType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnotherMoreComplexField", js_gozap_SimpleNativeClass_setAnotherMoreComplexField, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSomeOtherField", js_gozap_SimpleNativeClass_setSomeOtherField, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSomeOtherField", js_gozap_SimpleNativeClass_getSomeOtherField, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("returnsACString", js_gozap_SimpleNativeClass_returnsACString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("doSomeProcessing", js_gozap_SimpleNativeClass_doSomeProcessing, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSomeField", js_gozap_SimpleNativeClass_getSomeField, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("returnsAString", js_gozap_SimpleNativeClass_returnsAString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("func", js_gozap_SimpleNativeClass_func, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_SimpleNativeClass_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_SimpleNativeClass_class,
        js_gozap_SimpleNativeClass_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SimpleNativeClass", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<SimpleNativeClass> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_SimpleNativeClass_class;
        p->proto = jsb_SimpleNativeClass_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_HelloWorld_class;
JSObject *jsb_HelloWorld_prototype;

bool js_gozap_HelloWorld_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    HelloWorld* cobj = (HelloWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_gozap_HelloWorld_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_gozap_HelloWorld_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_gozap_HelloWorld_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        HelloWorld* ret = HelloWorld::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<HelloWorld>(cx, (HelloWorld*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    JS_ReportError(cx, "js_gozap_HelloWorld_create : wrong number of arguments");
    return false;
}

bool js_gozap_HelloWorld_createScene(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        cocos2d::Scene* ret = HelloWorld::createScene();
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
    JS_ReportError(cx, "js_gozap_HelloWorld_createScene : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Layer_prototype;

void js_HelloWorld_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HelloWorld)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        HelloWorld *nobj = static_cast<HelloWorld *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_gozap_HelloWorld(JSContext *cx, JSObject *global) {
    jsb_HelloWorld_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_HelloWorld_class->name = "HelloWorld";
    jsb_HelloWorld_class->addProperty = JS_PropertyStub;
    jsb_HelloWorld_class->delProperty = JS_DeletePropertyStub;
    jsb_HelloWorld_class->getProperty = JS_PropertyStub;
    jsb_HelloWorld_class->setProperty = JS_StrictPropertyStub;
    jsb_HelloWorld_class->enumerate = JS_EnumerateStub;
    jsb_HelloWorld_class->resolve = JS_ResolveStub;
    jsb_HelloWorld_class->convert = JS_ConvertStub;
    jsb_HelloWorld_class->finalize = js_HelloWorld_finalize;
    jsb_HelloWorld_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("init", js_gozap_HelloWorld_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_gozap_HelloWorld_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createScene", js_gozap_HelloWorld_createScene, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_HelloWorld_prototype = JS_InitClass(
        cx, global,
        jsb_cocos2d_Layer_prototype,
        jsb_HelloWorld_class,
        dummy_constructor<HelloWorld>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "HelloWorld", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<HelloWorld> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_HelloWorld_class;
        p->proto = jsb_HelloWorld_prototype;
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

    js_register_gozap_SimpleNativeClass(cx, obj);
    js_register_gozap_HelloWorld(cx, obj);
}

