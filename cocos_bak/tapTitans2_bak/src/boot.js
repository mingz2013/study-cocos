/**
 * Created by zhaojm on 15/1/10.
 */

// 预加载的资源
var res = {
    // plist
    hero_plist : "res/img/hero.plist",
    hero_png : "res/img/hero.png",
    effect_plist : "res/img/effect.plist",
    effect_png : "res/img/effect.png",

    // jpg
    background_jpg : "res/img/background.jpg",

    //skeletons
    moster0_atlas : "res/skeletons/guaiwu1.atlas",
    moster0_json : "res/skeletons/guaiwu1.json",
    moster0_png : "res/skeletons/guaiwu1.png",
    moster1_atlas : "res/skeletons/guaiwu-2.atlas",
    moster1_json : "res/skeletons/guaiwu-2.json",
    moster1_png : "res/skeletons/guaiwu-2.png",
    moster2_atlas : "res/skeletons/guaiwu-3.atlas",
    moster2_json : "res/skeletons/guaiwu-3.json",
    moster2_png : "res/skeletons/guaiwu-3.png",
    moster3_atlas : "res/skeletons/guaiwu-4-2.atlas",
    moster3_json : "res/skeletons/guaiwu-4-2.json",
    moster3_png : "res/skeletons/guaiwu-4-2.png",

    spineboy_atlas : "res/skeletons/spineboy.atlas",
    spineboy_json : "res/skeletons/spineboy.json",
    spineboy_png : "res/skeletons/spineboy.png",
};

var g_resources = [];
for (var i in res) {
    g_resources.push(res[i]);
}

cc.log('g_resources=', g_resources);

//
//var res = {
//    anim:"res/flaxAnim.plist"
//};
//
//var res_helloWorld = [
//    res.anim
//];
