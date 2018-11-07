/**
 * Created by zhaojm on 14/12/3.
 */
frame.GozapSpriteModel = cc.Class.extend({
    plistUrl:null,  // 需要的plist文件，用于之后的销毁时移除图片
    defaultSpriteFrameName:null,    // 默认的第一帧
    actionlist:null,            // 动作列表
    frameMoveObj:null,      // 移动数据


    ctor:function(){
        this.plistUrl = "";
        this.defaultSpriteFrameName = null;
        this.actionlist = [];
        this.frameMoveObj = {};
    },

});