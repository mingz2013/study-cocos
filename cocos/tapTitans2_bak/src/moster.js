/**
 * Created by zhaojm on 15/1/14.
 */

//
//var ANIMATION_TYPE = {
//    ANIMATION_START:      0,
//    ANIMATION_END:        1,
//    ANIMATION_COMPLETE:   2,
//    ANIMATION_EVENT:      3
//};

var Moster = cc.Node.extend({

    mosterData : [
        {jsonfile:res.moster0_json, atlasfile:res.moster0_atlas},
        {jsonfile:res.moster1_json, atlasfile:res.moster1_atlas},
        {jsonfile:res.moster2_json, atlasfile:res.moster2_atlas},
        {jsonfile:res.moster3_json, atlasfile:res.moster3_atlas},
    ],


    currentMoster : null,
    currentMosterIndex : null,
    //mosterList : [],

    ctor : function(){
        this._super();

        var size = cc.winSize;
        this.setPosition(cc.p(size.width / 2, size.height / 2 - 60));

        this.setCurrentMoster(0);

    },

    onEnter:function(){
        this._super();
    },

    animationStateEvent: function(obj, trackIndex, type, event, loopCount) {
        var entry = this.currentMoster.getCurrent();
        var animationName = (entry && entry.animation) ? entry.animation.name : 0;

        switch(type)
        {
            case sp.ANIMATION_EVENT_TYPE.START:
                cc.log(trackIndex + " start: " + animationName);
                break;
            case sp.ANIMATION_EVENT_TYPE.END:
                cc.log(trackIndex + " end:" + animationName);

                //this.currentMoster.setAnimation(0, 'idle', true);
                //this._spineboy.setAnimation(0, 'walk', true);
                break;
            case sp.ANIMATION_EVENT_TYPE.EVENT:
                cc.log(trackIndex + " event: " + animationName);
                break;
            case sp.ANIMATION_EVENT_TYPE.COMPLETE:
                cc.log(trackIndex + " complete: " + animationName + "," + loopCount);
                //if(this._flipped){
                //    this._flipped = false;
                //    this.currentMoster.setScaleX(1);
                //}else{
                //    this._flipped = true;
                //    this.currentMoster.setScaleX(-1);
                //}
                this.currentMoster.setAnimation(0, 'idle', true);

                break;
            default :
                break;
        }
    },

    nextMoster : function(){
        var currentIndex = this.currentMosterIndex;
        currentIndex = currentIndex + 1 < this.mosterData.length ?  currentIndex + 1 : 0;
        this.setCurrentMoster(currentIndex);
    },

    setCurrentMoster:function(index){
        cc.assert(index < this.mosterData.length, 'index error');
        if(this.currentMosterIndex == index) {
            return;
        }
        this.currentMosterIndex = index;
        this.removeChild(this.currentMoster);
        this.currentMoster = this.createMoster(this.currentMosterIndex);
        this.addChild(this.currentMoster);
    },

    createMoster : function(index){
        cc.assert(index < this.mosterData.length, 'index error');
        // 创建
        var moster = sp.SkeletonAnimation.create(this.mosterData[index].jsonfile, this.mosterData[index].atlasfile, 0.5);
        // 设置位置
        //moster0.setPosition(cc.p(size.width / 2, size.height / 2 - 60));
        // 设置动作
        moster.setAnimation(0, 'idle', true);

        // 设置混合
        moster.setMix('idle', 'attacked', 0.1);
        moster.setMix('idle', 'attacked2', 0.1);
        moster.setMix('attacked', 'idle', 0.1);
        moster.setMix('attacked2', 'idle', 0.1);
        // 设置监听
        moster.setAnimationListener(this, this.animationStateEvent);

        // 当要连续播放不同的动画时，用addAnimation
        //moster0.addAnimation(0, 'attacked', false);
        // 设置播放速度
        moster.setTimeScale(1);
        // 设置骨骼隐藏显示
        moster.setDebugBones(true);

        return moster;

    },

    idle : function(){

        this.currentMoster.setAnimation(0, 'idle', true);
    },

    attacked : function(){
        //this._spineboy.setAnimation(0, 'jump', false);
        this.currentMoster.setAnimation(0, 'attacked', false);
    },

    attacked2 : function(){

        this.currentMoster.setAnimation(0, 'attacked2', false);
    },






});