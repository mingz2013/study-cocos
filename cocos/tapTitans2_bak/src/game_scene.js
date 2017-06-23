/**
 * Created by zhaojm on 15/1/10.
 */

var GameLayer = cc.Layer.extend({

    hero : null,
    moster: null,
    attackedNum:0,
    //touchDelay : 0,
    ctor:function () {

        this._super();
        var size = cc.winSize;

        ccs.spriteFrameCacheHelper.addSpriteFrameFromFile(res.hero_plist, res.hero_png);
        cc.spriteFrameCache.addSpriteFrames(res.effect_plist, res.effect_png);

        var background = new cc.Sprite(res.background_jpg);
        background.setAnchorPoint(cc.p(0, 0));
        background.setPosition(cc.p(0, 0));
        //background.setScale(0.4);
        this.addChild(background);
        //
        this.hero = new Hero();
        this.addChild(this.hero, 1);
        //this.hero.setPosition(cc.p(size.width / 2, size.height / 2));
        //
        this.moster = new Moster();
        this.addChild(this.moster);
        //this.moster.setPosition(cc.p(size.width / 2, size.height / 2));

        var that = this;
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,                       // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
            onTouchBegan: function (touch, event) {     //实现 onTouchBegan 事件回调函数
                //if(that.hero.actionstate == that.hero.animations.idle.name){
                    that.hero.attack();
                //}else{
                //    //cc.log("push ontouch");
                //    that.hero.actionList.push(that.touchDelay);
                //
                //}
                that.moster.attacked();
                //cc.log("touchDelay->", that.touchDelay);
                //that.touchDelay = 0;

                if(that.attackedNum++ > 10){
                    that.attackedNum = 0;
                    that.moster.nextMoster();
                }

                return true;
            },

        }, this);

        this.scheduleUpdate();

        return true;
    },

    onEnter : function() {
        this._super();
    },

    //update : function(dt) {
    //    this._super();
    //    this.touchDelay += dt;
    //},

});

var GameScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new GameLayer();
        this.addChild(layer);
    }
});

