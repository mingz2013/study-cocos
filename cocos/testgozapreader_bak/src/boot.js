/**
 * Created by zhaojm on 14/12/1.
 */
var res = {
    HelloWorld_png : "res/HelloWorld.png",
    CloseNormal_png : "res/CloseNormal.png",
    CloseSelected_png : "res/CloseSelected.png",

    shilaimudongzuo_json:"res/shilaimudongzuo.json",
    shilaimudongzuo_plist:"res/shilaimudongzuo/0.plist",
    shilaimudongzuo_png:"res/shilaimudongzuo/0.png",

    spineboy_atlas:"res/skeletons/spineboy.atlas",
    spineboy_json:"res/skeletons/spineboy.json",
    spineboy_png:"res/skeletons/spineboy.png"
};

var g_resources = [];
for (var i in res) {
    g_resources.push(res[i]);
}

cc.log(g_resources);

frame.init();
game.init();