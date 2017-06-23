/**
 * Created by zhaojm on 15/1/10.
 */
var Hero = cc.Sprite.extend({

    animations : {
        idle : {name:"idle", maxCount:16, frameTime:0.2},

        attack00 : {name : "attack00", maxCount : 4, frameTime : 0.05},
        attack01 : {name : "attack01", maxCount : 6, frameTime : 0.1},

        attack10 : {name : "attack10", maxCount : 4, frameTime : 0.05},
        attack11 : {name : "attack11", maxCount : 3, frameTime : 0.13},

        attack20 : {name : "attack20", maxCount : 4, frameTime : 0.05},
        attack21 : {name : "attack21", maxCount : 4, frameTime : 0.1},
    },

    createAnimation:function(animation, time){
        cc.log("BaseSprite->createAniamtion");

        if(time == null){
            time = animation.frameTime * animation.maxCount;
        }

        var frames = [];
        for(var i = 0; i < animation.maxCount; i++){
            var frame = cc.spriteFrameCache.getSpriteFrame(animation.name + "/" + i + ".png");
            frames.push(frame);
        }
        var delay = time / animation.maxCount;
        cc.log("delay->", delay, "actionname->", animation.name);
        var anim  = cc.Animation.create(frames, delay);
        //cc.animationCache.addAnimation(anim, animation.name);
        var animate = cc.Animate.create(anim);
        return animate;
    },



    actionList : null,

    actionstate: null,

    ctor : function(){
        this._super();
        this.actionList = [];
        this.setAnchorPoint(0, 0);
    },


    onEnter:function(){
        this._super();
        this.idle();
    },



    playAnimOnce : function(action){
        //var animation = cc.animationCache.getAnimation(actionname);
        //var animate = cc.Animate.create(animation);

        var callback = cc.CallFunc.create(this.onAfterAnim, this);

        var seq = cc.Sequence.create(action, callback);

        this.stopAllActions();
        this.runAction(seq);
    },

    playAnimRepeatForever : function(action){
        cc.log("base_sprite->playAnimRepeatForever");
        //var animation = cc.animationCache.getAnimation(actionname);
        //var animate = cc.Animate.create(animation);
        var actionForever = cc.RepeatForever.create(action);
        this.stopAllActions();
        this.runAction(actionForever);
    },


    onAfterAnim:function(){
        if(this.actionList.length > 0){
            var time = this.actionList[0];
            this.attack(time);

            var actionListTmp = [];
            for(var i = 1; i < this.actionList.length; i++){
                actionListTmp.push(this.actionList[i]);
            }
            this.actionList = actionListTmp;

        }else{
            this.idle();
        }

    },

    idle:function(){
        var animate = this.createAnimation(this.animations.idle);

        this.playAnimRepeatForever(animate);

        this.actionstate = this.animations.idle.name;
    },

    attack : function(time) {
        if (this.actionstate == this.animations.attack00.name) {
            this.attack1(time);
        } else if (this.actionstate == this.animations.attack10.name) {
            this.attack2(time);
        } else if (this.actionstate == this.animations.attack20.name) {
            this.attack0(time);
        } else if (this.actionstate == this.animations.idle.name) {
            this.attack0(time);
        }
    },

    attack0 : function(time){
        //time = time - this.animations.attack00.frameTime * this.animations.attack00.maxCount;
        //time = (this.animations.attack01.frameTime * this.animations.attack01.maxCount  < time) ? (this.animations.attack01.frameTime * this.animations.attack01.maxCount) : time;

        var attack00 = this.createAnimation(this.animations.attack00);
        var attack01 = this.createAnimation(this.animations.attack01);
        var attack0 = cc.Sequence.create(attack00, attack01);
        this.playAnimOnce(attack0);
        this.actionstate = this.animations.attack00.name;
    },


    attack1 : function(time){
        //time = time - this.animations.attack10.frameTime * this.animations.attack10.maxCount;
        //time = (this.animations.attack11.frameTime * this.animations.attack11.maxCount  < time) ? (this.animations.attack11.frameTime * this.animations.attack11.maxCount) : time;

        var attack10 = this.createAnimation(this.animations.attack10);
        var attack11 = this.createAnimation(this.animations.attack11);
        var attack1 = cc.Sequence.create(attack10, attack11);
        this.playAnimOnce(attack1);
        this.actionstate = this.animations.attack10.name;
    },


    attack2 : function(time){
        //time = time - this.animations.attack20.frameTime * this.animations.attack20.maxCount;
        //time = (this.animations.attack21.frameTime * this.animations.attack21.maxCount  < time) ? (this.animations.attack21.frameTime * this.animations.attack21.maxCount) : time;

        var attack20 = this.createAnimation(this.animations.attack20);
        var attack21 = this.createAnimation(this.animations.attack21);
        var attack2 = cc.Sequence.create(attack20, attack21);
        this.playAnimOnce(attack2);
        this.actionstate = this.animations.attack20.name;
    },

});
