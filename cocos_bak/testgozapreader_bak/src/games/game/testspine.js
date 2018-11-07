/**
 * Created by zhaojm on 14/12/4.
 */
/**
 * Created by zhaojm on 14/12/2.
 */
var sp = sp || {};

var ANIMATION_TYPE = {
    ANIMATION_START:      0,
    ANIMATION_END:        1,
    ANIMATION_COMPLETE:   2,
    ANIMATION_EVENT:      3
};

var touchcount = 0;

var TestSpineLayer = cc.Layer.extend({
    //sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        var size = cc.winSize;
        //
        //// add a "close" icon to exit the progress. it's an autorelease object
        //var closeItem = new cc.MenuItemImage(
        //    res.CloseNormal_png,
        //    res.CloseSelected_png,
        //    function () {
        //        cc.log("Menu is clicked!");
        //        //this.gozapSprite.currentPos = cc.p(size.width / 2, size.height / 2);
        //
        //        this._spineboy.setAnimation(0, ['walk', 'jump'][touchcount % 2], true);
        //        //gozapSprite.playSomeAction(cc.RepeatForever.create(frame.GozapAnimate.create(cc.animationCache.getAnimation('移动'))));
        //        touchcount++;
        //    }, this);
        //closeItem.attr({
        //    x: size.width - 20,
        //    y: 20,
        //    anchorX: 0.5,
        //    anchorY: 0.5
        //});
        //
        //var menu = new cc.Menu(closeItem);
        //menu.x = 0;
        //menu.y = 0;
        //this.addChild(menu, 1);

        //this.sprite = new cc.Sprite(res.HelloWorld_png);
        //this.sprite.attr({
        //    x: size.width / 2,
        //    y: size.height/ 2
        //    //scale: 0.5,
        //    //rotation: 180
        //});
        //this.addChild(this.sprite, 0);



        for(var i = 0; i < 1; i++){
            var spineBoy = new sp.SkeletonAnimation('res/skeletons/spineboy.json', 'res/skeletons/spineboy.atlas');
            spineBoy.setPosition(cc.p(size.width * Math.random(), size.height * Math.random()));
            spineBoy.setAnimation(0, 'walk', true);
            spineBoy.setMix('walk', 'jump', 0.2);
            spineBoy.setMix('jump', 'walk', 0.4);
            //spineBoy.setAnimationListener(this, this.animationStateEvent);
            this.addChild(spineBoy, 4);

        }

        //var spineBoy = new sp.SkeletonAnimation('res/skeletons/spineboy.json', 'res/skeletons/spineboy.atlas');
        //spineBoy.setPosition(cc.p(size.width / 2, size.height / 2 - 150));
        //spineBoy.setAnimation(0, 'walk', true);
        //spineBoy.setMix('walk', 'jump', 0.2);
        //spineBoy.setMix('jump', 'walk', 0.4);
        ////spineBoy.setAnimationListener(this, this.animationStateEvent);
        //this.addChild(spineBoy, 4);
        //this._spineboy = spineBoy;



        //var gozapSprite = frame.GozapSprite.createWithJsonFile('res/shilaimudongzuo.json');
        //this.addChild(gozapSprite);
        //gozapSprite.setPosition(size.width / 2, size.height / 2);
        //gozapSprite.playSomeActionByName('移动');
        //gozapSprite.playSomeAction(cc.RepeatForever.create(frame.GozapAnimate.create(cc.animationCache.getAnimation('移动'))));
        //this.gozapSprite = gozapSprite;

        return true;
    },
    //
    //animationStateEvent: function(obj, trackIndex, type, event, loopCount) {
    //    var entry = this._spineboy.getCurrent();
    //    var animationName = (entry && entry.animation) ? entry.animation.name : 0;
    //
    //    switch(type)
    //    {
    //        case ANIMATION_TYPE.ANIMATION_START:
    //            cc.log(trackIndex + " start: " + animationName);
    //            break;
    //        case ANIMATION_TYPE.ANIMATION_END:
    //            cc.log(trackIndex + " end:" + animationName);
    //            break;
    //        case ANIMATION_TYPE.ANIMATION_EVENT:
    //            cc.log(trackIndex + " event: " + animationName);
    //            break;
    //        case ANIMATION_TYPE.ANIMATION_COMPLETE:
    //            cc.log(trackIndex + " complete: " + animationName + "," + loopCount);
    //            break;
    //        default :
    //            break;
    //    }
    //},


});

var TestSpineScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new TestSpineLayer();
        this.addChild(layer);
    }
});

