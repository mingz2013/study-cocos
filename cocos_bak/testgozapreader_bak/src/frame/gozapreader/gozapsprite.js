/**
 * Created by zhaojm on 14/12/2.
 */
frame.GozapSprite = cc.Node.extend({
    spriteModel:null,
    subSprite:null,
    that:null,
    currentPos:null,

    vector:null,

    ctor:function(){
        this._super();

        this.spriteModel = {};
        this.subSprite = null;
        this.that = this;
        this.currentPos = null;
        this.vector = cc.p(1, 1);

        this.scheduleUpdate();// 使这一层的update响应
    },

    onEnter:function(){
        this._super();
        this.currentPos = this.getPosition();
    },


    update: function (dt) {
        this._super(dt);
        cc.log('frame.GozapSprite->update');
        var size = cc.size();
        var x = this.currentPos.x < size.width ? this.currentPos.x : size.width;
        var x = this.currentPos.x > 0 ? this.currentPos.x : 0;
        var y = this.currentPos.y < size.height ? this.currentPos.y : size.height;
        var y = this.currentPos.y > 0 ? this.currentPos.y : 0;
        this.currentPos = cc.p(x, y);

        this.setPosition(this.currentPos);
    },


    onFrameUpdateEvent:function(timelineIndex){

        // 在subSprite播放动画的时候回调，用于改变位置
        var frameMoveObj = this.spriteModel.frameMoveObj;
        //cc.log('frame.GozapSprite->onFrameUpdateEvent, timelineIndex=', timelineIndex, 'frameMoveObj=', frameMoveObj);
        if(timelineIndex in frameMoveObj){
            cc.log('frame.GozapSprite->onFrameUpdateEvent, timelineIndex=', timelineIndex);
            var p = frameMoveObj[timelineIndex];
            //this.setPosition(cc.p(
            //    this.getPosition().x + parseFloat(p.x),
            //    this.getPosition().y + parseFloat(p.y)
            //));
            this.currentPos = cc.p(
                this.currentPos.x + this.vector.x * parseFloat(p.x),
                this.currentPos.y + this.vector.y * parseFloat(p.y)
            );

            //var size = cc.size();
            //var x = this.currentPos.x < size.width ? this.currentPos.x : size.width;
            //var x = this.currentPos.x > 0 ? this.currentPos.x : 0;
            //var y = this.currentPos.y < size.height ? this.currentPos.y : size.height;
            //var y = this.currentPos.y > 0 ? this.currentPos.y : 0;
            //if(this.currentPos.x < 0){
            //    this.currentPos.x = 0;
            //    //this.vector.x *= -1;
            //}else if(this.currentPos.x > size.width){
            //    this.currentPos.x = size.width;
            //    //this.vector.x *= -1;
            //}else{
            //
            //}
            //if(this.currentPos.y < 0){
            //    this.currentPos.y = 0;
            //    //this.vector.y *= -1;
            //}else if(this.currentPos.y > size.height){
            //    this.currentPos.y = size.height;
            //    //this.vector.y *= -1;
            //}else{
            //
            //}

            //this.currentPos = cc.p(x, y);

            //this.setPosition(this.currentPos);
        }
    },

    playSomeActionByName:function(actionname){

        var animation = cc.animationCache.getAnimation(actionname);
        var animate = frame.GozapAnimate.create(animation);
        this.playSomeAction(animate);
    },
    playSomeAction:function(action){
        this.subSprite.stopAllActions();
        this.subSprite.runAction(action);
    },


});
frame.GozapSprite.create = function(){
    return new frame.GozapSprite();
};
frame.GozapSprite.createWithModel = function(spriteModel){
    var subSprite = cc.Sprite.createWithSpriteFrame(cc.spriteFrameCache.getSpriteFrame(spriteModel.defaultSpriteFrameName));
    var gozapSprite = frame.GozapSprite.create();
    gozapSprite.addChild(subSprite);

    subSprite.setAnchorPoint(0, 0);
    subSprite.setPosition(0, 0);

    gozapSprite.spriteModel = spriteModel;
    gozapSprite.setAnchorPoint(0, 0);
    gozapSprite.setPosition(0, 0);
    gozapSprite.subSprite = subSprite;
    //gozapSprite.setContentSize(subSprite.getContentSize()); // TODO 试试这一句的必要性

    return gozapSprite;
};

frame.GozapSprite.createWithJsonFile = function(jsonfile){
    return frame.GozapSprite.createWithModel(
        frame.GozapReader.readSpriteFromJsonFile(jsonfile)
    );
};

//var test=function(){
//    var sprite = frame.GozapSprite.createWithGozapFile('res/shilaimudongzuo.json');
//    cc.batchNode.addChild(sprite);
//    sprite.runAction(
//        cc.animate.create(cc.animationCache.getAnimation('动作'))
//    );
//    var scene = cc.Scene.create();
//    var layer = cc.Layer.create();
//    layer.addChild(sprite);
//    scene.addChild(layer);
//
//    cc.Director.runScene(scene);
//};
//test();